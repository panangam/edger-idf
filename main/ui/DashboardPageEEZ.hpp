#pragma once

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "lvgl.h"

#include "eez_ui/screens.h"
#include "view.hpp"
#include "macroUtil.hpp"
#include "Page.hpp"
#include "ArousalMonitor.hpp"
#include "EdgingController.hpp"

#define TAG "DashboardPage"

class DashboardPageEEZ{
public:
    DashboardPageEEZ(
        ArousalMonitor& arousalMonitor,
        EdgingController& edgingController
    );
    void tick();
    void onEvent(uint8_t event, uint32_t modeNum);
    void loadPage();

    static constexpr uint32_t BAR_RANGE = 50;

    ArousalMonitor& arousalMonitor;
    EdgingController& edgingController;
    lv_obj_t* labelNumDenied = objects.label_num_denied;
    lv_obj_t* barArousal = objects.bar_arousal;
    lv_obj_t* labelNumArousal = objects.label_bar_value_arousal;
    lv_obj_t* barMotor = objects.bar_motor;
    lv_obj_t* labelNumMotor = objects.label_bar_value_motor;
    lv_obj_t* spinboxMaxArousal;
    lv_obj_t* spinboxMaxMotor;
};

DashboardPageEEZ::DashboardPageEEZ(
    ArousalMonitor& arousalMonitor,
    EdgingController& edgingController
) : arousalMonitor(arousalMonitor), 
    edgingController(edgingController)
{};

void DashboardPageEEZ::tick()
{
    uint32_t numDenied = edgingController.numDenied;
    float arousal = arousalMonitor.getArousal();
    float speed = edgingController.speed;
    float maxArousal = edgingController.settings.edgeArousal;
    float maxSpeed = edgingController.settings.motorSpeedMax;

    // ESP_LOGI(TAG, "speed %.2f", speed);

    withLVGL([&]() {
        lv_label_set_text_fmt(labelNumDenied, "%lu", numDenied);
        
        lv_bar_set_value(barArousal, static_cast<int32_t>(arousal / maxArousal * BAR_RANGE), LV_ANIM_OFF);
        lv_label_set_text_fmt(labelNumArousal, "%ld", static_cast<int32_t>(arousal));

        lv_bar_set_value(barMotor, static_cast<int32_t>(speed * BAR_RANGE), LV_ANIM_OFF);
        lv_label_set_text_fmt(labelNumMotor, "%ld%%", static_cast<int32_t>(speed * 100));

        // lv_label_set_text_fmt(labelNumMaxArousal, "%ld", static_cast<int32_t>(maxArousal));
        // lv_label_set_text_fmt(labelNumMaxSpeed, "%ld%%", static_cast<int32_t>(maxSpeed*100));
    });
}

void DashboardPageEEZ::loadPage()
{
    // load page
}

void DashboardPageEEZ::onEvent(uint8_t event, uint32_t modeNum)
{
    if (event == DIR_CW)
    {
        int32_t temp;
        edgingController.with([&]() mutable {
            if (modeNum == 1)
                edgingController.settings.edgeArousal += 10;
            else if (modeNum == 2)
                edgingController.settings.motorSpeedMax += 0.01;
            // temp = edgingController.settings.edgeArousal;
        });
        // withLVGL([&]() {
        //     lv_label_set_text(labelNumMaxArousal, std::to_string(temp).c_str());
        // });
    }
    else if (event == DIR_CCW)
    {
        int32_t temp;
        edgingController.with([&]() mutable {
            if (modeNum == 1)
            {
                edgingController.settings.edgeArousal -= 10;
                if (edgingController.settings.edgeArousal < 0)
                    edgingController.settings.edgeArousal = 0;
            }
            else if (modeNum == 2)
            {
                edgingController.settings.motorSpeedMax -= 0.01;
                if (edgingController.settings.motorSpeedMax < 0)
                    edgingController.settings.motorSpeedMax = 0;
            }
            // temp = edgingController.settings.edgeArousal;
        });
        // withLVGL([&]() {
        //     lv_label_set_text(labelNumMaxArousal, std::to_string(temp).c_str());
        // });
    }
}