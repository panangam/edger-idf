#pragma once

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "lvgl.h"

#include "Rotary.hpp"
#include "view.hpp"
#include "macroUtil.hpp"
#include "Page.hpp"
#include "ArousalMonitor.hpp"
#include "EdgingController.hpp"

#define TAG "DashboardPage"

class DashboardPage : public Page
{
public:
    DashboardPage(
        lv_display_t* disp,
        ArousalMonitor& arousalMonitor,
        EdgingController& edgingController
    );
    void tick() override;
    void onEvent(uint8_t event) override;

    static constexpr uint32_t BAR_RANGE = 100;

    ArousalMonitor& arousalMonitor;
    EdgingController& edgingController;
    lv_obj_t* bar, * label, * textLabel, * edgeLevelLabel;
};

DashboardPage::DashboardPage(
    lv_display_t* disp,
    ArousalMonitor& arousalMonitor,
    EdgingController& edgingController
) : Page(disp), 
    arousalMonitor(arousalMonitor), 
    edgingController(edgingController)
{
    static const uint32_t barWidth = 50;
    static const uint32_t barHeight = 12;

    withLVGL([&]() mutable {
        lv_obj_set_style_text_font(screen, &tamzen_12, 0);

        static lv_style_t style_bar_bg;
        lv_style_init(&style_bar_bg);
        lv_style_set_border_color(&style_bar_bg, WHITE);
        lv_style_set_border_width(&style_bar_bg, 1);
        lv_style_set_radius(&style_bar_bg, 0);

        static lv_style_t style_bar_indic;
        lv_style_init(&style_bar_indic);
        lv_style_set_bg_color(&style_bar_indic, WHITE);
        lv_style_set_radius(&style_bar_indic, 0);

        // bar
        bar = lv_bar_create(screen);
        lv_bar_set_orientation(bar, LV_BAR_ORIENTATION_HORIZONTAL);
        lv_bar_set_range(bar, 0, BAR_RANGE);
        lv_obj_align(bar, LV_ALIGN_TOP_LEFT, 0, 16);
        lv_obj_set_size(bar, barWidth, barHeight);
        lv_obj_add_style(bar, &style_bar_bg, 0);
        lv_obj_add_style(bar, &style_bar_indic, LV_PART_INDICATOR);
        lv_bar_set_value(bar, 0, LV_ANIM_OFF);

        // value label
        label = lv_label_create(screen);
        lv_obj_set_size(label, 20, barHeight);
        lv_obj_align(label, LV_ALIGN_TOP_LEFT, barWidth+2, 16);

        // text label
        textLabel = lv_label_create(screen);
        lv_obj_set_size(textLabel, 100, 12);
        lv_obj_set_pos(textLabel, 0, 30);
        lv_label_set_text(textLabel, "Max arousal:");

        // edge level label
        edgeLevelLabel = lv_label_create(screen);
        lv_obj_set_size(edgeLevelLabel, 20, 12);
        lv_obj_set_pos(edgeLevelLabel, 100, 30);
        lv_label_set_text(edgeLevelLabel, std::to_string(edgingController.settings.edgeArousal).c_str());
    });
}

void DashboardPage::tick()
{
    float speed;
    edgingController.with([&]() mutable {
        speed = edgingController.speed;
    });

    // ESP_LOGI(TAG, "speed %.2f", speed);

    withLVGL([&]() {
        lv_bar_set_value(bar, static_cast<int32_t>(speed * BAR_RANGE), LV_ANIM_OFF);
        lv_label_set_text(label, std::to_string((int32_t) std::floor(speed * 100)).c_str());
    });
}

void DashboardPage::onEvent(uint8_t event)
{
    if (event == DIR_CW)
    {
        int32_t temp;
        edgingController.with([&]() mutable {
            edgingController.settings.edgeArousal += 10;
            temp = edgingController.settings.edgeArousal;
        });
        withLVGL([&]() mutable {
            lv_label_set_text(edgeLevelLabel, std::to_string(temp).c_str());
        });
    }
    else if (event == DIR_CCW)
    {
        int32_t temp;
        edgingController.with([&]() mutable {
            edgingController.settings.edgeArousal -= 10;
            if (edgingController.settings.edgeArousal < 0)
            {
                edgingController.settings.edgeArousal = 0;
            }
            temp = edgingController.settings.edgeArousal;
        });
        withLVGL([&]() mutable {
            lv_label_set_text(edgeLevelLabel, std::to_string(temp).c_str());
        });
    }
}