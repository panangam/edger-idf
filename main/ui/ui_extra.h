#ifndef UI_EXTRA_H
#define UI_EXTRA_H

#include "lvgl.h"

#include "eez_ui/screens.h"

#ifdef __cplusplus
extern "C" {
#endif

#define CHART_POINT_COUNT 127

void set_style_my_chart(lv_obj_t* chart)
{
    lv_chart_set_type(chart, LV_CHART_TYPE_LINE);
    lv_chart_set_div_line_count(chart, 0, 0);
    lv_obj_set_style_pad_all(chart, 0, LV_PART_MAIN);
    lv_obj_set_style_size(chart, 0, 0, LV_PART_INDICATOR);
    lv_obj_set_style_line_width(chart, 1, LV_PART_ITEMS);
    lv_chart_set_point_count(chart, CHART_POINT_COUNT);
}

#ifdef __cplusplus
}
#endif

#endif /*UI_EXTRA_H*/