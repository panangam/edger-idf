#include "EdgingController.hpp"

constexpr const char* TAG = "EdgingController";

void EdgingController::setSpeed(float newSpeed)
{
    speed = newSpeed;
    motorController.setSpeed(newSpeed);
}

void EdgingController::tick()
{
    float curArousal = arousalMonitor.getArousal();

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
                rampStartTime = curTime - secToTick(settings.rampUpTime * settings.rampBreakRatio);
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
            vTaskDelay(pdMS_TO_TICKS(settings.cooldownTimeMin * 1000));
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
}
