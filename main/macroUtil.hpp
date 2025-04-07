#pragma once

#include <functional>

#include "freertos/FreeRTOS.h"
#include "esp_log.h"
#include "lvgl.h"
#include "esp_lvgl_port.h"


#define FREERTOS_ERROR_CHECK(x) do { \
    if ((x) != pdPASS) { \
        ESP_LOGE("FREERTOS_CHECK", "FreeRTOS error at %s:%d\n", __FILE__, __LINE__); \
        abort(); \
    } \
} while(0)

#define WITH_LVGL(code) do { \
    lvgl_port_lock(portMAX_DELAY); \
    code; \
    lvgl_port_unlock(); \
} while(0)

// run a function (could be lambda) while acquiring the lvgl port mutex
inline void withLVGL(const std::function<void ()>& func, TickType_t delay = portMAX_DELAY)
{
    if (lvgl_port_lock(delay))
    {
        func();
        lvgl_port_unlock();
    }
    else
    {
        ESP_LOGE("withLVGL", "could NOT acquire lvgl port mutex");
    }
};

struct LVGLMutex
{
    inline void lock() { lvgl_port_lock(portMAX_DELAY); };
    inline void unlock() { lvgl_port_unlock(); };
};
inline LVGLMutex lvglMutex;
