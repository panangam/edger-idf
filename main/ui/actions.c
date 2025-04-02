#include "eez_ui/actions.h"
#include "eez_ui/ui.h"

#define NUM_PAGES 2

void action_change_page(lv_event_t * e)
{
    lv_obj_t * target = lv_event_get_target_obj(e);
    lv_state_t state = lv_obj_get_state(target);
    if (state == LV_STATE_EDITED)
    {
        int32_t rotary_diff = lv_event_get_rotary_diff(e);
        int8_t cur_page_id = (int8_t) lv_event_get_user_data(e);
        int8_t page_offset = rotary_diff > 0 ? 1 : -1;
        int8_t new_page_id = (cur_page_id + page_offset + NUM_PAGES) % NUM_PAGES;
        loadScreen(new_page_id + 1);
    }
}
