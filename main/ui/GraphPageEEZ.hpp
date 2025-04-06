#pragma once

#include <cmath>

#include "lvgl.h"
#include "esp_lvgl_port.h"

#include "Page.hpp"
#include "ArousalMonitor.hpp"
#include "view.hpp"

#define GRAPH_AUTOSCALE INT32_MAX

class GraphPageEEZ 
{
public:
    GraphPageEEZ(
        lv_obj_t* screen,
        lv_obj_t* valLabel, 
        lv_obj_t* chart,
        int32_t rangeMin, 
        int32_t rangeMax
    );
    void autoScaleChart();
    void addPoint(int32_t val);
    void setActive();

    lv_obj_t* screen;
    lv_obj_t* valLabel;
    lv_obj_t* chart;
    lv_chart_series_t* series;
    int32_t rangeMin, rangeMax;
};
