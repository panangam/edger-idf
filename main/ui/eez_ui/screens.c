#include <string.h>

#include "screens.h"
#include "images.h"
#include "fonts.h"
#include "actions.h"
#include "vars.h"
#include "styles.h"
#include "ui.h"

#include <string.h>

groups_t groups;
static bool groups_created = false;

objects_t objects;
lv_obj_t *tick_value_change_obj;
uint32_t active_theme_index = 0;

static void event_handler_cb_page_home_page_home(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    if (event == LV_EVENT_SCREEN_LOAD_START) {
        // group: group_encoder
        lv_group_remove_all_objs(groups.group_encoder);
        lv_group_add_obj(groups.group_encoder, objects.title_home);
        lv_group_add_obj(groups.group_encoder, objects.spinbox_home_max_arousal);
        lv_group_add_obj(groups.group_encoder, objects.spinbox_home_max_motor);
    }
}

static void event_handler_cb_page_graph_arousal_page_graph_arousal(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    if (event == LV_EVENT_SCREEN_LOAD_START) {
        // group: group_encoder
        lv_group_remove_all_objs(groups.group_encoder);
        lv_group_add_obj(groups.group_encoder, objects.title_home_1);
    }
}

static void event_handler_cb_page_graph_pressure_page_graph_pressure(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    if (event == LV_EVENT_SCREEN_LOAD_START) {
        // group: group_encoder
        lv_group_remove_all_objs(groups.group_encoder);
        lv_group_add_obj(groups.group_encoder, objects.title_home_2);
    }
}

static void event_handler_cb_page_settings_page_settings(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    if (event == LV_EVENT_SCREEN_LOAD_START) {
        // group: group_encoder
        lv_group_remove_all_objs(groups.group_encoder);
        lv_group_add_obj(groups.group_encoder, objects.title);
        lv_group_add_obj(groups.group_encoder, objects.obj1__spinbox_max_arousal_7);
        lv_group_add_obj(groups.group_encoder, objects.obj1__spinbox_max_arousal_13);
        lv_group_add_obj(groups.group_encoder, objects.obj1__spinbox_max_arousal_14);
        lv_group_add_obj(groups.group_encoder, objects.obj1__spinbox_max_motor_1);
        lv_group_add_obj(groups.group_encoder, objects.obj1__spinbox_max_motor_2);
        lv_group_add_obj(groups.group_encoder, objects.obj1__spinbox_max_arousal_8);
        lv_group_add_obj(groups.group_encoder, objects.obj1__spinbox_max_arousal_9);
        lv_group_add_obj(groups.group_encoder, objects.obj1__spinbox_max_motor_3);
    }
}

