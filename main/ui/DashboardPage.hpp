#pragma once

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "lvgl.h"

#include "../device/Rotary.hpp"
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
    void onEvent(uint8_t event, uint32_t modeNum) override;

    static constexpr uint32_t BAR_RANGE = 50;

    ArousalMonitor& arousalMonitor;
    EdgingController& edgingController;
    lv_obj_t* labelNumDenied;
    lv_obj_t* barArousal;
    lv_obj_t* labelNumArousal;
    lv_obj_t* barMotor;
    lv_obj_t* labelNumMotor;
    lv_obj_t* labelNumMaxSpeed;
    lv_obj_t* labelNumMaxArousal;
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
    static const uint32_t rowHeight = 12;

    withLVGL([&]() mutable {
        static lv_style_t style_bar_bg;
        lv_style_init(&style_bar_bg);
        lv_style_set_border_color(&style_bar_bg, WHITE);
        lv_style_set_border_width(&style_bar_bg, 1);
        lv_style_set_radius(&style_bar_bg, 0);

        static lv_style_t style_bar_indic;
        lv_style_init(&style_bar_indic);
        lv_style_set_bg_color(&style_bar_indic, WHITE);
        lv_style_set_radius(&style_bar_indic, 0);

        // row
        auto createRow = [&](uint32_t y) {
            lv_obj_t* row = lv_obj_create(screen);
            lv_obj_remove_style_all(row);
            lv_obj_set_pos(row, 0, y);
            lv_obj_set_size(row, OLED_H_RES, rowHeight);
            lv_obj_set_flex_flow(row, LV_FLEX_FLOW_ROW);
            lv_obj_set_style_pad_column(row, 2, 0);
            return row;
        };

        lv_obj_t* row = createRow(5);

        static lv_style_t style_label;
        lv_style_init(&style_label);
        lv_style_set_text_font(&style_label, &tamzen_12);
        lv_style_set_height(&style_label, 12);

        auto createLabel = [&](lv_obj_t* parent, const char* text, int32_t w = LV_SIZE_CONTENT) {
            lv_obj_t* label = lv_label_create(parent);
            lv_obj_add_style(label, &style_label, 0);
            lv_label_set_text(label, text);
            lv_obj_set_width(label, w);
            return label;
        };
        lv_obj_t* labelTextDenied = createLabel(row, "# Denied:");

        labelNumDenied = createLabel(row, "0");

        lv_obj_t* row1 = createRow(16);
        // text label
        lv_obj_t* labelTextArousal = createLabel(row1, "Arousal:", 48);
        // bar
        auto createBar = [&](lv_obj_t* parent) {
            lv_obj_t* bar = lv_bar_create(parent);
            lv_bar_set_orientation(bar, LV_BAR_ORIENTATION_HORIZONTAL);
            lv_bar_set_range(bar, 0, BAR_RANGE);
            lv_obj_set_size(bar, barWidth, rowHeight-1);
            lv_obj_add_style(bar, &style_bar_bg, 0);
            lv_obj_add_style(bar, &style_bar_indic, LV_PART_INDICATOR);
            lv_bar_set_value(bar, 0, LV_ANIM_OFF);
            return bar;
        };
        barArousal = createBar(row1);
        // value label
        labelNumArousal = createLabel(row1, "0");

        lv_obj_t* row2 = createRow(28);
        // text label
        lv_obj_t* labelTextMotor = createLabel(row2, "Motor:", 48);
        // bar
        barMotor = createBar(row2);
        // value label
        labelNumMotor = createLabel(row2, "0%");

        lv_obj_t* row3 = createRow(40);
        lv_obj_t* labelTextMaxArousal = createLabel(row3, "Max arousal:", 72);
        labelNumMaxArousal = createLabel(row3, "");
       
        lv_obj_t* row4 = createRow(52);
        lv_obj_t* labelTextMaxSpeed = createLabel(row4, "Max Speed:", 72);
        labelNumMaxSpeed = createLabel(row4, "");
    });
}

void DashboardPage::tick()
{
    uint32_t numDenied = edgingController.numDenied;
    float arousal;
    arousalMonitor.with([&]() {
        arousal = arousalMonitor.getArousal();
    });
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

        lv_label_set_text_fmt(labelNumMaxArousal, "%ld", static_cast<int32_t>(maxArousal));
        lv_label_set_text_fmt(labelNumMaxSpeed, "%ld%%", static_cast<int32_t>(maxSpeed*100));
    });
}

void DashboardPage::onEvent(uint8_t event, uint32_t modeNum)
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