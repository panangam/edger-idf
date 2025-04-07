#pragma once

#include <cmath>

#include "lvgl.h"
#include "esp_lvgl_port.h"

#include "Page.hpp"
#include "ArousalMonitor.hpp"
#include "view.hpp"

#define GRAPH_AUTOSCALE INT32_MAX
#define GRAPH_POINTS_COUNT 127

void lvSetStyleMyChart(lv_obj_t* chart);

class GraphPage : public Page
{
public:
    GraphPage(
        lv_obj_t* screen,
        lv_obj_t* valLabel, 
        lv_obj_t* chart,
        int32_t rangeMin,
        int32_t rangeMax
    );
    void lvLoadPage() override;
    void lvAutoScaleChart();
    void lvAddPoint(float val);

    lv_obj_t* valLabel;
    lv_obj_t* chart;
    lv_chart_series_t* series;
    int32_t rangeMin, rangeMax;
};