void create_screen_page_home() {
    lv_obj_t *obj = lv_obj_create(0);
    objects.page_home = obj;
    lv_obj_set_pos(obj, 0, 0);
    lv_obj_set_size(obj, 128, 64);
    lv_obj_add_event_cb(obj, event_handler_cb_page_home_page_home, LV_EVENT_ALL, 0);
    add_style_style_page(obj);
    {
        lv_obj_t *parent_obj = obj;
        {
            // title_home
            lv_obj_t *obj = lv_obj_create(parent_obj);
            objects.title_home = obj;
            lv_obj_set_pos(obj, 0, 0);
            lv_obj_set_size(obj, 128, 16);
            lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_radius(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_add_event_cb(obj, action_change_page, LV_EVENT_KEY, (void *)0);
            add_style_style_title(obj);
            {
                lv_obj_t *parent_obj = obj;
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    lv_obj_set_pos(obj, 2, 2);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_label_set_text(obj, "Home");
                }
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    lv_obj_set_pos(obj, 55, 2);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_label_set_text(obj, "(Denied:   )");
                }
                {
                    // label_num_denied
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.label_num_denied = obj;
                    lv_obj_set_pos(obj, 104, 2);
                    lv_obj_set_size(obj, 18, LV_SIZE_CONTENT);
                    lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_RIGHT, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, "000");
                }
            }
        }
        {
            // row_bar_arousal
            lv_obj_t *obj = lv_obj_create(parent_obj);
            objects.row_bar_arousal = obj;
            lv_obj_set_pos(obj, 0, 16);
            lv_obj_set_size(obj, LV_PCT(100), 12);
            lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_radius(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            add_style_style_row_container(obj);
            lv_obj_set_style_layout(obj, LV_LAYOUT_FLEX, LV_PART_MAIN | LV_STATE_DEFAULT);
            {
                lv_obj_t *parent_obj = obj;
                {
                    // name_1
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.name_1 = obj;
                    lv_obj_set_pos(obj, 8, 32);
                    lv_obj_set_size(obj, 48, LV_PCT(100));
                    add_style_style_label(obj);
                    lv_label_set_text(obj, "Arousal:");
                }
                {
                    // bar_arousal
                    lv_obj_t *obj = lv_bar_create(parent_obj);
                    objects.bar_arousal = obj;
                    lv_obj_set_pos(obj, -49, -14);
                    lv_obj_set_size(obj, 50, 10);
                    lv_bar_set_range(obj, 0, 50);
                    lv_bar_set_value(obj, 25, LV_ANIM_OFF);
                    add_style_style_bar(obj);
                }
                {
                    // label_bar_value_arousal
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.label_bar_value_arousal = obj;
                    lv_obj_set_pos(obj, 8, 32);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_PCT(100));
                    add_style_style_label(obj);
                    lv_obj_set_style_flex_grow(obj, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_RIGHT, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, "50");
                }
            }
        }
        {
            // row_bar_motor
            lv_obj_t *obj = lv_obj_create(parent_obj);
            objects.row_bar_motor = obj;
            lv_obj_set_pos(obj, 0, 28);
            lv_obj_set_size(obj, LV_PCT(100), 12);
            lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_radius(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            add_style_style_row_container(obj);
            lv_obj_set_style_layout(obj, LV_LAYOUT_FLEX, LV_PART_MAIN | LV_STATE_DEFAULT);
            {
                lv_obj_t *parent_obj = obj;
                {
                    // name_2
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.name_2 = obj;
                    lv_obj_set_pos(obj, 8, 32);
                    lv_obj_set_size(obj, 48, LV_PCT(100));
                    add_style_style_label(obj);
                    lv_label_set_text(obj, "Motor:");
                }
                {
                    // bar_motor
                    lv_obj_t *obj = lv_bar_create(parent_obj);
                    objects.bar_motor = obj;
                    lv_obj_set_pos(obj, -49, -14);
                    lv_obj_set_size(obj, 50, 10);
                    lv_bar_set_range(obj, 0, 50);
                    lv_bar_set_value(obj, 25, LV_ANIM_OFF);
                    add_style_style_bar(obj);
                }
                {
                    // label_bar_value_motor
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.label_bar_value_motor = obj;
                    lv_obj_set_pos(obj, 8, 32);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_PCT(100));
                    add_style_style_label(obj);
                    lv_obj_set_style_flex_grow(obj, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_RIGHT, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, "50%");
                }
            }
        }
        {
            lv_obj_t *obj = lv_obj_create(parent_obj);
            lv_obj_set_pos(obj, 0, 40);
            lv_obj_set_size(obj, 128, 12);
            lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_radius(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            add_style_style_row_container_spinbox(obj);
            lv_obj_set_style_flex_main_place(obj, LV_FLEX_ALIGN_SPACE_BETWEEN, LV_PART_MAIN | LV_STATE_DEFAULT);
            {
                lv_obj_t *parent_obj = obj;
                {
                    // name_3
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.name_3 = obj;
                    lv_obj_set_pos(obj, 0, 0);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_PCT(100));
                    add_style_style_label(obj);
                    lv_label_set_text(obj, "Max Arousal:");
                }
                {
                    // spinbox_home_max_arousal
                    lv_obj_t *obj = lv_spinbox_create(parent_obj);
                    objects.spinbox_home_max_arousal = obj;
                    lv_obj_set_pos(obj, 0, 0);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_spinbox_set_digit_format(obj, 5, 0);
                    lv_spinbox_set_range(obj, 0, 99999);
                    lv_spinbox_set_rollover(obj, false);
                    lv_spinbox_set_step(obj, 10);
                    lv_spinbox_set_value(obj, 300);
                    add_style_style_spinbox(obj);
                }
            }
        }
        {
            lv_obj_t *obj = lv_obj_create(parent_obj);
            lv_obj_set_pos(obj, 0, 52);
            lv_obj_set_size(obj, 128, 12);
            lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_radius(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            add_style_style_row_container_spinbox(obj);
            lv_obj_set_style_flex_main_place(obj, LV_FLEX_ALIGN_SPACE_BETWEEN, LV_PART_MAIN | LV_STATE_DEFAULT);
            {
                lv_obj_t *parent_obj = obj;
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    lv_obj_set_pos(obj, 0, 0);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_PCT(100));
                    add_style_style_label(obj);
                    lv_label_set_text(obj, "Max Motor:");
                }
                {
                    lv_obj_t *obj = lv_obj_create(parent_obj);
                    lv_obj_set_pos(obj, -66, 16);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_PCT(100));
                    lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_radius(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_layout(obj, LV_LAYOUT_FLEX, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_column(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_row(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    {
                        lv_obj_t *parent_obj = obj;
                        {
                            // spinbox_home_max_motor
                            lv_obj_t *obj = lv_spinbox_create(parent_obj);
                            objects.spinbox_home_max_motor = obj;
                            lv_obj_set_pos(obj, 0, 0);
                            lv_obj_set_size(obj, 25, LV_SIZE_CONTENT);
                            lv_spinbox_set_digit_format(obj, 3, 0);
                            lv_spinbox_set_range(obj, 0, 100);
                            lv_spinbox_set_rollover(obj, false);
                            lv_spinbox_set_step(obj, 1);
                            lv_spinbox_set_value(obj, 50);
                            add_style_style_spinbox(obj);
                        }
                        {
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            objects.obj0 = obj;
                            lv_obj_set_pos(obj, 0, 100);
                            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                            lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[active_theme_index][0]), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_label_set_text(obj, "%");
                        }
                    }
                }
            }
        }
    }
    
    tick_screen_page_home();
}

