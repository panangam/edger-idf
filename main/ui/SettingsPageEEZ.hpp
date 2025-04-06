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

#define TAG "SettingsPage"

class SettingsPageEEZ
{
public:
    SettingsPageEEZ(EdgingController& edgingController)
      : edgingController(edgingController) {}
    void tick() override;
    void onEvent(uint8_t event, uint32_t modeNum) override;
    void loadPage() override;

    static constexpr uint32_t BAR_RANGE = 50;

    EdgingController& edgingController;
    lv_obt_t* screen = objects.page_settings;
};

void SettingsPageEEZ::tick()
{}

void SettingsPageEEZ::loadPage()
{
    // load page
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