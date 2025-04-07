#pragma once

#include "esp_log.h"
#include "driver/gpio.h"
#include "driver/mcpwm_prelude.h"

#define PWM_LEVEL_RESOLUTION 256

class MotorController
{
public:
    MotorController(gpio_num_t pinPWM, uint32_t freq = 25000);
    ~MotorController();
    void setSpeed(float speed);

private:
    gpio_num_t pinPWM;
    uint32_t freq;
    mcpwm_timer_handle_t timer;
    mcpwm_oper_handle_t oper;
    mcpwm_cmpr_handle_t comparator;
    mcpwm_gen_handle_t generator;
};