void tick_screen_page_home() {
}

void create_screen_page_graph_arousal() {
    lv_obj_t *obj = lv_obj_create(0);
    objects.page_graph_arousal = obj;
    lv_obj_set_pos(obj, 0, 0);
    lv_obj_set_size(obj, 128, 64);
    lv_obj_add_event_cb(obj, event_handler_cb_page_graph_arousal_page_graph_arousal, LV_EVENT_ALL, 0);
    add_style_style_page(obj);
    {
        lv_obj_t *parent_obj = obj;
        {
            // title_home_1
            lv_obj_t *obj = lv_obj_create(parent_obj);
            objects.title_home_1 = obj;
            lv_obj_set_pos(obj, 0, 0);
            lv_obj_set_size(obj, 128, 16);
            lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_radius(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_add_event_cb(obj, action_change_page, LV_EVENT_KEY, (void *)0);
            add_style_style_title(obj);
            {
                lv_obj_t *parent_obj = obj;
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    lv_obj_set_pos(obj, 2, 2);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_label_set_text(obj, "Arousal");
                }
                {
                    // label_chart_value_arousal
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.label_chart_value_arousal = obj;
                    lv_obj_set_pos(obj, 96, 2);
                    lv_obj_set_size(obj, 30, LV_SIZE_CONTENT);
                    lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_RIGHT, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, "00000");
                }
            }
        }
        {
            // chart_arousal
            lv_obj_t *obj = lv_chart_create(parent_obj);
            objects.chart_arousal = obj;
            lv_obj_set_pos(obj, 0, 16);
            lv_obj_set_size(obj, 128, 48);
            add_style_style_chart(obj);
        }
    }
    
    tick_screen_page_graph_arousal();
}

void tick_screen_page_graph_arousal() {
}

void create_screen_page_graph_pressure() {
    lv_obj_t *obj = lv_obj_create(0);
    objects.page_graph_pressure = obj;
    lv_obj_set_pos(obj, 0, 0);
    lv_obj_set_size(obj, 128, 64);
    lv_obj_add_event_cb(obj, event_handler_cb_page_graph_pressure_page_graph_pressure, LV_EVENT_ALL, 0);
    add_style_style_page(obj);
    {
        lv_obj_t *parent_obj = obj;
        {
            // title_home_2
            lv_obj_t *obj = lv_obj_create(parent_obj);
            objects.title_home_2 = obj;
            lv_obj_set_pos(obj, 0, 0);
            lv_obj_set_size(obj, 128, 16);
            lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_radius(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_add_event_cb(obj, action_change_page, LV_EVENT_KEY, (void *)0);
            add_style_style_title(obj);
            {
                lv_obj_t *parent_obj = obj;
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    lv_obj_set_pos(obj, 2, 2);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_label_set_text(obj, "Pressure");
                }
                {
                    // label_chart_value_pressure
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.label_chart_value_pressure = obj;
                    lv_obj_set_pos(obj, 96, 2);
                    lv_obj_set_size(obj, 30, LV_SIZE_CONTENT);
                    lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_RIGHT, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, "00000");
                }
            }
        }
        {
            // chart_pressure
            lv_obj_t *obj = lv_chart_create(parent_obj);
            objects.chart_pressure = obj;
            lv_obj_set_pos(obj, 0, 16);
            lv_obj_set_size(obj, 128, 48);
            add_style_style_chart(obj);
        }
    }
    
    tick_screen_page_graph_pressure();
}

void tick_screen_page_graph_pressure() {
}

