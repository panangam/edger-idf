/*
 * Rotary encoder library for Arduino.
 */

#ifndef rotary_h
#define rotary_h

#include <cstdint>

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
    Rotary(gpio_num_t pinClk, gpio_num_t pinDt, QueueHandle_t eventQueue);
private:
    unsigned char state;
    gpio_num_t pinClk;
    gpio_num_t pinDt;
    QueueHandle_t eventQueue;

    void interrupt();
    void registerInterrupts();
    void taskCode();
};

#endif
 
