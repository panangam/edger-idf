#pragma once

#include <cstdint>
#include <functional>

#include "driver/gpio.h"
#include "freertos/FreeRTOS.h"
#include "freertos/queue.h"

// Enable this to emit codes twice per step.
//#define HALF_STEP

// Values returned by 'process'
// No complete step yet.
#define DIR_NONE 0x0
// Clockwise step.
#define DIR_CW 0x10
// Anti-clockwise step.
#define DIR_CCW 0x20

class Rotary
{
public:
    Rotary(gpio_num_t pinClk, gpio_num_t pinDt, size_t eventQueueSize);
    QueueHandle_t eventQueue;
    void setCallbackCW(std::function<void(void)>&& f);
    void setCallbackCCW(std::function<void(void)>&& f);
private:
    uint8_t state;
    gpio_num_t pinClk;
    gpio_num_t pinDt;
    std::function<void(void)> callbackCW;
    std::function<void(void)> callbackCCW;
    
    void processPins();
    void registerInterrupts();
};
