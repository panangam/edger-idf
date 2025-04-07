#pragma once

#include "GraphPageEEZ.hpp"

class PressurePageEEZ : public GraphPageEEZ
{
public:
    PressurePageEEZ(ArousalMonitor& arousalMonitor) 
      : GraphPageEEZ{
            objects.page_graph_pressure,
            objects.label_chart_value_arousal,
            objects.chart_arousal,
            GRAPH_AUTOSCALE, 
            GRAPH_AUTOSCALE,
        }, 
        arousalMonitor(arousalMonitor) {};

    void tick() {
        float newVal = arousalMonitor.getPressure();
        {
            std::scoped_lock lock(lvgl_mutex);
            addPoint(std::round(newVal));
        }
    };

    ArousalMonitor& arousalMonitor;
};
