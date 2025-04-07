#pragma once

#include <mutex>

#include "eez_ui/screens.h"

#include "GraphPageEEZ.hpp"

class ArousalPageEEZ : public GraphPageEEZ
{
public:
    ArousalPageEEZ(ArousalMonitor& arousalMonitor)
      : GraphPageEEZ(
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
            addPoint(std::round(newVal));
        }
        ESP_LOGI("ArousalPage", "arousal: %f", newVal);
    };

    ArousalMonitor& arousalMonitor;
};
