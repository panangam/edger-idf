#include <stdio.h>

#include "esp_log.h"

#include "eez_ui/actions.h"
#include "eez_ui/ui.h"

#include "PagesManager.hpp"

void action_change_page(lv_event_t * e)
{
    lv_obj_t* target = lv_event_get_target_obj(e);
    lv_state_t state = lv_obj_get_state(target);
    // ESP_LOGI(TAG, "got action %d, key %ld, state %d", lv_event_get_code(e), lv_event_get_key(e), state);
    if (state & LV_STATE_EDITED)
    {
        uint32_t key = lv_event_get_key(e);
        int page_offset = 0;
        if (key == LV_KEY_LEFT) page_offset = -1;
        else if (key == LV_KEY_RIGHT) page_offset = 1;
        else if (key == LV_KEY_ENTER) 
        {
            lv_group_t* group = lv_obj_get_group(target);
            if (lv_group_get_obj_count(group) > 1) lv_group_set_editing(group, false);
            return;
        }
        else return;
        
        if (global_pages_manager == nullptr) return;
        global_pages_manager->changePage(page_offset);
    }
}
