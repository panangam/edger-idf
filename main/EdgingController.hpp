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
    float motorSpeedMax = 0.3;
};

enum EdgingState_t
{
    EDGING_STATE_START = 0,
    EDGING_STATE_RAMPING,
    EDGING_STATE_COOLDOWN
};

inline TickType_t secToTick(float sec) { return pdMS_TO_TICKS(sec * 1000); }

inline float tickToSec(TickType_t tick) { return static_cast<float>(pdTICKS_TO_MS(tick)) / 1000; }

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
