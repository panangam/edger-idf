#pragma once

#include <mutex>

#include "GraphPage.hpp"

class PressurePage : public GraphPage
{
public:
    PressurePage(
        lv_display_t* disp, 
        ArousalMonitor& arousalMonitor, 
        uint32_t pointCount
    ) : GraphPage(disp, "Pressure", pointCount, GRAPH_AUTOSCALE, GRAPH_AUTOSCALE), 
        arousalMonitor(arousalMonitor) {};
    void tick();

    ArousalMonitor& arousalMonitor;
};

void PressurePage::tick()
{
    float newVal = arousalMonitor.getPressure();
    {
        std::scoped_lock lock(lvgl_mutex);
        addPoint(std::round(newVal));
    }
}
