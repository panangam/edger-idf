#include <algorithm>
#include <mutex>

#include "lvgl.h"

#include "macroUtil.hpp"
#include "GraphPageEEZ.hpp"

#define GRAPH_SCALE_MULTIPLIER 1000

void set_style_my_chart(lv_obj_t* chart)
{
    lv_chart_set_type(chart, LV_CHART_TYPE_LINE);
    lv_chart_set_div_line_count(chart, 0, 0);
    lv_chart_set_point_count(chart, GRAPH_POINTS_COUNT);
    lv_obj_set_style_bg_opa(chart, 255, LV_PART_ITEMS);
    lv_obj_set_style_pad_all(chart, 0, LV_PART_MAIN);
    lv_obj_set_style_size(chart, 0, 0, LV_PART_INDICATOR);
    lv_obj_set_style_line_width(chart, 1, LV_PART_ITEMS);
}

GraphPageEEZ::GraphPageEEZ(
    lv_obj_t* screen, 
    lv_obj_t* valLabel, 
    lv_obj_t* chart,
    int32_t rangeMin, 
    int32_t rangeMax
) : Page{screen}, valLabel(valLabel), chart(chart), rangeMin(rangeMin), rangeMax(rangeMax)
{
    if (rangeMin == GRAPH_AUTOSCALE) rangeMin = INT32_MAX;
    else rangeMin = rangeMin * GRAPH_SCALE_MULTIPLIER;

    if (rangeMax == GRAPH_AUTOSCALE) rangeMax = INT32_MIN;
    else rangeMax = rangeMax * GRAPH_SCALE_MULTIPLIER;

    {
        std::scoped_lock lock(lvgl_mutex);
        set_style_my_chart(chart);
        series = lv_chart_add_series(chart, FG, LV_CHART_AXIS_PRIMARY_Y);
    }
}

void GraphPageEEZ::autoScaleChart()
{
    int32_t* seriesVals = lv_chart_get_y_array(chart, series);
    int32_t min = seriesVals[0], max = seriesVals[0];
    for (size_t i = 1; i < lv_chart_get_point_count(chart); i++)
    {
        int32_t val = seriesVals[i];
        if (val == LV_CHART_POINT_NONE) continue;
        else if (val < min) min = val;
        else if (val > max) max = val;
    }
    lv_chart_set_range(
        chart, 
        LV_CHART_AXIS_PRIMARY_Y, 
        rangeMin == GRAPH_AUTOSCALE ? min : std::min(min, rangeMin), 
        rangeMin == GRAPH_AUTOSCALE ? max : std::max(max, rangeMax)
    );
}

void GraphPageEEZ::addPoint(float val)
{
    lv_chart_set_next_value(chart, series, val*GRAPH_SCALE_MULTIPLIER);
    autoScaleChart();
    lv_chart_refresh(chart);
    lv_label_set_text(valLabel, std::to_string(static_cast<int32_t>(val)).c_str());
}

void GraphPageEEZ::loadPage()
{
    Page::loadPage();
    for (size_t i = 0; i < GRAPH_POINTS_COUNT; i++)
    {
        lv_chart_set_next_value(chart, series, LV_CHART_POINT_NONE);
    }
}