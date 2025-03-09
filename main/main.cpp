#include <stdio.h>

#include "esp_log.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"

#include "Rotary.h"

#define PIN_ROTARY_CLK GPIO_NUM_20
#define PIN_ROTARY_DT GPIO_NUM_19
#define PIN_ROTARY_SW GPIO_NUM_18

#define QUEUE_LENGTH 16

extern "C" void app_main(void)
{
    QueueHandle_t eventQueue = xQueueCreate(QUEUE_LENGTH, sizeof(unsigned char));
    Rotary rotaryEncoder(PIN_ROTARY_CLK, PIN_ROTARY_DT, eventQueue);
    unsigned char event;
    int count = 0;
    
    for (;;)
    {
        xQueueReceive(eventQueue, &event, portMAX_DELAY);
        if (event == DIR_CW)
        {
            count++;
            ESP_LOGI("rotary", "CW %d", count);
        }
        else if (event == DIR_CCW)
        {
            count--;
            ESP_LOGI("rotary", "CCW %d", count);
        }
        else 
        {
            ESP_LOGE("rotary", "WTF HOW DID NON DIR GET HERE %d", event);
        }
    }
}

