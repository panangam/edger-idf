#include <algorithm>

#include "lvgl.h"

#include "Page.hpp"
#include "macroUtil.hpp"
#include "GraphPage.hpp"

GraphPage::GraphPage(
    lv_display_t* disp, 
    const char* name, 
    uint32_t pointCount, 
    int32_t rangeMin, 
    int32_t rangeMax
) : Page(disp), pointCount(pointCount), rangeMin{rangeMin}, rangeMax{rangeMax}
{
    if (rangeMin == GRAPH_AUTOSCALE) rangeMin = INT32_MAX;
    if (rangeMax == GRAPH_AUTOSCALE) rangeMax = INT32_MIN;

    withLVGL([&]() mutable {
        // name label
        nameLabel = lv_label_create(screen);
        lv_label_set_text(nameLabel, name);
        lv_obj_set_width(nameLabel, 64);
        lv_obj_align(nameLabel, LV_ALIGN_TOP_LEFT, 0, 2);
        lv_obj_set_style_text_font(nameLabel, &tamzen_12, 0);
        lv_obj_set_pos(nameLabel, 0, 2);

        // value label
        valLabel = lv_label_create(screen);
        lv_label_set_text(valLabel, "0");
        lv_obj_set_width(valLabel, 64);
        lv_obj_align(valLabel, LV_ALIGN_TOP_RIGHT, 0, 2);
        lv_obj_set_style_text_font(valLabel, &tamzen_12, 0);
        lv_obj_set_style_text_align(valLabel, LV_TEXT_ALIGN_RIGHT, 0);

        // graph
        chart = lv_chart_create(screen);
        lv_obj_set_size(chart, 128, 48);
        lv_obj_set_pos(chart, 0, 16);
        lv_chart_set_type(chart, LV_CHART_TYPE_LINE);
        lv_chart_set_div_line_count(chart, 0, 0);
        lv_obj_set_style_radius(chart, 0, LV_PART_INDICATOR);
        lv_obj_set_style_size(chart, 0, 0, LV_PART_INDICATOR);
        lv_obj_set_style_line_width(chart, 1, LV_PART_ITEMS);
        lv_obj_set_style_pad_all(chart, 0, LV_PART_MAIN);
        lv_chart_set_point_count(chart, pointCount);

        // data series
        series = lv_chart_add_series(chart, WHITE, LV_CHART_AXIS_PRIMARY_Y);
    });
}

void GraphPage::autoScaleChart()
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

void GraphPage::addPoint(int32_t val)
{
    lv_chart_set_next_value(chart, series, val);
    autoScaleChart();
    lv_chart_refresh(chart);
    lv_label_set_text(valLabel, std::to_string(val).c_str());
}
