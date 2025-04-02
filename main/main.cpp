#include <stdio.h>
#include <array>

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"
#include "esp_log.h"
#include "driver/i2c_master.h"
#include "iot_button.h"
#include "button_gpio.h"
#include "esp_lvgl_port.h"

#include "macroUtil.hpp"
#include "device/Rotary.hpp"
#include "device/Button.hpp"
#include "device/RotaryEncoderWithButton.hpp"
#include "device/ADS1115.hpp"
#include "ArousalMonitor.hpp"
#include "MotorController.hpp"
#include "EdgingController.hpp"

#include "ui/view.hpp"
#include "ui/ArousalPage.hpp"
#include "ui/PressurePage.hpp"
#include "ui/DashboardPage.hpp"

#include "ui/eez_ui/ui.h"

#define TAG "main.cpp"

#define PIN_ROTARY_CLK GPIO_NUM_20
#define PIN_ROTARY_DT GPIO_NUM_19
#define PIN_ROTARY_SW GPIO_NUM_18

#define PIN_OLED_SDA GPIO_NUM_5
#define PIN_OLED_SCL GPIO_NUM_6

#define PIN_MOTOR_PWM GPIO_NUM_21

#define KNOB_EVENT_QUEUE_LENGTH 16
#define GRAPH_POINTS_COUNT 127

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

void renderTaskFunc(void* appStatePtr);
void arousalTaskFunc(void* appStatePtr);
void edgingTaskFunc(void* appStatePtr);
static void renderTaskFuncEEZ(void* appStatePtr);

extern "C" void app_main(void)
{
    // register inputs
    Rotary knob(PIN_ROTARY_CLK, PIN_ROTARY_DT, KNOB_EVENT_QUEUE_LENGTH);

    uint32_t modeNum = 0;
    auto button_click_cb = [](void* btn_handle, void* usr_data)
    {
        ESP_LOGI("btn", "click");
        uint32_t* modeNum = reinterpret_cast<uint32_t*>(usr_data);
        *modeNum = (*modeNum+1) % MODE_COUNT;
    };
    auto button_long_press_cb = [](void* btn_handle, void* usr_data)
    {
        ESP_LOGI("btn", "long press");
    };
    Button knobButton{PIN_ROTARY_SW, 0};
    knobButton.registerCallback(BUTTON_SINGLE_CLICK, button_click_cb, {}, &modeNum);
    knobButton.registerCallback(BUTTON_LONG_PRESS_START, button_long_press_cb, {.long_press = 500});

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
    ArousalMonitor arousalMonitor{adc, 0.99, 20.0, 10};
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
    xTaskCreate(arousalTaskFunc, "arousalTask", 2048, &appState, 5, &adcTask);
    // xTaskCreate(renderTaskFunc, "renderTask", 4096, &appState, 7, &renderTask);
    xTaskCreate(renderTaskFuncEEZ, "renderTask", 4096, &appState, 7, &renderTask);
    xTaskCreate(edgingTaskFunc, "edgingTask", 2048, &appState, 7, &edgingTask);

    // do nothing forever
    for (;;) { vTaskDelay(portMAX_DELAY); }
}

