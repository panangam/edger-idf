#include "styles.h"
#include "images.h"
#include "fonts.h"

#include "ui.h"
#include "screens.h"

//
// Style: style_label
//

void init_style_style_label_MAIN_DEFAULT(lv_style_t *style) {
    lv_style_set_text_color(style, lv_color_hex(theme_colors[active_theme_index][0]));
    lv_style_set_text_font(style, &ui_font_tamzen_12);
};

lv_style_t *get_style_style_label_MAIN_DEFAULT() {
    static lv_style_t *style;
    if (!style) {
        style = lv_malloc(sizeof(lv_style_t));
        lv_style_init(style);
        init_style_style_label_MAIN_DEFAULT(style);
    }
    return style;
};

void add_style_style_label(lv_obj_t *obj) {
    (void)obj;
    lv_obj_add_style(obj, get_style_style_label_MAIN_DEFAULT(), LV_PART_MAIN | LV_STATE_DEFAULT);
};

void remove_style_style_label(lv_obj_t *obj) {
    (void)obj;
    lv_obj_remove_style(obj, get_style_style_label_MAIN_DEFAULT(), LV_PART_MAIN | LV_STATE_DEFAULT);
};

//
// Style: style_bar
//

void init_style_style_bar_MAIN_DEFAULT(lv_style_t *style) {
    lv_style_set_bg_color(style, lv_color_hex(theme_colors[active_theme_index][1]));
    lv_style_set_border_color(style, lv_color_hex(theme_colors[active_theme_index][0]));
    lv_style_set_border_width(style, 1);
    lv_style_set_border_side(style, LV_BORDER_SIDE_FULL);
    lv_style_set_radius(style, 0);
};

lv_style_t *get_style_style_bar_MAIN_DEFAULT() {
    static lv_style_t *style;
    if (!style) {
        style = lv_malloc(sizeof(lv_style_t));
        lv_style_init(style);
        init_style_style_bar_MAIN_DEFAULT(style);
    }
    return style;
};

void init_style_style_bar_INDICATOR_DEFAULT(lv_style_t *style) {
    lv_style_set_bg_color(style, lv_color_hex(theme_colors[active_theme_index][0]));
    lv_style_set_radius(style, 0);
};

lv_style_t *get_style_style_bar_INDICATOR_DEFAULT() {
    static lv_style_t *style;
    if (!style) {
        style = lv_malloc(sizeof(lv_style_t));
        lv_style_init(style);
        init_style_style_bar_INDICATOR_DEFAULT(style);
    }
    return style;
};

