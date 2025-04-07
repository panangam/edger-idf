#pragma once

#include <vector>

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "lvgl.h"

#include "eez_ui/screens.h"
#include "view.hpp"
#include "macroUtil.hpp"
#include "Page.hpp"
#include "../EdgingController.hpp"

class SettingsPage : public Page
{
public:
    SettingsPage(EdgingController& edgingController)
      : Page{objects.page_settings}, edgingController(edgingController) 
    {
        std::scoped_lock lock(lvglMutex);

        // register a flag for percent spinboxes
        lv_obj_add_flag(objects.settings_box__spinbox_motor_min_percent, LV_OBJ_FLAG_SPINBOX_PERCENT);
        lv_obj_add_flag(objects.settings_box__spinbox_motor_max_percent, LV_OBJ_FLAG_SPINBOX_PERCENT);
        lv_obj_add_flag(objects.settings_box__spinbox_motor_break_ratio_percent, LV_OBJ_FLAG_SPINBOX_PERCENT);
    
        // update spinbox values upon page load
        lv_obj_add_event_cb(screen, [](lv_event_t* e) {
            auto page = reinterpret_cast<SettingsPage*>(lv_event_get_user_data(e));
            page->lvUpdateSpinboxValues();
        }, LV_EVENT_SCREEN_LOAD_START, this);

        // update params when spinbox value changes
        for (const auto& [obj, param] : spinboxToParam)
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
    };
    
    void lvUpdateSpinboxValues()
    {
        for (const auto& [obj, param] : spinboxToParam)
        {
            if (lv_obj_has_flag(obj, LV_OBJ_FLAG_SPINBOX_PERCENT))
                lv_spinbox_set_value(obj, static_cast<int32_t>(*param * 100));
            else
                lv_spinbox_set_value(obj, static_cast<int32_t>(*param));
        }
    }

    EdgingController& edgingController;
    const std::vector<std::pair<lv_obj_t*, float*>> spinboxToParam{
        {objects.settings_box__spinbox_edging_max_arousal, &edgingController.settings.edgeArousal},
        {objects.settings_box__spinbox_cooldown_max_arousal, &edgingController.settings.cooldownArousalMax},
        {objects.settings_box__spinbox_cooldown_time, &edgingController.settings.cooldownTimeMin},
        {objects.settings_box__spinbox_motor_min_percent, &edgingController.settings.motorSpeedMin},
        {objects.settings_box__spinbox_motor_max_percent, &edgingController.settings.motorSpeedMax},
        {objects.settings_box__spinbox_motor_ramp_time, &edgingController.settings.rampUpTime},
        {objects.settings_box__spinbox_motor_plateau_time, &edgingController.settings.rampPlateauTime},
        {objects.settings_box__spinbox_motor_break_ratio_percent, &edgingController.settings.rampBreakRatio},
    };
};
