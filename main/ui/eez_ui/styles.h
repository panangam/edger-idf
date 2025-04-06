#ifndef EEZ_LVGL_UI_STYLES_H
#define EEZ_LVGL_UI_STYLES_H

#include "lvgl.h"

#ifdef __cplusplus
extern "C" {
#endif

// Style: style_label
lv_style_t *get_style_style_label_MAIN_DEFAULT();
void add_style_style_label(lv_obj_t *obj);
void remove_style_style_label(lv_obj_t *obj);

// Style: style_bar
lv_style_t *get_style_style_bar_MAIN_DEFAULT();
lv_style_t *get_style_style_bar_INDICATOR_DEFAULT();
void add_style_style_bar(lv_obj_t *obj);
void remove_style_style_bar(lv_obj_t *obj);

// Style: style_spinbox
lv_style_t *get_style_style_spinbox_MAIN_DEFAULT();
lv_style_t *get_style_style_spinbox_MAIN_EDITED();
lv_style_t *get_style_style_spinbox_MAIN_FOCUSED();
lv_style_t *get_style_style_spinbox_MAIN_FOCUS_KEY();
lv_style_t *get_style_style_spinbox_CURSOR_EDITED();
lv_style_t *get_style_style_spinbox_CURSOR_DEFAULT();
void add_style_style_spinbox(lv_obj_t *obj);
void remove_style_style_spinbox(lv_obj_t *obj);

// Style: style_page
lv_style_t *get_style_style_page_MAIN_DEFAULT();
lv_style_t *get_style_style_page_MAIN_FOCUSED();
void add_style_style_page(lv_obj_t *obj);
void remove_style_style_page(lv_obj_t *obj);

// Style: style_container_master
lv_style_t *get_style_style_container_master_MAIN_DEFAULT();
void add_style_style_container_master(lv_obj_t *obj);
void remove_style_style_container_master(lv_obj_t *obj);

// Style: style_title
lv_style_t *get_style_style_title_MAIN_FOCUSED();
lv_style_t *get_style_style_title_MAIN_EDITED();
lv_style_t *get_style_style_title_MAIN_DEFAULT();
void add_style_style_title(lv_obj_t *obj);
void remove_style_style_title(lv_obj_t *obj);

// Style: style_row_container
lv_style_t *get_style_style_row_container_MAIN_DEFAULT();
void add_style_style_row_container(lv_obj_t *obj);
void remove_style_style_row_container(lv_obj_t *obj);

// Style: style_row_container_spinbox
lv_style_t *get_style_style_row_container_spinbox_MAIN_DEFAULT();
void add_style_style_row_container_spinbox(lv_obj_t *obj);
void remove_style_style_row_container_spinbox(lv_obj_t *obj);

// Style: style_chart
lv_style_t *get_style_style_chart_MAIN_DEFAULT();
void add_style_style_chart(lv_obj_t *obj);
void remove_style_style_chart(lv_obj_t *obj);



#ifdef __cplusplus
}
#endif

#endif /*EEZ_LVGL_UI_STYLES_H*/