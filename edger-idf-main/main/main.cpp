#include <stdio.h>
#include <array>
#include <chrono>

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"
#include "esp_log.h"
#include "driver/i2c_master.h"
#include "iot_button.h"
#include "button_gpio.h"
#include "esp_lvgl_port.h"
#include "esp_timer.h"

#include "device/Rotary.hpp"
#include "device/Button.hpp"
#include "device/ADS1115.hpp"

#include "macroUtil.hpp"
#include "ArousalMonitor.hpp"
#include "MotorController.hpp"
#include "EdgingController.hpp"
#include "RotaryEncoderWithButton.hpp"

#include "ui/view.hpp"
#include "ui/ArousalPage.hpp"
#include "ui/PressurePage.hpp"
#include "ui/DashboardPage.hpp"
#include "ui/SettingsPage.hpp"
#include "ui/PagesManager.hpp"

#include "ui/eez_ui/ui.h"

constexpr const char* TAG = "main.cpp";

#define PIN_ROTARY_CLK GPIO_NUM_20
#define PIN_ROTARY_DT GPIO_NUM_19
#define PIN_ROTARY_SW GPIO_NUM_18

#define PIN_OLED_SDA GPIO_NUM_5
#define PIN_OLED_SCL GPIO_NUM_6

#define PIN_MOTOR_PWM GPIO_NUM_21

#define KNOB_EVENT_QUEUE_LENGTH 16
#define GRAPH_POINTS_COUNT 127

// LVGLMutex lvglMutex;

struct AppState
{
    i2c_master_bus_handle_t& i2cBus;
    ArousalMonitor& arousalMonitor;
    Rotary& knob;
    Button& knobButton;
    EdgingSettings& edgingSettings;
    EdgingController& edgingController;
    uint32_t& modeNum;
};

constexpr uint32_t MODE_COUNT = 3;

void arousalTaskFunc(void* appStatePtr);
void edgingTaskFunc(void* appStatePtr);
void renderTaskFuncEEZ(void* appStatePtr);

extern "C" void app_main(void)
{
    // register inputs
    Rotary knob(PIN_ROTARY_CLK, PIN_ROTARY_DT, KNOB_EVENT_QUEUE_LENGTH);

    uint32_t modeNum = 0;

    Button knobButton{PIN_ROTARY_SW, 0};

    // initialize i2c bus
    ESP_LOGI("main", "Initialize I2C bus");
    i2c_master_bus_handle_t i2cBus = NULL;
    i2c_master_bus_config_t bus_config_0 = {
        .i2c_port = -1,
        .sda_io_num = PIN_OLED_SDA,
        .scl_io_num = PIN_OLED_SCL,
        .clk_source = I2C_CLK_SRC_DEFAULT,
        .glitch_ignore_cnt = 7,
        .flags = {
            .enable_internal_pullup = true,
        },
    };
    ESP_ERROR_CHECK(i2c_new_master_bus(&bus_config_0, &i2cBus));

    // initialize shared resources
    ADS1115 adc{i2cBus};
    adc.config.gain = ADS1115_GAIN_2V048;
    adc.config.mux = ADS1115_MUX_0_GND;
    ArousalMonitor arousalMonitor{adc, 0.90, 20.0, 10};
    EdgingSettings edgingSettings{};
    MotorController motorController{PIN_MOTOR_PWM, 25000};
    EdgingController edgingController{
        arousalMonitor, 
        motorController, 
        edgingSettings
    };

    // construct app state (shared resources) container
    AppState appState{
        i2cBus,
        arousalMonitor,
        knob,
        knobButton,
        edgingSettings,
        edgingController,
        modeNum
    };

    // start tasks
    TaskHandle_t renderTask, adcTask, edgingTask;
    xTaskCreate(arousalTaskFunc, "arousalTask", 2048, &appState, 7, &adcTask);
    // xTaskCreate(renderTaskFunc, "renderTask", 4096, &appState, 7, &renderTask);
    xTaskCreate(renderTaskFuncEEZ, "renderTask", 4096, &appState, 7, &renderTask);
    xTaskCreate(edgingTaskFunc, "edgingTask", 2048, &appState, 7, &edgingTask);

    // do nothing forever
    for (;;) { vTaskDelay(portMAX_DELAY); }
}

void renderTaskFuncEEZ(void* appStatePtr)
{
    AppState& appState = *(reinterpret_cast<AppState*>(appStatePtr));

    auto [IOHandle, panelHandle] = initOLED(appState.i2cBus);
    lv_display_t* disp = initLVGL(IOHandle, panelHandle);
    {
        std::scoped_lock lock(lvglMutex);
        ui_init();
    }
    PagesManager pages{
        appState.arousalMonitor, 
        appState.edgingController
    };
    // register global pages manager pointer so plain c functions can access it
    global_pages_manager = &pages;
    RotaryEncoderWithButtonIndev encoder (PIN_ROTARY_CLK, PIN_ROTARY_DT, PIN_ROTARY_SW, 0);
    {
        std::scoped_lock lock(lvglMutex);
        lv_group_set_wrap(groups.group_encoder, false);
        lv_indev_set_group(encoder.indevPtr, groups.group_encoder);
    }
    
    esp_timer_handle_t tickTimer;
    esp_timer_create_args_t timerArgs = {
        .callback = [](void* arg) {
            auto pagesPtr = reinterpret_cast<PagesManager*>(arg);
            pagesPtr->tick();
        },
        .arg = global_pages_manager,
        .name = "tickTimer"
    };
    esp_timer_create(&timerArgs, &tickTimer);
    // tick page at 60Hz
    // esp_timer_start_periodic(tickTimer, 1000000 / 60);

    for (;;) { 
        pages.tick();
        // vTaskDelay(portMAX_DELAY); 
        vTaskDelay(pdMS_TO_TICKS(1000 / 30));
    }
}

void arousalTaskFunc(void* appStatePtr)
{
    AppState& appState = *(reinterpret_cast<AppState*>(appStatePtr));
    ArousalMonitor& arousalMonitor = appState.arousalMonitor;

    ESP_LOGI("arousalTaskFunc", "starting arousal monitor loop");

    esp_timer_handle_t arousalTimer;
    esp_timer_create_args_t timerArgs = {
        .callback = [](void* arg) {
            auto arousalMonitorPtr = reinterpret_cast<ArousalMonitor*>(arg);
            arousalMonitorPtr->tick();
        },
        .arg = &arousalMonitor,
        .name = "arousalTimer"
    };
    esp_timer_create(&timerArgs, &arousalTimer);
    // esp_timer_start_periodic(arousalTimer, 1000000 / 100);

    for (;;)
    {
        arousalMonitor.tick();
        // printf(">pressure:%f\n", arousalMonitor.getPressure());
        // printf(">arousal:%f\n", arousalMonitor.getArousal());
        // vTaskDelay(portMAX_DELAY);'
        vTaskDelay(pdMS_TO_TICKS(10));
    }
}

void edgingTaskFunc(void* appStatePtr)
{
    AppState& appState = *(reinterpret_cast<AppState*>(appStatePtr));
    EdgingController& edgingController = appState.edgingController;

    ESP_LOGI("edgingTaskFunc", "starting edging controller loop");

    for (;;)
    {
        edgingController.tick();
        vTaskDelay(pdMS_TO_TICKS(10));
    }
}