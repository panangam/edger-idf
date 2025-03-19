#pragma once

#include "esp_log.h"
#include "driver/gpio.h"
#include "driver/mcpwm_prelude.h"

#define PWM_LEVEL_RESOLUTION 100

class MotorController
{
public:
    MotorController(gpio_num_t pinPWM, uint32_t freq = 25000);
    ~MotorController();
    void setSpeed(float speed);

    gpio_num_t pinPWM;
    uint32_t freq;
    mcpwm_timer_handle_t timer;
    mcpwm_oper_handle_t oper;
    mcpwm_cmpr_handle_t comparator;
    mcpwm_gen_handle_t generator;
};

MotorController::MotorController(gpio_num_t pinPWM, uint32_t freq)
  : pinPWM(pinPWM), freq(freq)
{
    mcpwm_timer_config_t timerConfig = {
        .group_id = 0,
        .clk_src = MCPWM_TIMER_CLK_SRC_DEFAULT,
        .resolution_hz = PWM_LEVEL_RESOLUTION * freq,
        .count_mode = MCPWM_TIMER_COUNT_MODE_UP,
        .period_ticks = PWM_LEVEL_RESOLUTION
    };
    ESP_ERROR_CHECK(mcpwm_new_timer(&timerConfig, &timer));

    mcpwm_operator_config_t operatorConfig = {
        .group_id = 0 // operator must be in the same group to the timer
    };
    ESP_ERROR_CHECK(mcpwm_new_operator(&operatorConfig, &oper));

    // Connect timer and operator
    ESP_ERROR_CHECK(mcpwm_operator_connect_timer(oper, timer));

    mcpwm_comparator_config_t comparator_config = {
        .flags = {
            .update_cmp_on_tez = true
        }
    };
    ESP_ERROR_CHECK(mcpwm_new_comparator(oper, &comparator_config, &comparator));

    mcpwm_generator_config_t generator_config = {
        .gen_gpio_num = pinPWM,
    };
    ESP_ERROR_CHECK(mcpwm_new_generator(oper, &generator_config, &generator));

    // set the initial compare value
    ESP_ERROR_CHECK(mcpwm_comparator_set_compare_value(comparator, 0));

    // go high on counter empty
    ESP_ERROR_CHECK(mcpwm_generator_set_action_on_timer_event(
        generator,
        MCPWM_GEN_TIMER_EVENT_ACTION(MCPWM_TIMER_DIRECTION_UP, MCPWM_TIMER_EVENT_EMPTY, MCPWM_GEN_ACTION_HIGH)
    ));
    // go low on compare threshold
    ESP_ERROR_CHECK(mcpwm_generator_set_action_on_compare_event(
        generator,
        MCPWM_GEN_COMPARE_EVENT_ACTION(MCPWM_TIMER_DIRECTION_UP, comparator, MCPWM_GEN_ACTION_LOW)
    ));

    ESP_ERROR_CHECK(mcpwm_timer_enable(timer));
    ESP_ERROR_CHECK(mcpwm_timer_start_stop(timer, MCPWM_TIMER_START_NO_STOP));
}

MotorController::~MotorController()
{
    mcpwm_del_generator(generator);
    mcpwm_del_comparator(comparator);
    mcpwm_del_operator(oper);
    mcpwm_del_timer(timer);
}

void MotorController::setSpeed(float speed)
{
    assert(speed >= 0 && speed <= 1);

    uint32_t speedTicks = speed * PWM_LEVEL_RESOLUTION;
    // ESP_LOGI("MotorController", "speed %lu", speedTicks);
    ESP_ERROR_CHECK(mcpwm_comparator_set_compare_value(comparator, speedTicks));
}
