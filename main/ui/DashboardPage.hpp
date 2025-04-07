#pragma once

#include <map>

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "lvgl.h"

#include "eez_ui/screens.h"
#include "view.hpp"
#include "macroUtil.hpp"
#include "Page.hpp"
#include "ArousalMonitor.hpp"
#include "EdgingController.hpp"

class DashboardPage : public Page
{
public:
    DashboardPage(
        ArousalMonitor& arousalMonitor,
        EdgingController& edgingController
    ) : Page{objects.page_home},
        arousalMonitor(arousalMonitor), 
        edgingController(edgingController) 
    {
        {
            std::scoped_lock lock(lvglMutex);

            // register a flag for percent spinboxes
            lv_obj_add_flag(objects.spinbox_home_max_motor, LV_OBJ_FLAG_SPINBOX_PERCENT);

            // update spinbox values upon page load
            lv_obj_add_event_cb(screen, [](lv_event_t* e) {
                auto page = reinterpret_cast<DashboardPage*>(lv_event_get_user_data(e));
                page->lvUpdateSpinboxValues();
            }, LV_EVENT_SCREEN_LOAD_START, this);

            // update params when spinbox value changes
            for (const auto [obj, param] : spinboxToParam)
            {
                lv_obj_add_event_cb(obj, [](lv_event_t* e) {
                    auto param = reinterpret_cast<float*>(lv_event_get_user_data(e));
                    lv_obj_t* obj = lv_event_get_target_obj(e);
                    int32_t val = lv_spinbox_get_value(obj);
                    if (lv_obj_has_flag(obj, LV_OBJ_FLAG_SPINBOX_PERCENT))
                        *param = static_cast<float>(val) / 100;
                    else
                        *param = static_cast<float>(val);
                }, LV_EVENT_VALUE_CHANGED, param);
            }
        }
    };
    void tick() override
    {
        uint32_t numDenied = edgingController.numDenied;
        float arousal = arousalMonitor.getArousal();
        float speed = edgingController.speed;
        float maxArousal = edgingController.settings.edgeArousal;

        // ESP_LOGI(TAG, "speed %.2f", speed);

        {
            std::scoped_lock lock(lvglMutex);
            lv_label_set_text_fmt(labelNumDenied, "%lu", numDenied);
            
            lv_bar_set_value(barArousal, static_cast<int32_t>(arousal / maxArousal * BAR_RANGE), LV_ANIM_OFF);
            lv_label_set_text_fmt(labelNumArousal, "%ld", static_cast<int32_t>(arousal));

            lv_bar_set_value(barMotor, static_cast<int32_t>(speed * BAR_RANGE), LV_ANIM_OFF);
            lv_label_set_text_fmt(labelNumMotor, "%ld%%", static_cast<int32_t>(speed * 100));

            // lv_label_set_text_fmt(labelNumMaxArousal, "%ld", static_cast<int32_t>(maxArousal));
            // lv_label_set_text_fmt(labelNumMaxSpeed, "%ld%%", static_cast<int32_t>(maxSpeed*100));
        }
    };
    void lvUpdateSpinboxValues()
    {
        for (const auto [obj, param] : spinboxToParam)
        {
            if (lv_obj_has_flag(obj, LV_OBJ_FLAG_SPINBOX_PERCENT))
                lv_spinbox_set_value(obj, static_cast<int32_t>(*param * 100));
            else
                lv_spinbox_set_value(obj, static_cast<int32_t>(*param));
        }    
    }

    static constexpr uint32_t BAR_RANGE = 50;

    ArousalMonitor& arousalMonitor;
    EdgingController& edgingController;
    lv_obj_t* labelNumDenied = objects.label_num_denied;
    lv_obj_t* barArousal = objects.bar_arousal;
    lv_obj_t* labelNumArousal = objects.label_bar_value_arousal;
    lv_obj_t* barMotor = objects.bar_motor;
    lv_obj_t* labelNumMotor = objects.label_bar_value_motor;

    const std::map<lv_obj_t*, float*> spinboxToParam{
        {objects.spinbox_home_max_arousal, &edgingController.settings.edgeArousal},
        {objects.spinbox_home_max_motor, &edgingController.settings.motorSpeedMax},
    };
};
