#ifndef EEZ_LVGL_UI_SCREENS_H
#define EEZ_LVGL_UI_SCREENS_H

#include "lvgl.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct _groups_t {
    lv_group_t *group_encoder;
} groups_t;

extern groups_t groups;

void ui_create_groups();

typedef struct _objects_t {
    lv_obj_t *page_home;
    lv_obj_t *page_graph_arousal;
    lv_obj_t *page_graph_pressure;
    lv_obj_t *page_settings;
    lv_obj_t *title_home;
    lv_obj_t *label_num_denied;
    lv_obj_t *row_bar_arousal;
    lv_obj_t *name_1;
    lv_obj_t *bar_arousal;
    lv_obj_t *label_bar_value_arousal;
    lv_obj_t *row_bar_motor;
    lv_obj_t *name_2;
    lv_obj_t *bar_motor;
    lv_obj_t *label_bar_value_motor;
    lv_obj_t *name_3;
    lv_obj_t *spinbox_home_max_arousal;
    lv_obj_t *spinbox_home_max_motor;
    lv_obj_t *obj0;
    lv_obj_t *title_home_1;
    lv_obj_t *label_chart_value_arousal;
    lv_obj_t *chart_arousal;
    lv_obj_t *title_home_2;
    lv_obj_t *label_chart_value_pressure;
    lv_obj_t *chart_pressure;
    lv_obj_t *title;
    lv_obj_t *scroll_area;
    lv_obj_t *obj1;
    lv_obj_t *obj1__name_10;
    lv_obj_t *obj1__spinbox_max_arousal_7;
    lv_obj_t *obj1__name_11;
    lv_obj_t *obj1__spinbox_max_arousal_13;
    lv_obj_t *obj1__name_16;
    lv_obj_t *obj1__spinbox_max_arousal_14;
    lv_obj_t *obj1__name_14;
    lv_obj_t *obj1__spinbox_max_motor_1;
    lv_obj_t *obj1__name_15;
    lv_obj_t *obj1__spinbox_max_motor_2;
    lv_obj_t *obj1__spinbox_max_arousal_8;
    lv_obj_t *obj1__name_12;
    lv_obj_t *obj1__spinbox_max_arousal_9;
    lv_obj_t *obj1__name_13;
    lv_obj_t *obj1__spinbox_max_motor_3;
} objects_t;

extern objects_t objects;

enum ScreensEnum {
    SCREEN_ID_PAGE_HOME = 1,
    SCREEN_ID_PAGE_GRAPH_AROUSAL = 2,
    SCREEN_ID_PAGE_GRAPH_PRESSURE = 3,
    SCREEN_ID_PAGE_SETTINGS = 4,
};

void create_screen_page_home();
void tick_screen_page_home();

void create_screen_page_graph_arousal();
void tick_screen_page_graph_arousal();

void create_screen_page_graph_pressure();
void tick_screen_page_graph_pressure();

void create_screen_page_settings();
void tick_screen_page_settings();

void create_user_widget_row_bar(lv_obj_t *parent_obj, int startWidgetIndex);
void tick_user_widget_row_bar(int startWidgetIndex);

void create_user_widget_row_spinbox(lv_obj_t *parent_obj, int startWidgetIndex);
void tick_user_widget_row_spinbox(int startWidgetIndex);

void create_user_widget_settings_container(lv_obj_t *parent_obj, int startWidgetIndex);
void tick_user_widget_settings_container(int startWidgetIndex);

enum Themes {
    THEME_ID_DEFAULT,
};
enum Colors {
    COLOR_ID_FG,
    COLOR_ID_BG,
};
void change_color_theme(uint32_t themeIndex);
extern uint32_t theme_colors[1][2];

void tick_screen_by_id(enum ScreensEnum screenId);
void tick_screen(int screen_index);

void create_screens();


extern uint32_t active_theme_index;
#ifdef __cplusplus
}
#endif

#endif /*EEZ_LVGL_UI_SCREENS_H*/