void create_screen_page_settings() {
    lv_obj_t *obj = lv_obj_create(0);
    objects.page_settings = obj;
    lv_obj_set_pos(obj, 0, 0);
    lv_obj_set_size(obj, 128, 64);
    lv_obj_add_event_cb(obj, event_handler_cb_page_settings_page_settings, LV_EVENT_ALL, 0);
    add_style_style_page(obj);
    {
        lv_obj_t *parent_obj = obj;
        {
            // title
            lv_obj_t *obj = lv_obj_create(parent_obj);
            objects.title = obj;
            lv_obj_set_pos(obj, 0, 0);
            lv_obj_set_size(obj, 128, 16);
            lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_radius(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_add_event_cb(obj, action_change_page, LV_EVENT_KEY, (void *)1);
            add_style_style_title(obj);
            {
                lv_obj_t *parent_obj = obj;
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    lv_obj_set_pos(obj, 2, 2);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_label_set_text(obj, "Settings");
                }
            }
        }
        {
            // scroll_area
            lv_obj_t *obj = lv_obj_create(parent_obj);
            objects.scroll_area = obj;
            lv_obj_set_pos(obj, 0, 16);
            lv_obj_set_size(obj, 128, 48);
            lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_radius(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE|LV_OBJ_FLAG_SCROLL_MOMENTUM);
            lv_obj_set_scrollbar_mode(obj, LV_SCROLLBAR_MODE_OFF);
            lv_obj_set_style_bg_color(obj, lv_color_hex(theme_colors[active_theme_index][0]), LV_PART_SCROLLBAR | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_opa(obj, 0, LV_PART_SCROLLBAR | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_top(obj, 0, LV_PART_SCROLLBAR | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_bottom(obj, 0, LV_PART_SCROLLBAR | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_left(obj, 0, LV_PART_SCROLLBAR | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_right(obj, 0, LV_PART_SCROLLBAR | LV_STATE_DEFAULT);
            lv_obj_set_style_radius(obj, 0, LV_PART_SCROLLBAR | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_opa(obj, 0, LV_PART_SCROLLBAR | LV_STATE_SCROLLED);
            lv_obj_set_style_anim_duration(obj, 0, LV_PART_MAIN | LV_STATE_SCROLLED);
            lv_obj_set_style_anim_duration(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            {
                lv_obj_t *parent_obj = obj;
                {
                    lv_obj_t *obj = lv_obj_create(parent_obj);
                    objects.obj1 = obj;
                    lv_obj_set_pos(obj, 0, 0);
                    lv_obj_set_size(obj, 128, 128);
                    lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    create_user_widget_settings_container(obj, 27);
                }
            }
        }
    }
    
    tick_screen_page_settings();
}

void tick_screen_page_settings() {
    tick_user_widget_settings_container(27);
}

void create_user_widget_row_bar(lv_obj_t *parent_obj, int startWidgetIndex) {
    (void)startWidgetIndex;
    lv_obj_t *obj = parent_obj;
    {
        lv_obj_t *parent_obj = obj;
        {
            // container
            lv_obj_t *obj = lv_obj_create(parent_obj);
            ((lv_obj_t **)&objects)[startWidgetIndex + 0] = obj;
            lv_obj_set_pos(obj, 0, 0);
            lv_obj_set_size(obj, LV_PCT(100), 12);
            lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_radius(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            add_style_style_row_container(obj);
            lv_obj_set_style_layout(obj, LV_LAYOUT_FLEX, LV_PART_MAIN | LV_STATE_DEFAULT);
            {
                lv_obj_t *parent_obj = obj;
                {
                    // name
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    ((lv_obj_t **)&objects)[startWidgetIndex + 1] = obj;
                    lv_obj_set_pos(obj, 8, 32);
                    lv_obj_set_size(obj, 48, LV_PCT(100));
                    add_style_style_label(obj);
                    lv_label_set_text(obj, "Name:");
                }
                {
                    // bar
                    lv_obj_t *obj = lv_bar_create(parent_obj);
                    ((lv_obj_t **)&objects)[startWidgetIndex + 2] = obj;
                    lv_obj_set_pos(obj, -49, -14);
                    lv_obj_set_size(obj, 50, 10);
                    lv_bar_set_range(obj, 0, 50);
                    lv_bar_set_value(obj, 25, LV_ANIM_OFF);
                    add_style_style_bar(obj);
                }
                {
                    // value
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    ((lv_obj_t **)&objects)[startWidgetIndex + 3] = obj;
                    lv_obj_set_pos(obj, 8, 32);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_PCT(100));
                    add_style_style_label(obj);
                    lv_obj_set_style_flex_grow(obj, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_RIGHT, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, "50%");
                }
            }
        }
    }
}

void tick_user_widget_row_bar(int startWidgetIndex) {
    (void)startWidgetIndex;
}

void create_user_widget_row_spinbox(lv_obj_t *parent_obj, int startWidgetIndex) {
    (void)startWidgetIndex;
    lv_obj_t *obj = parent_obj;
    {
        lv_obj_t *parent_obj = obj;
        {
            // name
            lv_obj_t *obj = lv_label_create(parent_obj);
            ((lv_obj_t **)&objects)[startWidgetIndex + 0] = obj;
            lv_obj_set_pos(obj, 0, 0);
            lv_obj_set_size(obj, 80, LV_PCT(100));
            add_style_style_label(obj);
            lv_label_set_text(obj, "Name:");
        }
        {
            // spinbox
            lv_obj_t *obj = lv_spinbox_create(parent_obj);
            ((lv_obj_t **)&objects)[startWidgetIndex + 1] = obj;
            lv_obj_set_pos(obj, 80, 0);
            lv_obj_set_size(obj, 48, LV_PCT(100));
            lv_spinbox_set_digit_format(obj, 3, 0);
            lv_spinbox_set_range(obj, 0, 999);
            lv_spinbox_set_rollover(obj, false);
            lv_spinbox_set_step(obj, 1);
            lv_spinbox_set_value(obj, 999);
            add_style_style_spinbox(obj);
        }
    }
}

void tick_user_widget_row_spinbox(int startWidgetIndex) {
    (void)startWidgetIndex;
}

void create_user_widget_settings_container(lv_obj_t *parent_obj, int startWidgetIndex) {
    (void)startWidgetIndex;
    lv_obj_t *obj = parent_obj;
    {
        lv_obj_t *parent_obj = obj;
        {
            lv_obj_t *obj = lv_obj_create(parent_obj);
            lv_obj_set_pos(obj, 0, 0);
            lv_obj_set_size(obj, LV_PCT(100), LV_PCT(100));
            lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_radius(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            add_style_style_container_master(obj);
            lv_obj_set_style_flex_flow(obj, LV_FLEX_FLOW_COLUMN, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_layout(obj, LV_LAYOUT_FLEX, LV_PART_MAIN | LV_STATE_DEFAULT);
            {
                lv_obj_t *parent_obj = obj;
                {
                    lv_obj_t *obj = lv_obj_create(parent_obj);
                    lv_obj_set_pos(obj, 0, 0);
                    lv_obj_set_size(obj, 128, 11);
                    lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_radius(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    add_style_style_row_container_spinbox(obj);
                    lv_obj_set_style_flex_main_place(obj, LV_FLEX_ALIGN_SPACE_BETWEEN, LV_PART_MAIN | LV_STATE_DEFAULT);
                    {
                        lv_obj_t *parent_obj = obj;
                        {
                            // name_10
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            ((lv_obj_t **)&objects)[startWidgetIndex + 0] = obj;
                            lv_obj_set_pos(obj, 0, 0);
                            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_PCT(100));
                            add_style_style_label(obj);
                            lv_label_set_text(obj, "EdgeMaxArsl:");
                        }
                        {
                            // spinbox_max_arousal_7
                            lv_obj_t *obj = lv_spinbox_create(parent_obj);
                            ((lv_obj_t **)&objects)[startWidgetIndex + 1] = obj;
                            lv_obj_set_pos(obj, 0, 0);
                            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                            lv_spinbox_set_digit_format(obj, 5, 0);
                            lv_spinbox_set_range(obj, 0, 99999);
                            lv_spinbox_set_rollover(obj, false);
                            lv_spinbox_set_step(obj, 10);
                            lv_spinbox_set_value(obj, 300);
                            add_style_style_spinbox(obj);
                        }
                    }
                }
                {
                    lv_obj_t *obj = lv_obj_create(parent_obj);
                    lv_obj_set_pos(obj, 0, 11);
                    lv_obj_set_size(obj, 128, 11);
                    lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_radius(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    add_style_style_row_container_spinbox(obj);
                    lv_obj_set_style_flex_main_place(obj, LV_FLEX_ALIGN_SPACE_BETWEEN, LV_PART_MAIN | LV_STATE_DEFAULT);
                    {
                        lv_obj_t *parent_obj = obj;
                        {
                            // name_11
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            ((lv_obj_t **)&objects)[startWidgetIndex + 2] = obj;
                            lv_obj_set_pos(obj, 0, 0);
                            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_PCT(100));
                            add_style_style_label(obj);
                            lv_label_set_text(obj, "CooldwnMaxArsl:");
                        }
                        {
                            // spinbox_max_arousal_13
                            lv_obj_t *obj = lv_spinbox_create(parent_obj);
                            ((lv_obj_t **)&objects)[startWidgetIndex + 3] = obj;
                            lv_obj_set_pos(obj, 0, 0);
                            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                            lv_spinbox_set_digit_format(obj, 5, 0);
                            lv_spinbox_set_range(obj, 0, 99999);
                            lv_spinbox_set_rollover(obj, false);
                            lv_spinbox_set_step(obj, 10);
                            lv_spinbox_set_value(obj, 300);
                            add_style_style_spinbox(obj);
                        }
                    }
                }
                {
                    lv_obj_t *obj = lv_obj_create(parent_obj);
                    lv_obj_set_pos(obj, 0, 22);
                    lv_obj_set_size(obj, 128, 11);
                    lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_radius(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    add_style_style_row_container_spinbox(obj);
                    lv_obj_set_style_flex_main_place(obj, LV_FLEX_ALIGN_SPACE_BETWEEN, LV_PART_MAIN | LV_STATE_DEFAULT);
                    {
                        lv_obj_t *parent_obj = obj;
                        {
                            // name_16
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            ((lv_obj_t **)&objects)[startWidgetIndex + 4] = obj;
                            lv_obj_set_pos(obj, 0, 0);
                            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_PCT(100));
                            add_style_style_label(obj);
                            lv_label_set_text(obj, "CooldwnTime:");
                        }
                        {
                            // spinbox_max_arousal_14
                            lv_obj_t *obj = lv_spinbox_create(parent_obj);
                            ((lv_obj_t **)&objects)[startWidgetIndex + 5] = obj;
                            lv_obj_set_pos(obj, 0, 0);
                            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                            lv_spinbox_set_digit_format(obj, 3, 0);
                            lv_spinbox_set_range(obj, 0, 999);
                            lv_spinbox_set_rollover(obj, false);
                            lv_spinbox_set_step(obj, 1);
                            lv_spinbox_set_value(obj, 5);
                            add_style_style_spinbox(obj);
                        }
                    }
                }
                {
                    lv_obj_t *obj = lv_obj_create(parent_obj);
                    lv_obj_set_pos(obj, 0, 66);
                    lv_obj_set_size(obj, 128, 11);
                    lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_radius(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    add_style_style_row_container_spinbox(obj);
                    lv_obj_set_style_flex_main_place(obj, LV_FLEX_ALIGN_SPACE_BETWEEN, LV_PART_MAIN | LV_STATE_DEFAULT);
                    {
                        lv_obj_t *parent_obj = obj;
                        {
                            // name_14
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            ((lv_obj_t **)&objects)[startWidgetIndex + 6] = obj;
                            lv_obj_set_pos(obj, 0, 0);
                            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_PCT(100));
                            add_style_style_label(obj);
                            lv_label_set_text(obj, "Motor min:");
                        }
                        {
                            lv_obj_t *obj = lv_obj_create(parent_obj);
                            lv_obj_set_pos(obj, -66, 16);
                            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_PCT(100));
                            lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_radius(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_layout(obj, LV_LAYOUT_FLEX, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_column(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_row(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            {
                                lv_obj_t *parent_obj = obj;
                                {
                                    // spinbox_max_motor_1
                                    lv_obj_t *obj = lv_spinbox_create(parent_obj);
                                    ((lv_obj_t **)&objects)[startWidgetIndex + 7] = obj;
                                    lv_obj_set_pos(obj, 0, 0);
                                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                                    lv_spinbox_set_digit_format(obj, 3, 0);
                                    lv_spinbox_set_range(obj, 0, 100);
                                    lv_spinbox_set_rollover(obj, false);
                                    lv_spinbox_set_step(obj, 1);
                                    lv_spinbox_set_value(obj, 50);
                                    add_style_style_spinbox(obj);
                                    lv_obj_set_style_max_width(obj, 25, LV_PART_MAIN | LV_STATE_DEFAULT);
                                }
                                {
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    lv_obj_set_pos(obj, 0, 100);
                                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                                    lv_label_set_text(obj, "%");
                                }
                            }
                        }
                    }
                }
                {
                    lv_obj_t *obj = lv_obj_create(parent_obj);
                    lv_obj_set_pos(obj, 0, 77);
                    lv_obj_set_size(obj, 128, 11);
                    lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_radius(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    add_style_style_row_container_spinbox(obj);
                    lv_obj_set_style_flex_main_place(obj, LV_FLEX_ALIGN_SPACE_BETWEEN, LV_PART_MAIN | LV_STATE_DEFAULT);
                    {
                        lv_obj_t *parent_obj = obj;
                        {
                            // name_15
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            ((lv_obj_t **)&objects)[startWidgetIndex + 8] = obj;
                            lv_obj_set_pos(obj, 0, 0);
                            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_PCT(100));
                            add_style_style_label(obj);
                            lv_label_set_text(obj, "Motor max:");
                        }
                        {
                            lv_obj_t *obj = lv_obj_create(parent_obj);
                            lv_obj_set_pos(obj, -66, 16);
                            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_PCT(100));
                            lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_radius(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_layout(obj, LV_LAYOUT_FLEX, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_column(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_row(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            {
                                lv_obj_t *parent_obj = obj;
                                {
                                    // spinbox_max_motor_2
                                    lv_obj_t *obj = lv_spinbox_create(parent_obj);
                                    ((lv_obj_t **)&objects)[startWidgetIndex + 9] = obj;
                                    lv_obj_set_pos(obj, 0, 0);
                                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                                    lv_spinbox_set_digit_format(obj, 3, 0);
                                    lv_spinbox_set_range(obj, 0, 100);
                                    lv_spinbox_set_rollover(obj, false);
                                    lv_spinbox_set_step(obj, 1);
                                    lv_spinbox_set_value(obj, 50);
                                    add_style_style_spinbox(obj);
                                    lv_obj_set_style_max_width(obj, 25, LV_PART_MAIN | LV_STATE_DEFAULT);
                                }
                                {
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    lv_obj_set_pos(obj, 0, 100);
                                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                                    lv_label_set_text(obj, "%");
                                }
                            }
                        }
                    }
                }
                {
                    lv_obj_t *obj = lv_obj_create(parent_obj);
                    lv_obj_set_pos(obj, 0, 33);
                    lv_obj_set_size(obj, 128, 11);
                    lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_radius(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    add_style_style_row_container_spinbox(obj);
                    lv_obj_set_style_flex_main_place(obj, LV_FLEX_ALIGN_SPACE_BETWEEN, LV_PART_MAIN | LV_STATE_DEFAULT);
                    {
                        lv_obj_t *parent_obj = obj;
                        {
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            lv_obj_set_pos(obj, 0, 0);
                            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_PCT(100));
                            add_style_style_label(obj);
                            lv_obj_set_style_text_font(obj, &ui_font_tamzen_12, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_label_set_text(obj, "MtrRampTime:");
                        }
                        {
                            // spinbox_max_arousal_8
                            lv_obj_t *obj = lv_spinbox_create(parent_obj);
                            ((lv_obj_t **)&objects)[startWidgetIndex + 10] = obj;
                            lv_obj_set_pos(obj, 0, 0);
                            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                            lv_spinbox_set_digit_format(obj, 3, 0);
                            lv_spinbox_set_range(obj, 0, 999);
                            lv_spinbox_set_rollover(obj, false);
                            lv_spinbox_set_step(obj, 1);
                            lv_spinbox_set_value(obj, 10);
                            add_style_style_spinbox(obj);
                        }
                    }
                }
                {
                    lv_obj_t *obj = lv_obj_create(parent_obj);
                    lv_obj_set_pos(obj, 0, 44);
                    lv_obj_set_size(obj, 128, 11);
                    lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_radius(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    add_style_style_row_container_spinbox(obj);
                    lv_obj_set_style_flex_main_place(obj, LV_FLEX_ALIGN_SPACE_BETWEEN, LV_PART_MAIN | LV_STATE_DEFAULT);
                    {
                        lv_obj_t *parent_obj = obj;
                        {
                            // name_12
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            ((lv_obj_t **)&objects)[startWidgetIndex + 11] = obj;
                            lv_obj_set_pos(obj, 0, 0);
                            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_PCT(100));
                            add_style_style_label(obj);
                            lv_label_set_text(obj, "MtrPlateauTime:");
                        }
                        {
                            // spinbox_max_arousal_9
                            lv_obj_t *obj = lv_spinbox_create(parent_obj);
                            ((lv_obj_t **)&objects)[startWidgetIndex + 12] = obj;
                            lv_obj_set_pos(obj, 0, 0);
                            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                            lv_spinbox_set_digit_format(obj, 3, 0);
                            lv_spinbox_set_range(obj, 0, 999);
                            lv_spinbox_set_rollover(obj, false);
                            lv_spinbox_set_step(obj, 1);
                            lv_spinbox_set_value(obj, 10);
                            add_style_style_spinbox(obj);
                        }
                    }
                }
                {
                    lv_obj_t *obj = lv_obj_create(parent_obj);
                    lv_obj_set_pos(obj, 0, 55);
                    lv_obj_set_size(obj, 128, 11);
                    lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_radius(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    add_style_style_row_container_spinbox(obj);
                    lv_obj_set_style_flex_main_place(obj, LV_FLEX_ALIGN_SPACE_BETWEEN, LV_PART_MAIN | LV_STATE_DEFAULT);
                    {
                        lv_obj_t *parent_obj = obj;
                        {
                            // name_13
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            ((lv_obj_t **)&objects)[startWidgetIndex + 13] = obj;
                            lv_obj_set_pos(obj, 0, 0);
                            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_PCT(100));
                            add_style_style_label(obj);
                            lv_label_set_text(obj, "MtrBreakRatio:");
                        }
                        {
                            lv_obj_t *obj = lv_obj_create(parent_obj);
                            lv_obj_set_pos(obj, -66, 16);
                            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_PCT(100));
                            lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_radius(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_layout(obj, LV_LAYOUT_FLEX, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_column(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_row(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            {
                                lv_obj_t *parent_obj = obj;
                                {
                                    // spinbox_max_motor_3
                                    lv_obj_t *obj = lv_spinbox_create(parent_obj);
                                    ((lv_obj_t **)&objects)[startWidgetIndex + 14] = obj;
                                    lv_obj_set_pos(obj, 0, 0);
                                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                                    lv_spinbox_set_digit_format(obj, 3, 0);
                                    lv_spinbox_set_range(obj, 0, 100);
                                    lv_spinbox_set_rollover(obj, false);
                                    lv_spinbox_set_step(obj, 1);
                                    lv_spinbox_set_value(obj, 50);
                                    add_style_style_spinbox(obj);
                                    lv_obj_set_style_max_width(obj, 25, LV_PART_MAIN | LV_STATE_DEFAULT);
                                }
                                {
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    lv_obj_set_pos(obj, 0, 100);
                                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                                    lv_label_set_text(obj, "%");
                                }
                            }
                        }
                    }
                }
            }
        }
    }
}

void tick_user_widget_settings_container(int startWidgetIndex) {
    (void)startWidgetIndex;
}

void change_color_theme(uint32_t theme_index) {
    active_theme_index = theme_index;
    
    lv_style_set_text_color(get_style_style_label_MAIN_DEFAULT(), lv_color_hex(theme_colors[theme_index][0]));
    
    lv_style_set_bg_color(get_style_style_bar_MAIN_DEFAULT(), lv_color_hex(theme_colors[theme_index][1]));
    
    lv_style_set_border_color(get_style_style_bar_MAIN_DEFAULT(), lv_color_hex(theme_colors[theme_index][0]));
    
    lv_style_set_bg_color(get_style_style_bar_INDICATOR_DEFAULT(), lv_color_hex(theme_colors[theme_index][0]));
    
    lv_style_set_text_color(get_style_style_spinbox_MAIN_DEFAULT(), lv_color_hex(theme_colors[theme_index][0]));
    
    lv_style_set_bg_color(get_style_style_spinbox_MAIN_DEFAULT(), lv_color_hex(theme_colors[theme_index][1]));
    
    lv_style_set_bg_color(get_style_style_spinbox_MAIN_EDITED(), lv_color_hex(theme_colors[theme_index][0]));
    
    lv_style_set_text_color(get_style_style_spinbox_MAIN_EDITED(), lv_color_hex(theme_colors[theme_index][1]));
    
    lv_style_set_outline_color(get_style_style_spinbox_MAIN_FOCUSED(), lv_color_hex(theme_colors[theme_index][0]));
    
    lv_style_set_outline_color(get_style_style_spinbox_MAIN_FOCUS_KEY(), lv_color_hex(theme_colors[theme_index][0]));
    
    lv_style_set_bg_color(get_style_style_spinbox_CURSOR_EDITED(), lv_color_hex(theme_colors[theme_index][1]));
    
    lv_style_set_text_color(get_style_style_spinbox_CURSOR_EDITED(), lv_color_hex(theme_colors[theme_index][0]));
    
    lv_style_set_text_color(get_style_style_spinbox_CURSOR_DEFAULT(), lv_color_hex(theme_colors[theme_index][0]));
    
    lv_style_set_text_color(get_style_style_page_MAIN_DEFAULT(), lv_color_hex(theme_colors[theme_index][0]));
    
    lv_style_set_bg_color(get_style_style_page_MAIN_DEFAULT(), lv_color_hex(theme_colors[theme_index][1]));
    
    lv_style_set_bg_color(get_style_style_page_MAIN_FOCUSED(), lv_color_hex(theme_colors[theme_index][0]));
    
    lv_style_set_text_color(get_style_style_page_MAIN_FOCUSED(), lv_color_hex(theme_colors[theme_index][1]));
    
    lv_style_set_bg_color(get_style_style_container_master_MAIN_DEFAULT(), lv_color_hex(theme_colors[theme_index][1]));
    
    lv_style_set_text_color(get_style_style_container_master_MAIN_DEFAULT(), lv_color_hex(theme_colors[theme_index][0]));
    
    lv_style_set_outline_color(get_style_style_title_MAIN_FOCUSED(), lv_color_hex(theme_colors[theme_index][0]));
    
    lv_style_set_bg_color(get_style_style_title_MAIN_EDITED(), lv_color_hex(theme_colors[theme_index][0]));
    
    lv_style_set_text_color(get_style_style_title_MAIN_EDITED(), lv_color_hex(theme_colors[theme_index][1]));
    
    lv_obj_set_style_text_color(objects.obj0, lv_color_hex(theme_colors[theme_index][0]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_bg_color(objects.scroll_area, lv_color_hex(theme_colors[theme_index][0]), LV_PART_SCROLLBAR | LV_STATE_DEFAULT);
    
    lv_obj_invalidate(objects.page_home);
    lv_obj_invalidate(objects.page_graph_arousal);
    lv_obj_invalidate(objects.page_graph_pressure);
    lv_obj_invalidate(objects.page_settings);
}

void ui_create_groups() {
    if (!groups_created) {
        groups.group_encoder = lv_group_create();
        groups_created = true;
    }
}

uint32_t theme_colors[1][2] = {
    { 0xff000000, 0xffffffff },
};


typedef void (*tick_screen_func_t)();
tick_screen_func_t tick_screen_funcs[] = {
    tick_screen_page_home,
    tick_screen_page_graph_arousal,
    tick_screen_page_graph_pressure,
    tick_screen_page_settings,
};
void tick_screen(int screen_index) {
    tick_screen_funcs[screen_index]();
}
void tick_screen_by_id(enum ScreensEnum screenId) {
    tick_screen_funcs[screenId - 1]();
}

void create_screens() {
    ui_create_groups();
    
    lv_disp_t *dispp = lv_disp_get_default();
    lv_theme_t *theme = lv_theme_default_init(dispp, lv_palette_main(LV_PALETTE_BLUE), lv_palette_main(LV_PALETTE_RED), false, LV_FONT_DEFAULT);
    lv_disp_set_theme(dispp, theme);
    
    create_screen_page_home();
    create_screen_page_graph_arousal();
    create_screen_page_graph_pressure();
    create_screen_page_settings();
}