void add_style_style_bar(lv_obj_t *obj) {
    (void)obj;
    lv_obj_add_style(obj, get_style_style_bar_MAIN_DEFAULT(), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_add_style(obj, get_style_style_bar_INDICATOR_DEFAULT(), LV_PART_INDICATOR | LV_STATE_DEFAULT);
};

void remove_style_style_bar(lv_obj_t *obj) {
    (void)obj;
    lv_obj_remove_style(obj, get_style_style_bar_MAIN_DEFAULT(), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_remove_style(obj, get_style_style_bar_INDICATOR_DEFAULT(), LV_PART_INDICATOR | LV_STATE_DEFAULT);
};

//
// Style: style_spinbox
//

void init_style_style_spinbox_MAIN_DEFAULT(lv_style_t *style) {
    lv_style_set_text_color(style, lv_color_hex(theme_colors[active_theme_index][0]));
    lv_style_set_bg_color(style, lv_color_hex(theme_colors[active_theme_index][1]));
    lv_style_set_pad_top(style, 0);
    lv_style_set_pad_bottom(style, 0);
    lv_style_set_pad_left(style, 0);
    lv_style_set_pad_right(style, 0);
    lv_style_set_text_font(style, &ui_font_tamzen_12);
    lv_style_set_radius(style, 0);
    lv_style_set_text_align(style, LV_TEXT_ALIGN_RIGHT);
    lv_style_set_pad_row(style, 0);
    lv_style_set_pad_column(style, 0);
    lv_style_set_max_width(style, 31);
    lv_style_set_border_width(style, 0);
};

lv_style_t *get_style_style_spinbox_MAIN_DEFAULT() {
    static lv_style_t *style;
    if (!style) {
        style = lv_malloc(sizeof(lv_style_t));
        lv_style_init(style);
        init_style_style_spinbox_MAIN_DEFAULT(style);
    }
    return style;
};

void init_style_style_spinbox_MAIN_EDITED(lv_style_t *style) {
    lv_style_set_outline_opa(style, 0);
    lv_style_set_bg_color(style, lv_color_hex(theme_colors[active_theme_index][0]));
    lv_style_set_text_color(style, lv_color_hex(theme_colors[active_theme_index][1]));
};

lv_style_t *get_style_style_spinbox_MAIN_EDITED() {
    static lv_style_t *style;
    if (!style) {
        style = lv_malloc(sizeof(lv_style_t));
        lv_style_init(style);
        init_style_style_spinbox_MAIN_EDITED(style);
    }
    return style;
};

void init_style_style_spinbox_MAIN_FOCUSED(lv_style_t *style) {
    lv_style_set_outline_width(style, 1);
    lv_style_set_outline_pad(style, -1);
    lv_style_set_outline_color(style, lv_color_hex(theme_colors[active_theme_index][0]));
};

lv_style_t *get_style_style_spinbox_MAIN_FOCUSED() {
    static lv_style_t *style;
    if (!style) {
        style = lv_malloc(sizeof(lv_style_t));
        lv_style_init(style);
        init_style_style_spinbox_MAIN_FOCUSED(style);
    }
    return style;
};

void init_style_style_spinbox_MAIN_FOCUS_KEY(lv_style_t *style) {
    lv_style_set_outline_width(style, 1);
    lv_style_set_outline_color(style, lv_color_hex(theme_colors[active_theme_index][0]));
    lv_style_set_outline_pad(style, -1);
};

lv_style_t *get_style_style_spinbox_MAIN_FOCUS_KEY() {
    static lv_style_t *style;
    if (!style) {
        style = lv_malloc(sizeof(lv_style_t));
        lv_style_init(style);
        init_style_style_spinbox_MAIN_FOCUS_KEY(style);
    }
    return style;
};

void init_style_style_spinbox_CURSOR_EDITED(lv_style_t *style) {
    lv_style_set_bg_opa(style, 255);
    lv_style_set_bg_color(style, lv_color_hex(theme_colors[active_theme_index][1]));
    lv_style_set_text_color(style, lv_color_hex(theme_colors[active_theme_index][0]));
    lv_style_set_pad_left(style, 1);
};

lv_style_t *get_style_style_spinbox_CURSOR_EDITED() {
    static lv_style_t *style;
    if (!style) {
        style = lv_malloc(sizeof(lv_style_t));
        lv_style_init(style);
        init_style_style_spinbox_CURSOR_EDITED(style);
    }
    return style;
};

void init_style_style_spinbox_CURSOR_DEFAULT(lv_style_t *style) {
    lv_style_set_text_color(style, lv_color_hex(theme_colors[active_theme_index][0]));
    lv_style_set_bg_opa(style, 0);
};

lv_style_t *get_style_style_spinbox_CURSOR_DEFAULT() {
    static lv_style_t *style;
    if (!style) {
        style = lv_malloc(sizeof(lv_style_t));
        lv_style_init(style);
        init_style_style_spinbox_CURSOR_DEFAULT(style);
    }
    return style;
};

void add_style_style_spinbox(lv_obj_t *obj) {
    (void)obj;
    lv_obj_add_style(obj, get_style_style_spinbox_MAIN_DEFAULT(), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_add_style(obj, get_style_style_spinbox_MAIN_EDITED(), LV_PART_MAIN | LV_STATE_EDITED);
    lv_obj_add_style(obj, get_style_style_spinbox_MAIN_FOCUSED(), LV_PART_MAIN | LV_STATE_FOCUSED);
    lv_obj_add_style(obj, get_style_style_spinbox_MAIN_FOCUS_KEY(), LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_add_style(obj, get_style_style_spinbox_CURSOR_EDITED(), LV_PART_CURSOR | LV_STATE_EDITED);
    lv_obj_add_style(obj, get_style_style_spinbox_CURSOR_DEFAULT(), LV_PART_CURSOR | LV_STATE_DEFAULT);
};

void remove_style_style_spinbox(lv_obj_t *obj) {
    (void)obj;
    lv_obj_remove_style(obj, get_style_style_spinbox_MAIN_DEFAULT(), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_remove_style(obj, get_style_style_spinbox_MAIN_EDITED(), LV_PART_MAIN | LV_STATE_EDITED);
    lv_obj_remove_style(obj, get_style_style_spinbox_MAIN_FOCUSED(), LV_PART_MAIN | LV_STATE_FOCUSED);
    lv_obj_remove_style(obj, get_style_style_spinbox_MAIN_FOCUS_KEY(), LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_remove_style(obj, get_style_style_spinbox_CURSOR_EDITED(), LV_PART_CURSOR | LV_STATE_EDITED);
    lv_obj_remove_style(obj, get_style_style_spinbox_CURSOR_DEFAULT(), LV_PART_CURSOR | LV_STATE_DEFAULT);
};

//
// Style: style_page
//

void init_style_style_page_MAIN_DEFAULT(lv_style_t *style) {
    lv_style_set_text_color(style, lv_color_hex(theme_colors[active_theme_index][0]));
    lv_style_set_text_font(style, &ui_font_tamzen_12);
    lv_style_set_bg_color(style, lv_color_hex(theme_colors[active_theme_index][1]));
    lv_style_set_bg_opa(style, 255);
};

lv_style_t *get_style_style_page_MAIN_DEFAULT() {
    static lv_style_t *style;
    if (!style) {
        style = lv_malloc(sizeof(lv_style_t));
        lv_style_init(style);
        init_style_style_page_MAIN_DEFAULT(style);
    }
    return style;
};

void init_style_style_page_MAIN_FOCUSED(lv_style_t *style) {
    lv_style_set_bg_color(style, lv_color_hex(theme_colors[active_theme_index][0]));
    lv_style_set_text_color(style, lv_color_hex(theme_colors[active_theme_index][1]));
    lv_style_set_bg_opa(style, 255);
};

lv_style_t *get_style_style_page_MAIN_FOCUSED() {
    static lv_style_t *style;
    if (!style) {
        style = lv_malloc(sizeof(lv_style_t));
        lv_style_init(style);
        init_style_style_page_MAIN_FOCUSED(style);
    }
    return style;
};

void add_style_style_page(lv_obj_t *obj) {
    (void)obj;
    lv_obj_add_style(obj, get_style_style_page_MAIN_DEFAULT(), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_add_style(obj, get_style_style_page_MAIN_FOCUSED(), LV_PART_MAIN | LV_STATE_FOCUSED);
};

void remove_style_style_page(lv_obj_t *obj) {
    (void)obj;
    lv_obj_remove_style(obj, get_style_style_page_MAIN_DEFAULT(), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_remove_style(obj, get_style_style_page_MAIN_FOCUSED(), LV_PART_MAIN | LV_STATE_FOCUSED);
};

//
// Style: style_container_master
//

void init_style_style_container_master_MAIN_DEFAULT(lv_style_t *style) {
    lv_style_set_bg_color(style, lv_color_hex(theme_colors[active_theme_index][1]));
    lv_style_set_text_color(style, lv_color_hex(theme_colors[active_theme_index][0]));
    lv_style_set_text_font(style, &ui_font_tamzen_12);
    lv_style_set_pad_row(style, 0);
    lv_style_set_bg_opa(style, 255);
    lv_style_set_pad_column(style, 0);
    lv_style_set_pad_right(style, 0);
    lv_style_set_pad_left(style, 0);
    lv_style_set_pad_bottom(style, 0);
    lv_style_set_pad_top(style, 0);
};

lv_style_t *get_style_style_container_master_MAIN_DEFAULT() {
    static lv_style_t *style;
    if (!style) {
        style = lv_malloc(sizeof(lv_style_t));
        lv_style_init(style);
        init_style_style_container_master_MAIN_DEFAULT(style);
    }
    return style;
};

void add_style_style_container_master(lv_obj_t *obj) {
    (void)obj;
    lv_obj_add_style(obj, get_style_style_container_master_MAIN_DEFAULT(), LV_PART_MAIN | LV_STATE_DEFAULT);
};

void remove_style_style_container_master(lv_obj_t *obj) {
    (void)obj;
    lv_obj_remove_style(obj, get_style_style_container_master_MAIN_DEFAULT(), LV_PART_MAIN | LV_STATE_DEFAULT);
};

//
// Style: style_title
//

void init_style_style_title_MAIN_FOCUSED(lv_style_t *style) {
    lv_style_set_outline_width(style, 1);
    lv_style_set_outline_color(style, lv_color_hex(theme_colors[active_theme_index][0]));
    lv_style_set_outline_pad(style, -1);
};

lv_style_t *get_style_style_title_MAIN_FOCUSED() {
    static lv_style_t *style;
    if (!style) {
        style = lv_malloc(sizeof(lv_style_t));
        lv_style_init(style);
        init_style_style_title_MAIN_FOCUSED(style);
    }
    return style;
};

void init_style_style_title_MAIN_EDITED(lv_style_t *style) {
    lv_style_set_bg_color(style, lv_color_hex(theme_colors[active_theme_index][0]));
    lv_style_set_bg_opa(style, 255);
    lv_style_set_text_color(style, lv_color_hex(theme_colors[active_theme_index][1]));
};

lv_style_t *get_style_style_title_MAIN_EDITED() {
    static lv_style_t *style;
    if (!style) {
        style = lv_malloc(sizeof(lv_style_t));
        lv_style_init(style);
        init_style_style_title_MAIN_EDITED(style);
    }
    return style;
};

void init_style_style_title_MAIN_DEFAULT(lv_style_t *style) {
    init_style_style_container_master_MAIN_DEFAULT(style);
    
};

lv_style_t *get_style_style_title_MAIN_DEFAULT() {
    static lv_style_t *style;
    if (!style) {
        style = lv_malloc(sizeof(lv_style_t));
        lv_style_init(style);
        init_style_style_title_MAIN_DEFAULT(style);
    }
    return style;
};

void add_style_style_title(lv_obj_t *obj) {
    (void)obj;
    lv_obj_add_style(obj, get_style_style_title_MAIN_FOCUSED(), LV_PART_MAIN | LV_STATE_FOCUSED);
    lv_obj_add_style(obj, get_style_style_title_MAIN_EDITED(), LV_PART_MAIN | LV_STATE_EDITED);
    lv_obj_add_style(obj, get_style_style_title_MAIN_DEFAULT(), LV_PART_MAIN | LV_STATE_DEFAULT);
};

void remove_style_style_title(lv_obj_t *obj) {
    (void)obj;
    lv_obj_remove_style(obj, get_style_style_title_MAIN_FOCUSED(), LV_PART_MAIN | LV_STATE_FOCUSED);
    lv_obj_remove_style(obj, get_style_style_title_MAIN_EDITED(), LV_PART_MAIN | LV_STATE_EDITED);
    lv_obj_remove_style(obj, get_style_style_title_MAIN_DEFAULT(), LV_PART_MAIN | LV_STATE_DEFAULT);
};

//
// Style: style_row_container
//

void init_style_style_row_container_MAIN_DEFAULT(lv_style_t *style) {
    init_style_style_container_master_MAIN_DEFAULT(style);
    
    lv_style_set_layout(style, LV_LAYOUT_FLEX);
    lv_style_set_pad_column(style, 2);
    lv_style_set_flex_cross_place(style, LV_FLEX_ALIGN_CENTER);
};

lv_style_t *get_style_style_row_container_MAIN_DEFAULT() {
    static lv_style_t *style;
    if (!style) {
        style = lv_malloc(sizeof(lv_style_t));
        lv_style_init(style);
        init_style_style_row_container_MAIN_DEFAULT(style);
    }
    return style;
};

void add_style_style_row_container(lv_obj_t *obj) {
    (void)obj;
    lv_obj_add_style(obj, get_style_style_row_container_MAIN_DEFAULT(), LV_PART_MAIN | LV_STATE_DEFAULT);
};

void remove_style_style_row_container(lv_obj_t *obj) {
    (void)obj;
    lv_obj_remove_style(obj, get_style_style_row_container_MAIN_DEFAULT(), LV_PART_MAIN | LV_STATE_DEFAULT);
};

//
// Style: style_row_container_spinbox
//

void init_style_style_row_container_spinbox_MAIN_DEFAULT(lv_style_t *style) {
    init_style_style_row_container_MAIN_DEFAULT(style);
    
};

lv_style_t *get_style_style_row_container_spinbox_MAIN_DEFAULT() {
    static lv_style_t *style;
    if (!style) {
        style = lv_malloc(sizeof(lv_style_t));
        lv_style_init(style);
        init_style_style_row_container_spinbox_MAIN_DEFAULT(style);
    }
    return style;
};

void add_style_style_row_container_spinbox(lv_obj_t *obj) {
    (void)obj;
    lv_obj_add_style(obj, get_style_style_row_container_spinbox_MAIN_DEFAULT(), LV_PART_MAIN | LV_STATE_DEFAULT);
};

void remove_style_style_row_container_spinbox(lv_obj_t *obj) {
    (void)obj;
    lv_obj_remove_style(obj, get_style_style_row_container_spinbox_MAIN_DEFAULT(), LV_PART_MAIN | LV_STATE_DEFAULT);
};

//
// Style: style_chart
//

void init_style_style_chart_MAIN_DEFAULT(lv_style_t *style) {
    lv_style_set_radius(style, 0);
    lv_style_set_border_width(style, 0);
    lv_style_set_pad_top(style, 0);
    lv_style_set_pad_bottom(style, 0);
    lv_style_set_pad_left(style, 0);
    lv_style_set_pad_right(style, 0);
    lv_style_set_pad_row(style, 0);
    lv_style_set_pad_column(style, 0);
};

lv_style_t *get_style_style_chart_MAIN_DEFAULT() {
    static lv_style_t *style;
    if (!style) {
        style = lv_malloc(sizeof(lv_style_t));
        lv_style_init(style);
        init_style_style_chart_MAIN_DEFAULT(style);
    }
    return style;
};

void add_style_style_chart(lv_obj_t *obj) {
    (void)obj;
    lv_obj_add_style(obj, get_style_style_chart_MAIN_DEFAULT(), LV_PART_MAIN | LV_STATE_DEFAULT);
};

void remove_style_style_chart(lv_obj_t *obj) {
    (void)obj;
    lv_obj_remove_style(obj, get_style_style_chart_MAIN_DEFAULT(), LV_PART_MAIN | LV_STATE_DEFAULT);
};

//
//
//

void add_style(lv_obj_t *obj, int32_t styleIndex) {
    typedef void (*AddStyleFunc)(lv_obj_t *obj);
    static const AddStyleFunc add_style_funcs[] = {
        add_style_style_label,
        add_style_style_bar,
        add_style_style_spinbox,
        add_style_style_page,
        add_style_style_container_master,
        add_style_style_title,
        add_style_style_row_container,
        add_style_style_row_container_spinbox,
        add_style_style_chart,
    };
    add_style_funcs[styleIndex](obj);
}

void remove_style(lv_obj_t *obj, int32_t styleIndex) {
    typedef void (*RemoveStyleFunc)(lv_obj_t *obj);
    static const RemoveStyleFunc remove_style_funcs[] = {
        remove_style_style_label,
        remove_style_style_bar,
        remove_style_style_spinbox,
        remove_style_style_page,
        remove_style_style_container_master,
        remove_style_style_title,
        remove_style_style_row_container,
        remove_style_style_row_container_spinbox,
        remove_style_style_chart,
    };
    remove_style_funcs[styleIndex](obj);
}

