#include <array>

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"
#include "esp_event.h"
#include "esp_wifi.h"
#include "espnow.h"

#include "xiao_esp32c6_util.hpp"
#include "MotorController.hpp"

#define PIN_MOTOR_1 GPIO_NUM_21
#define PIN_MOTOR_2 GPIO_NUM_22
#define PIN_MOTOR_3 GPIO_NUM_23
#define PIN_MOTOR_4 GPIO_NUM_16

constexpr const char* TAG = "main";

static void app_wifi_init()
{
    esp_event_loop_create_default();

    wifi_init_config_t cfg = WIFI_INIT_CONFIG_DEFAULT();

    ESP_ERROR_CHECK(esp_wifi_init(&cfg));
    ESP_ERROR_CHECK(esp_wifi_set_mode(WIFI_MODE_STA));
    ESP_ERROR_CHECK(esp_wifi_set_storage(WIFI_STORAGE_RAM));
    ESP_ERROR_CHECK(esp_wifi_set_ps(WIFI_PS_NONE));
    ESP_ERROR_CHECK(esp_wifi_start());
}

extern "C" void app_main(void)
{
    // init xiao esp32c6 features
    initXiaoESP32C6();

    // initialize ESP-NOW and WiFi
    espnow_storage_init();
    app_wifi_init();
    espnow_config_t espnowConfig = ESPNOW_INIT_CONFIG_DEFAULT();
    espnow_init(&espnowConfig);

    // initialize motor controllers
    std::array<MotorController, 4> motors = {{
        {PIN_MOTOR_1, 0},
        {PIN_MOTOR_2, 0},
        {PIN_MOTOR_3, 1},
        {PIN_MOTOR_4, 1}
    }};
    for (const auto& m : motors)
    {
        ESP_LOGI(TAG, "Motor at pin %d initialized", m.pinPWM);
    }

    for (;;) { vTaskDelay(portMAX_DELAY); }
}
