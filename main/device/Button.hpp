#include <cstdint>

#include "iot_button.h"
#include "button_gpio.h"

class Button
{
public:
    Button(
        int32_t pinNum, 
        bool activeLevel, 
        uint16_t longPressTimeMS = 1000, 
        uint16_t shortPressTimeMS = 100,
        bool enablePowerSave = true, 
        bool disablePull = true
    );
    ~Button();
    void registerCallback(
        button_event_t event, 
        button_cb_t callback, 
        button_event_args_t eventArgs = {}, 
        void* userData = NULL
    );
private:
    button_handle_t buttonHandle;
};
