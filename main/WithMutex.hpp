#pragma once

#include <functional>

#include "freertos/FreeRTOS.h"
#include "freertos/semphr.h"

#include "macroUtil.hpp"

class WithMutex
{
public:
    WithMutex() : mutex(xSemaphoreCreateMutex()) {};
    BaseType_t take(TickType_t delay = portMAX_DELAY) { return xSemaphoreTake(mutex, delay); };
    BaseType_t give() { return xSemaphoreGive(mutex); };

    // run a function (could be a lambda) while acquiring the mutex
    // automatically take and give (kinda like python with)
    void with(const std::function<void ()>& func, TickType_t delay = portMAX_DELAY)
    {
        take(delay);
        func();
        give();
    };
private:
    SemaphoreHandle_t mutex;
};
