#pragma once

#include <numeric>

#include "freertos/FreeRTOS.h"
#include "freertos/semphr.h"

#include "WithMutex.hpp"
#include "ADS1115.hpp"
#include "RingBuffer.hpp"

class ArousalMonitor : public WithMutex
{
public:
    ArousalMonitor(
        ADS1115 adc,
        float arousalDecayRate = 0.997,
        float sensitivityThreshold = 20,
        size_t pressureQueueSize = 20
    ) : adc{adc}, 
        pressureQueue{pressureQueueSize}, 
        arousalDecayRate{arousalDecayRate}, 
        sensitivityThreshold{sensitivityThreshold}
    {};

    float getPressure();
    float getArousal() { return arousal; };
    float getPreviousPressure() { return previousPressure; };
    
    void tick();

private:
    ADS1115 adc;
    float arousal = 0;
    RingBuffer<float> pressureQueue;
    float arousalDecayRate;
    float sensitivityThreshold;

    float previousPressure = 0;
    float peakStart = 0;
};
