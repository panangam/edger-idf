#pragma once

#include "lvgl.h"

#include "macroUtil.hpp"

class Page
{
public:
    Page(lv_display_t* disp) 
        : disp(disp), screen(lv_obj_create(NULL)) {};
    inline virtual void setActive() { lv_screen_load(screen); };
    virtual void tick() {};
    virtual void onEvent(uint8_t event) {};

    lv_display_t* disp;
    lv_obj_t* screen;
};