void renderTaskFunc(void* appStatePtr)
{
    AppState& appState = *(reinterpret_cast<AppState*>(appStatePtr));

    auto [IOHandle, panelHandle] = initOLED(appState.i2cBus);
    lv_display_t* disp = initLVGL(IOHandle, panelHandle);
    ArousalPage arousalPage{disp, appState.arousalMonitor, GRAPH_POINTS_COUNT};
    PressurePage pressurePage{disp, appState.arousalMonitor, GRAPH_POINTS_COUNT};
    DashboardPage dashboardPage{disp, appState.arousalMonitor, appState.edgingController};

    std::array<Page*, 3> pages = {&dashboardPage, &arousalPage, &pressurePage};
    size_t curPageNum = 0;
    size_t prevPageNum = curPageNum;
    withLVGL([&]() {
        pages[curPageNum]->setActive();
    });

    TickType_t startTick;
    uint8_t rotaryEvent;

    ESP_LOGI("renderTaskFunc", "starting render loop");

    for (;;)
    {
        startTick = xTaskGetTickCount();
        while (xQueueReceive(appState.knob.eventQueue, &rotaryEvent, 0) == pdTRUE)
        {
            if (appState.modeNum == 0)
            {
                // detect rotary event
                if (rotaryEvent == DIR_CCW) 
                {
                    ESP_LOGI(TAG, "Got CCW");
                    curPageNum = (curPageNum + pages.size() - 1) % pages.size();
                }
                else if (rotaryEvent == DIR_CW) 
                {
                    ESP_LOGI(TAG, "Got CW");
                    curPageNum = (curPageNum + 1) % pages.size();
                }
                else ESP_LOGE("task render", "got non-cw and non-ccw rotary event: %d", rotaryEvent);
            
                if (curPageNum != prevPageNum)
                {
                    ESP_LOGI(TAG, "Page is changed to number %d", curPageNum);
                    withLVGL([&]() {
                        pages[curPageNum]->setActive();
                    });
                    prevPageNum = curPageNum;
                }
            }
            else
            {
                pages[curPageNum]->onEvent(rotaryEvent, appState.modeNum);
            }
        }

        pages[curPageNum]->tick();
        // HACK: flush every frame to circumvent dupont connection error which stops the app
        lvgl_port_flush_ready(disp);
        vTaskDelayUntil(&startTick, configTICK_RATE_HZ / 30);
    }
}

static void renderTaskFuncEEZ(void* appStatePtr)
{
    AppState& appState = *(reinterpret_cast<AppState*>(appStatePtr));

    auto [IOHandle, panelHandle] = initOLED(appState.i2cBus);
    lv_display_t* disp = initLVGL(IOHandle, panelHandle);
    ui_init();

    lv_indev_t * encoder = lv_indev_create();
    lv_indev_set_type(encoder, LV_INDEV_TYPE_ENCODER);
    lv_indev_set_mode(encoder, LV_INDEV_MODE_EVENT);
    lv_indev_set_driver_data(encoder, appStatePtr);

    struct TempEncoderData
    {
        int32_t encDiff;
        bool buttonIsDown;
    };

    auto encoderReadCB = [](lv_indev_t * indev, lv_indev_data_t * data) {
        AppState& appState = *(reinterpret_cast<AppState*>(lv_indev_get_driver_data(indev)));
    };
    lv_indev_set_read_cb(encoder, encoderReadCB);

    auto knobButtonCB = [](void *button_handle, void *encoder) {
        lv_indev_read((lv_indev_t*) encoder);
    };
    appState.knobButton.registerCallback(BUTTON_PRESS_DOWN, [](void *button_handle, void *encoder) {
        lv_indev_read((lv_indev_t*) encoder);
    }, {}, (void*) encoder);
    appState.knobButton.registerCallback(BUTTON_PRESS_UP, [](void *button_handle, void *encoder) {
        lv_indev_read((lv_indev_t*) encoder);
    }, {}, (void*) encoder);

    lv_screen_load(objects.page_settings);

    for (;;) { vTaskDelay(portMAX_DELAY); }
}

void arousalTaskFunc(void* appStatePtr)
{
    AppState& appState = *(reinterpret_cast<AppState*>(appStatePtr));
    ArousalMonitor& arousalMonitor = appState.arousalMonitor;

    ESP_LOGI("arousalTaskFunc", "starting arousal monitor loop");

    for (;;)
    {
        arousalMonitor.tick();
        // printf(">pressure:%f\n", arousalMonitor.getPressure());
        // printf(">arousal:%f\n", arousalMonitor.getArousal());
        vTaskDelay(1);
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
        vTaskDelay(1);
    }
}