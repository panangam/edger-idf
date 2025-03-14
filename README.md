# Edger using ESP-IDF

- Class methods won't deal with semaphores or locks (e.g. `xSemaphoreTake`, `lvgl_port_lock`), EXCEPT for `.tick()`. Will treat `.tick()` like a high level app code. 
