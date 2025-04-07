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

class DashboardPageEEZ : public Page
{
public:
    DashboardPageEEZ(
        ArousalMonitor& arousalMonitor,
        EdgingController& edgingController
    ) : Page{objects.page_home},
        arousalMonitor(arousalMonitor), 
        edgingController(edgingController) 
    {};
    void tick() override
    {
        uint32_t numDenied = edgingController.numDenied;
        float arousal = arousalMonitor.getArousal();
        float speed = edgingController.speed;
        float maxArousal = edgingController.settings.edgeArousal;

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
    };

    static constexpr uint32_t BAR_RANGE = 50;

    ArousalMonitor& arousalMonitor;
    EdgingController& edgingController;
    lv_obj_t* labelNumDenied = objects.label_num_denied;
    lv_obj_t* barArousal = objects.bar_arousal;
    lv_obj_t* labelNumArousal = objects.label_bar_value_arousal;
    lv_obj_t* barMotor = objects.bar_motor;
    lv_obj_t* labelNumMotor = objects.label_bar_value_motor;
    lv_obj_t* spinboxMaxArousal = objects.spinbox_home_max_arousal;
    lv_obj_t* spinboxMaxMotor = objects.spinbox_home_max_motor;
};
