#include "esp_log.h"
#include "freertos/FreeRTOS.h"

#define FREERTOS_CHECK(x) do { \
    if ((x) != pdPASS) { \
        ESP_LOGE("FREERTOS_CHECK", "FreeRTOS error at %s:%d\n", __FILE__, __LINE__); \
    } \
} while(0)
