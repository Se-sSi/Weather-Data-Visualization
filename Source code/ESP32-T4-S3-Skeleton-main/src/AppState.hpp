#pragma once
#include <Arduino.h>

void app_set_city(const char* city);
const char* app_get_city();

// register a single callback that will be invoked on city change
void app_register_city_cb(void (*cb)(void*), void* user_data);