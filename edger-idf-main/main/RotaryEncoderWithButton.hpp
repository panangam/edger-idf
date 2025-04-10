#pragma once

#include <thread>
#include <atomic>
#include <mutex>

#include "driver/gpio.h"
#include "freertos/FreeRTOS.h"
#include "freertos/queue.h"

#include "macroUtil.hpp"

#include "device/Rotary.hpp"

enum RotaryEncoderWithButtonEvent
{
    ORAS_ENCODER_CCW,
    ORAS_ENCODER_CW,
    ORAS_ENCODER_PRESS,
    ORAS_ENCODER_RELEASE
};

class RotaryEncoderWithButtonIndev
{
public:
    RotaryEncoderWithButtonIndev(
        gpio_num_t pinClk,
        gpio_num_t pinDt,
        gpio_num_t pinSw,
        uint32_t swDebounceMS
    );

    lv_indev_t* indevPtr;
    Rotary rotary;
    Button button;

    std::atomic_int16_t tempEncDiff = 0;
    lv_indev_state_t tempButtonState = LV_INDEV_STATE_RELEASED;
};

RotaryEncoderWithButtonIndev::RotaryEncoderWithButtonIndev(
    gpio_num_t pinClk,
    gpio_num_t pinDt,
    gpio_num_t pinSw,
    uint32_t swDebounceMS
) : rotary(pinClk, pinDt, 0), button(pinSw, false, 200) {
    // create lvgl indev
    {
        std::scoped_lock lock(lvglMutex);
        indevPtr = lv_indev_create();
        lv_indev_set_type(indevPtr, LV_INDEV_TYPE_ENCODER);
        // lv_indev_set_mode(indevPtr, LV_INDEV_MODE_EVENT);
        lv_indev_set_long_press_time(indevPtr, 200);
        lv_indev_set_display(indevPtr, lv_display_get_default());
        lv_indev_set_driver_data(indevPtr, this);
        lv_indev_set_read_cb(indevPtr, [](lv_indev_t * indev, lv_indev_data_t * data) {
            auto encoder = (RotaryEncoderWithButtonIndev*) lv_indev_get_driver_data(indev);

            data->state = encoder->tempButtonState;
            data->enc_diff = encoder->tempEncDiff;
            encoder->tempEncDiff = 0;
        });
    }

    // register callbacks
    rotary.setCallbackCCW([&]() {
        tempEncDiff--;
    });
    rotary.setCallbackCW([&]() {
        tempEncDiff++;
    });
    button.registerCallback(BUTTON_PRESS_DOWN, [](void* button_handle, void* user_data) {
        auto encoder = (RotaryEncoderWithButtonIndev*) user_data;
        encoder->tempButtonState = LV_INDEV_STATE_PRESSED;
    }, {}, this);
    button.registerCallback(BUTTON_LONG_PRESS_START, [](void* button_handle, void* user_data) {
        auto encoder = (RotaryEncoderWithButtonIndev*) user_data;
        encoder->tempButtonState = LV_INDEV_STATE_PRESSED;
    }, {.long_press = 210}, this);
    button.registerCallback(BUTTON_PRESS_UP, [](void* button_handle, void* user_data) {
        auto encoder = (RotaryEncoderWithButtonIndev*) user_data;
        encoder->tempButtonState = LV_INDEV_STATE_RELEASED;
    }, {}, this);

}
