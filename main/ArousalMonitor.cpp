#include <numeric>

#include "freertos/FreeRTOS.h"
#include "freertos/semphr.h"
#include "esp_log.h"

#include "ADS1115.hpp"
#include "RingBuffer.hpp"

#include "ArousalMonitor.hpp"

float ArousalMonitor::getPressure()
{
    float avgPressure = (
        std::reduce(pressureQueue.begin(), pressureQueue.end()) 
        / pressureQueue.getSize()
    );
    return avgPressure;
}

void ArousalMonitor::tick()
{
    take();

    arousal *= arousalDecayRate;
    float newPressureReading = static_cast<float>(adc.readRawValue());
    pressureQueue.push(newPressureReading);
    float pressure = getPressure();

    if (pressure < previousPressure)
    {
        float peakSize = pressure - peakStart;
        if (peakSize >= sensitivityThreshold && peakSize < 10000)  // reject big spikes
        {
            arousal += pressure - peakStart;
        }
        peakStart = pressure;
    }

    previousPressure = pressure;

    give();
}