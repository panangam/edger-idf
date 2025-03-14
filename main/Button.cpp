
#include <cstdint>

#include "iot_button.h"
#include "button_gpio.h"

#include "Button.hpp"

Button::Button(
    int32_t pinNum, 
    bool activeLevel, 
    uint16_t longPressTimeMS,
    uint16_t shortPressTimeMS,
    bool enablePowerSave, 
    bool disablePull
)
{
    button_gpio_config_t gpio_cfg = {
        .gpio_num = pinNum,
        .active_level = activeLevel,
        .enable_power_save = enablePowerSave,
        .disable_pull = disablePull,
    };
    button_config_t btn_cfg = {
        .long_press_time = longPressTimeMS,
        .short_press_time = shortPressTimeMS,
    };

    iot_button_new_gpio_device(&btn_cfg, &gpio_cfg, &this->buttonHandle);
}

Button::~Button()
{
    iot_button_delete(this->buttonHandle);
}

void Button::registerCallback(
    button_event_t event, 
    button_cb_t callback, 
    button_event_args_t eventArgs, 
    void* userData
)
{
    ESP_ERROR_CHECK(iot_button_register_cb(this->buttonHandle, event, &eventArgs, callback, userData));
}
