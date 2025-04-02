#pragma once

#include <cmath>

#include "lvgl.h"
#include "esp_lvgl_port.h"

#include "Page.hpp"
#include "ArousalMonitor.hpp"
#include "view.hpp"

#define GRAPH_AUTOSCALE INT32_MAX

class GraphPage : public Page
{
public:
    GraphPage(lv_display_t* disp, const char* name, uint32_t pointCount, int32_t rangeMin, int32_t rangeMax);
    void autoScaleChart();
    void addPoint(int32_t val);
    void setActive() override;

    lv_obj_t* nameLabel;
    lv_obj_t* valLabel;
    lv_obj_t* chart;
    lv_chart_series_t* series;
    uint32_t pointCount;
    int32_t rangeMin, rangeMax;
};
