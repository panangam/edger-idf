#pragma once

#include "driver/gpio.h"
#include "freertos/FreeRTOS.h"
#include "freertos/queue.h"

#include "Rotary.hpp"

class RotaryEncoderWithButton
{
public:
    RotaryEncoderWithButton(
        gpio_num_t pinClk,
        gpio_num_t pinDt,
        gpio_num_t pinSw,
        size_t rotaryEventQueueSize,
        uint32_t swDebounceMS
    ) : rotary(pinClk, pinDt, rotaryEventQueueSize), pinSw(pinSw) {};

    static lv_indev_t* createLVGLIndev();

    Rotary rotary;
    gpio_num_t pinSw;
};

lv_indev_t* RotaryEncoderWithButton::createLVGLIndev()
{
    lv_indev_t* encoder = lv_indev_create();
    return encoder;
}