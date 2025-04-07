#pragma once

#include "GraphPageEEZ.hpp"

class PressurePageEEZ : public GraphPageEEZ
{
public:
    PressurePageEEZ(ArousalMonitor& arousalMonitor) 
      : GraphPageEEZ{
            objects.page_graph_pressure,
            objects.label_chart_value_pressure,
            objects.chart_pressure,
            GRAPH_AUTOSCALE, 
            GRAPH_AUTOSCALE,
        }, 
        arousalMonitor(arousalMonitor) {};

    void tick() {
        float newVal = arousalMonitor.getPressure();
        {
            std::scoped_lock lock(lvgl_mutex);
            addPoint(newVal);
        }
    };

    ArousalMonitor& arousalMonitor;
};
