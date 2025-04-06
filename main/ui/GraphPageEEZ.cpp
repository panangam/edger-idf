#include <algorithm>
#include <mutex>

#include "lvgl.h"

#include "ui_extra.h"
#include "macroUtil.hpp"
#include "GraphPageEEZ.hpp"

GraphPageEEZ::GraphPageEEZ(
    lv_obj_t* screen, 
    lv_obj_t* valLabel, 
    lv_obj_t* chart,
    int32_t rangeMin, 
    int32_t rangeMax
) : screen(screen), valLabel(valLabel), chart(chart), rangeMin(rangeMin), rangeMax(rangeMax)
{
    if (rangeMin == GRAPH_AUTOSCALE) rangeMin = INT32_MAX;
    if (rangeMax == GRAPH_AUTOSCALE) rangeMax = INT32_MIN;

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

void GraphPageEEZ::addPoint(int32_t val)
{
    lv_chart_set_next_value(chart, series, val);
    autoScaleChart();
    lv_chart_refresh(chart);
    lv_label_set_text(valLabel, std::to_string(val).c_str());
}

void GraphPageEEZ::setActive()
{
    // for (size_t i = 0; i < pointCount; i++)
    // {
    //     lv_chart_set_next_value(chart, series, LV_CHART_POINT_NONE);
    // }
}