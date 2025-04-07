#pragma once

#include <numeric>
#include <mutex>

#include "freertos/FreeRTOS.h"
#include "freertos/semphr.h"
#include "esp_timer.h"

#include "WithMutex.hpp"
#include "RingBuffer.hpp"
#include "device/ADS1115.hpp"

class ArousalMonitor : public WithMutex
{
public:
    ArousalMonitor(
        ADS1115 adc,
        float arousalDecayRate = 0.99,
        float sensitivityThreshold = 20,
        size_t pressureQueueSize = 20
    ) : adc{adc}, 
        pressureQueue{pressureQueueSize}, 
        arousalDecayRate{arousalDecayRate}, 
        sensitivityThreshold{sensitivityThreshold}
    {
        esp_timer_create_args_t timerArgs{
            .callback = [](void* arg) {
                auto arousalMonitor = reinterpret_cast<ArousalMonitor*>(arg);
                std::scoped_lock lock(arousalMonitor->arousalMutex);
                arousalMonitor->arousal *= arousalMonitor->arousalDecayRate;
            },
            .arg = this,
            .name = "arousalDecayTimer"
        };
        esp_timer_create(&timerArgs, &decayTimer);
        // decay 10 times per second
        esp_timer_start_periodic(decayTimer, 1'000'000 / 10);
    };

    float getPressure();
    float getArousal() { return arousal; };
    float getPreviousPressure() { return previousPressure; };
    
    void tick();

private:
    ADS1115 adc;
    float arousal = 0;
    std::mutex arousalMutex;
    RingBuffer<float> pressureQueue;
    float arousalDecayRate;
    float sensitivityThreshold;
    esp_timer_handle_t decayTimer;

    float previousPressure = 0;
    float peakStart = 0;
};
