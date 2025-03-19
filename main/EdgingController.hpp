#pragma once

#include <algorithm>

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"

#include "WithMutex.hpp"
#include "ArousalMonitor.hpp"
#include "MotorController.hpp"

#define TAG "EdgingController"

struct EdgingSettings
{
    float edgeArousal = 100;
    float cooldownArousalMax = 100;
    float cooldownTimeMin = 10;  // seconds
    float rampUpTime = 60;  // seconds
    float rampPlateauTime = 30;  // seconds
    float rampBreakRatio = 0.5;
    float motorSpeedMin = 0.1;
    float motorSpeedMax = 0.7;
};

enum EdgingState_t
{
    EDGING_STATE_START = 0,
    EDGING_STATE_RAMPING,
    EDGING_STATE_COOLDOWN
};

TickType_t secToTick(float sec) { return pdMS_TO_TICKS(sec*1000); };
float tickToSec(TickType_t tick) { return static_cast<float>(pdTICKS_TO_MS(tick)) / 1000; };

class EdgingController : public WithMutex
{
public:
    EdgingController(
        ArousalMonitor& arousalMonitor, 
        MotorController& motorController,
        EdgingSettings& settings
    ) : arousalMonitor(arousalMonitor), 
        motorController(motorController),
        settings(settings)
    {};
    void setSpeed(float newSpeed);
    void tick();

    ArousalMonitor& arousalMonitor;
    MotorController& motorController;
    EdgingSettings& settings;
    EdgingState_t state = EDGING_STATE_START;
    TickType_t rampStartTime;

    float speed;
    uint32_t numDenied = 0;
};

void EdgingController::setSpeed(float newSpeed)
{
    speed = newSpeed;
    motorController.setSpeed(newSpeed);
}

void EdgingController::tick()
{
    float curArousal = arousalMonitor.getArousal();

    take();

    switch (state)
    {
    case EDGING_STATE_START:
        // start ramping up
        rampStartTime = xTaskGetTickCount();
        state = EDGING_STATE_RAMPING;
        ESP_LOGI(TAG, "Start edging state machine");
        break;
    case EDGING_STATE_RAMPING:
        if (curArousal < settings.edgeArousal)
        {
            // not at edge threshold yet; ramp up motor
            TickType_t curTime = xTaskGetTickCount();
            if ((curTime - rampStartTime) > secToTick(settings.rampUpTime + settings.rampPlateauTime))
            {
                // hit plateau time threshold
                rampStartTime = curTime - secToTick(settings.rampUpTime*settings.rampBreakRatio);
            }
            float newSpeed = std::min(
                (
                    tickToSec(curTime - rampStartTime) 
                    / settings.rampUpTime
                    * (settings.motorSpeedMax - settings.motorSpeedMin) 
                ) + settings.motorSpeedMin,
                settings.motorSpeedMax
            );
            setSpeed(newSpeed);
            // ESP_LOGI(TAG, "Ramping motor power to %.2f", newSpeed);
        }
        else
        {
            // edge
            ESP_LOGI(TAG, "Near orgasm detected, cooldown start");
            setSpeed(0);
            state = EDGING_STATE_COOLDOWN;
            numDenied++;
            give();  // unblock while pausing for break
            vTaskDelay(pdMS_TO_TICKS(settings.cooldownTimeMin * 1000));
            take();
        }
        break;
    case EDGING_STATE_COOLDOWN:
        // rest time delay must be over by now
        if (curArousal < settings.cooldownArousalMax)
        {
            ESP_LOGI(TAG, "Cooldown finish, continue ramping up");
            rampStartTime = xTaskGetTickCount();
            state = EDGING_STATE_RAMPING;
        }
        break;
    }

    give();
}
