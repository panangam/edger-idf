#pragma once

#include "driver/gpio.h"
#include "esp_log.h"

#define PIN_RF_SWITCH GPIO_NUM_3
#define PIN_ANTENNA_SELECT GPIO_NUM_14

inline void initXiaoESP32C6()
{
    // turn on RF switch
    gpio_reset_pin(PIN_RF_SWITCH);
    gpio_set_direction(PIN_RF_SWITCH, GPIO_MODE_OUTPUT);
    gpio_set_level(PIN_RF_SWITCH, 0);

    // choose internal antenna
    gpio_reset_pin(PIN_ANTENNA_SELECT);
    gpio_set_direction(PIN_ANTENNA_SELECT, GPIO_MODE_OUTPUT);
    gpio_set_level(PIN_ANTENNA_SELECT, 0);

    ESP_LOGI("xiao_exp32c6", "Xiao ESP32-C6 RF initialized");
}
