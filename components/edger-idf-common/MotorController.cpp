#include "MotorController.hpp"

constexpr const char* TAG = "MotorController";

mcpwm_timer_handle_t timers[3] = {nullptr, nullptr, nullptr};
mcpwm_oper_handle_t operators[3] = {nullptr, nullptr, nullptr};

MotorController::MotorController(gpio_num_t pinPWM, int timerIdx, uint32_t freq)
  : pinPWM(pinPWM), freq(freq)
{
    if (timers[timerIdx] == nullptr)
    {
        ESP_LOGI(TAG, "Creating timer and operator %d", timerIdx);
        mcpwm_timer_config_t timerConfig = {
            .group_id = 0,
            .clk_src = MCPWM_TIMER_CLK_SRC_DEFAULT,
            .resolution_hz = PWM_LEVEL_RESOLUTION * freq,
            .count_mode = MCPWM_TIMER_COUNT_MODE_UP,
            .period_ticks = PWM_LEVEL_RESOLUTION
        };
        ESP_ERROR_CHECK(mcpwm_new_timer(&timerConfig, &timers[timerIdx]));
        ESP_ERROR_CHECK(mcpwm_timer_enable(timers[timerIdx]));
        ESP_ERROR_CHECK(mcpwm_timer_start_stop(timers[timerIdx], MCPWM_TIMER_START_NO_STOP));

        mcpwm_operator_config_t operatorConfig = {
            .group_id = 0  // ESP32C6 has only one MCPWM group
        };
        ESP_ERROR_CHECK(mcpwm_new_operator(&operatorConfig, &operators[timerIdx]));
        ESP_ERROR_CHECK(mcpwm_operator_connect_timer(operators[timerIdx], timers[timerIdx]));
    }
    else
    {
        ESP_LOGI(TAG, "Using existing timer and operator %d", timerIdx);
    }
    // Set the timer and operator for this instance
    timer = timers[timerIdx];
    oper = operators[timerIdx];

    // define new comparator and generator
    // NOTE: ESP32C6 has 2 comparators and 2 generators per operator
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

    // Set the initial compare value
    ESP_ERROR_CHECK(mcpwm_comparator_set_compare_value(comparator, 0));

    // Go high on counter empty
    ESP_ERROR_CHECK(mcpwm_generator_set_action_on_timer_event(
        generator,
        MCPWM_GEN_TIMER_EVENT_ACTION(MCPWM_TIMER_DIRECTION_UP, MCPWM_TIMER_EVENT_EMPTY, MCPWM_GEN_ACTION_HIGH)
    ));
    // Go low on compare threshold
    ESP_ERROR_CHECK(mcpwm_generator_set_action_on_compare_event(
        generator,
        MCPWM_GEN_COMPARE_EVENT_ACTION(MCPWM_TIMER_DIRECTION_UP, comparator, MCPWM_GEN_ACTION_LOW)
    ));
}

MotorController::~MotorController()
{
    mcpwm_del_generator(generator);
    mcpwm_del_comparator(comparator);
    // mcpwm_del_operator(oper);  operators are shared so can't delete here; oh well
    // mcpwm_dels_timer(timer);  timers are shared so can't delete here; oh well
}

void MotorController::setSpeed(float speed)
{
    assert(speed >= 0 && speed <= 1);

    uint32_t speedTicks = speed * PWM_LEVEL_RESOLUTION;
    ESP_ERROR_CHECK(mcpwm_comparator_set_compare_value(comparator, speedTicks));
}
