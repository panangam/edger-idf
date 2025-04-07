#pragma once

#include "lvgl.h"

#define LV_OBJ_FLAG_SPINBOX_PERCENT LV_OBJ_FLAG_USER_1

class Page
{
public:
    Page(lv_obj_t* screen) : screen(screen) {};
    virtual void tick() {};
    virtual void lvLoadPage() {
        lv_screen_load(screen);
    };

protected:
    lv_obj_t* screen;
};
