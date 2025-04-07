#pragma once

#include <mutex>

#include "eez_ui/screens.h"

#include "GraphPage.hpp"

class ArousalPage : public GraphPage
{
public:
    ArousalPage(ArousalMonitor& arousalMonitor)
      : GraphPage(
            objects.page_graph_arousal,
            objects.label_chart_value_arousal,
            objects.chart_arousal,
            0, 
            300
        ), 
        arousalMonitor(arousalMonitor) {};

    void tick() {
        float newVal = arousalMonitor.getArousal();
        {
            std::scoped_lock lock(lvgl_mutex);
            addPoint(newVal);
        }
        // ESP_LOGI("ArousalPage", "arousal: %f", newVal);
    };

    ArousalMonitor& arousalMonitor;
};
