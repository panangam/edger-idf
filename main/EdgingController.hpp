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
    float edgeArousal = 300;
    float restArousalMax = 100;
    float restTimeMin = 10;  // seconds
    float rampUpTime = 60;  // seconds
    float motorSpeedMin = 0.2;
    float motorSpeedMax = 1.0;
};

enum EdgingState_t
{
    EDGING_STATE_START = 0,
    EDGING_STATE_RAMPING,
    EDGING_STATE_COOLDOWN
};

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
};

void EdgingController::setSpeed(float newSpeed)
{
    speed = newSpeed;
    motorController.setSpeed(newSpeed);
}

void EdgingController::tick()
{
    arousalMonitor.take();
    float curArousal = arousalMonitor.getArousal();
    arousalMonitor.give();

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
            float newSpeed = std::min(
                (
                    (float) pdTICKS_TO_MS(curTime - rampStartTime) 
                    / 1000 
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
            give();  // unblock while pausing for break
            vTaskDelay(pdMS_TO_TICKS(settings.restTimeMin * 1000));
            take();
        }
        break;
    case EDGING_STATE_COOLDOWN:
        // rest time delay must be over by now
        if (curArousal < settings.restArousalMax)
        {
            ESP_LOGI(TAG, "Cooldown finish, continue ramping up");
            rampStartTime = xTaskGetTickCount();
            state = EDGING_STATE_RAMPING;
        }
        break;
    }

    give();
}
