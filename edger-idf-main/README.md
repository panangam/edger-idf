# Edger using ESP-IDF

- Class methods that call lvgl code (and thus must be guarded with lvglMutex) are prefixed with "lv", e.g. "lvLoadPage".
