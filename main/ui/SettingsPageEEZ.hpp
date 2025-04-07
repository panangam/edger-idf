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

class SettingsPageEEZ : public Page
{
public:
    SettingsPageEEZ(EdgingController& edgingController)
      : Page{objects.page_settings}, edgingController(edgingController) {};
    // void tick() override { ESP_LOGI("SettingsPage", "tick"); };

    EdgingController& edgingController;
};
