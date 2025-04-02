#pragma once

#include "macroUtil.hpp"
#include "GraphPage.hpp"

class ArousalPage : public GraphPage
{
public:
    ArousalPage(
        lv_display_t* disp, 
        ArousalMonitor& arousalMonitor, 
        uint32_t pointCount
    ) : GraphPage(disp, "Arousal", pointCount, 0, 300), 
        arousalMonitor(arousalMonitor) {};
    void tick() override;

    ArousalMonitor& arousalMonitor;
};

void ArousalPage::tick()
{
    float newVal;
    arousalMonitor.with([&]() mutable {
        newVal = arousalMonitor.getArousal();
    });

    withLVGL([&]() {
        addPoint(std::round(newVal));
    });
}

