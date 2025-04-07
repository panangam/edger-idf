#pragma once

#include "lvgl.h"

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
