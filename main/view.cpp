#include <utility>
#include <cmath>

#include "esp_log.h"
#include "driver/i2c_master.h"
#include "esp_lcd_panel_ssd1306.h"
#include "esp_lcd_panel_io.h"
#include "esp_lcd_panel_ops.h"
#include "esp_lvgl_port.h"
#include "lvgl.h"

#include "view.hpp"

std::pair<esp_lcd_panel_io_handle_t, esp_lcd_panel_handle_t> initOLED(i2c_master_bus_handle_t i2c_bus)
{
    ESP_LOGI(TAG, "Install panel IO");
    esp_lcd_panel_io_handle_t io_handle = NULL;
    esp_lcd_panel_io_i2c_config_t io_config = {
        .dev_addr = SSD1306_I2C_ADDR,
        .control_phase_bytes = 1,               // According to SSD1306 datasheet
        .dc_bit_offset = 6,                     // According to SSD1306 datasheet
        .lcd_cmd_bits = 8,                      // According to SSD1306 datasheet
        .lcd_param_bits = 8,                    // According to SSD1306 datasheet
        .scl_speed_hz = SSD1306_I2C_HZ,
    };
    ESP_ERROR_CHECK(esp_lcd_new_panel_io_i2c(i2c_bus, &io_config, &io_handle));

    ESP_LOGI(TAG, "Install SSD1306 panel driver");
    esp_lcd_panel_handle_t panel_handle = NULL;
    esp_lcd_panel_dev_config_t panel_config = {
        .reset_gpio_num = -1,
        .bits_per_pixel = 1,
    };
    ESP_ERROR_CHECK(esp_lcd_new_panel_ssd1306(io_handle, &panel_config, &panel_handle));
    ESP_ERROR_CHECK(esp_lcd_panel_reset(panel_handle));
    ESP_ERROR_CHECK(esp_lcd_panel_init(panel_handle));
    ESP_ERROR_CHECK(esp_lcd_panel_disp_on_off(panel_handle, true));

    return std::make_pair(io_handle, panel_handle);
}

lv_display_t *initLVGL(esp_lcd_panel_io_handle_t io_handle, esp_lcd_panel_handle_t panel_handle)
{
    ESP_LOGI(TAG, "Initialize LVGL");
    const lvgl_port_cfg_t lvgl_cfg = ESP_LVGL_PORT_INIT_CONFIG();
    ESP_ERROR_CHECK(lvgl_port_init(&lvgl_cfg));

    const lvgl_port_display_cfg_t disp_cfg = {
        .io_handle = io_handle,
        .panel_handle = panel_handle,
        .buffer_size = OLED_H_RES * OLED_V_RES,
        .double_buffer = true,
        .hres = OLED_H_RES,
        .vres = OLED_V_RES,
        .monochrome = true,
        .rotation = {
            .swap_xy = false,
            .mirror_x = true,
            .mirror_y = true,
        }
    };
    lv_display_t *disp = lvgl_port_add_disp(&disp_cfg);
    lv_display_set_antialiasing(disp, false);

    return disp;
}

void graphUI(lv_display_t* disp)
{
    while (!lvgl_port_lock(0)) vTaskDelay(1);

    lv_obj_t *scr = lv_display_get_screen_active(disp);

    // label
    lv_obj_t *label = lv_label_create(scr);
    lv_label_set_text(label, "Arousal");
    lv_obj_set_width(label, lv_display_get_horizontal_resolution(disp));
    lv_obj_align(label, LV_ALIGN_TOP_LEFT, 0, 0);
    static lv_style_t lvStyle;
    lv_style_init(&lvStyle);
    lv_style_set_text_font(&lvStyle, &tamzen_12);
    lv_obj_add_style(label, &lvStyle, 0);
    lv_obj_set_pos(label, 0, 2);

    // graph
    lv_obj_t* chart = lv_chart_create(scr);
    lv_obj_set_size(chart, 128, 48);
    lv_obj_set_pos(chart, 0, 16);
    lv_chart_set_type(chart, LV_CHART_TYPE_LINE);
    lv_chart_set_div_line_count(chart, 0, 0);
    lv_obj_set_style_radius(chart, 0, LV_PART_INDICATOR);
    lv_obj_set_style_size(chart, 0, 0, LV_PART_INDICATOR);
    lv_obj_set_style_line_width(chart, 1, LV_PART_ITEMS);
    lv_obj_set_style_pad_all(chart, 0, LV_PART_MAIN);
    lv_chart_set_point_count(chart, 63);

    lv_chart_series_t* ser1 = lv_chart_add_series(chart, WHITE, LV_CHART_AXIS_PRIMARY_Y);
    // lv_chart_series_t * ser2 = lv_chart_add_series(chart, WHITE, LV_CHART_AXIS_SECONDARY_Y);
    int32_t* ser1_y_points = lv_chart_get_y_array(chart, ser1);

    uint32_t i;

    lvgl_port_unlock();

    for(i = 0;; i++) {
        while (!lvgl_port_lock(0)) vTaskDelay(1);
        /*Set the next points on 'ser1'*/
        lv_chart_set_next_value(chart, ser1, std::sin(i*3.14/20)*1000);
        int32_t min = ser1_y_points[0], max = ser1_y_points[0];
        for (int i = 1; i < 63; i++)
        {
            int32_t val = ser1_y_points[i];
            if (val == LV_CHART_POINT_NONE) continue;
            if (val < min) min = val;
            if (val > max) max = val;
        }
        lv_chart_set_range(chart, LV_CHART_AXIS_PRIMARY_Y, min, max);

        lv_chart_refresh(chart);
        lvgl_port_unlock();
        vTaskDelay(50);
    }
    lv_chart_refresh(chart); /*Required after direct set*/
}

