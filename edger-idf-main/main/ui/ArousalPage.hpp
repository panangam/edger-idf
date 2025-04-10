#pragma once

#include <mutex>

#include "eez_ui/screens.h"

#include "macroUtil.hpp"
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

    void tick() override {
        float newVal = arousalMonitor.getArousal();

        std::scoped_lock lock(lvglMutex);
        lvAddPoint(newVal);
    };

    ArousalMonitor& arousalMonitor;
};
