#pragma once

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
      : Page{objects.page_settings}, edgingController(edgingController) {};
    // void tick() override { ESP_LOGI("SettingsPage", "tick"); };

    EdgingController& edgingController;
};
