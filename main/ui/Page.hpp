#pragma once

#include "lvgl.h"

class Page
{
public:
    Page(lv_obj_t* screen) : screen(screen) {};
    virtual void tick() = 0;
    virtual void loadPage() {
        lv_screen_load(screen);
    };

private:
    lv_obj_t* screen;
};
