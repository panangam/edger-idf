#pragma once

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
    void tick() override;

    ArousalMonitor& arousalMonitor;
};

void PressurePage::tick()
{
    float newVal;
    arousalMonitor.with([&]() mutable {
        newVal = arousalMonitor.getPressure();
    });

    withLVGL([&]() {
        addPoint(std::round(newVal));
    });
}
