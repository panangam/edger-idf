#pragma once

#include <cmath>

#include "lvgl.h"
#include "esp_lvgl_port.h"

#include "Page.hpp"
#include "ArousalMonitor.hpp"
#include "view.hpp"

#define GRAPH_AUTOSCALE INT32_MAX
#define GRAPH_POINTS_COUNT 127

void set_style_my_chart(lv_obj_t* chart);

class GraphPageEEZ : public Page
{
public:
    GraphPageEEZ(
        lv_obj_t* screen,
        lv_obj_t* valLabel, 
        lv_obj_t* chart,
        int32_t rangeMin,
        int32_t rangeMax
    );
    void loadPage() override;
    void autoScaleChart();
    void addPoint(int32_t val);

    lv_obj_t* valLabel;
    lv_obj_t* chart;
    lv_chart_series_t* series;
    int32_t rangeMin, rangeMax;
};
