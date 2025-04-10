#pragma once

#include <utility>

#include "esp_lcd_io_i2c.h"
#include "lvgl.h"

#define SSD1306_I2C_ADDR 0x3C
#define SSD1306_I2C_HZ (400 * 1000)
#define OLED_H_RES 128
#define OLED_V_RES 64

LV_FONT_DECLARE(tamzen_12)
constexpr lv_color_t FG{1, 1, 1};
constexpr lv_color_t BG{0, 0, 0};

std::pair<esp_lcd_panel_io_handle_t, esp_lcd_panel_handle_t> initOLED(i2c_master_bus_handle_t i2c_bus);
lv_display_t *initLVGL(esp_lcd_panel_io_handle_t io_handle, esp_lcd_panel_handle_t panel_handle);

void graphUI(lv_display_t* disp);
