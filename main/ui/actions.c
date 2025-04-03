#include <stdio.h>

#include "esp_log.h"

#include "eez_ui/actions.h"
#include "eez_ui/ui.h"

#define TAG "actions.c"

#define NUM_PAGES 2  // must manually edit to match number of pages in rotation

void action_change_page(lv_event_t * e)
{
    lv_obj_t * target = lv_event_get_target_obj(e);
    lv_state_t state = lv_obj_get_state(target);
    // ESP_LOGI(TAG, "got action %d, key %ld, state %d", lv_event_get_code(e), lv_event_get_key(e), state);
    if (state & LV_STATE_EDITED)
    {
        uint32_t key = lv_event_get_key(e);
        int page_offset = 0;
        if (key == LV_KEY_LEFT) page_offset = -1;
        else if (key == LV_KEY_RIGHT) page_offset = 1;
        else return;
        
        size_t cur_page_id = (size_t) lv_event_get_user_data(e);
        size_t new_page_id = ((cur_page_id + page_offset) % NUM_PAGES + NUM_PAGES) % NUM_PAGES;
        lv_obj_t* screen = ((lv_obj_t **)&objects)[new_page_id];
        lv_screen_load(screen);
    }
}
