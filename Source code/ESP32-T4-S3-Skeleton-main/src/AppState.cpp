#include "AppState.hpp"
#include <cstring>

static char s_city[32] = "Karlskrona";
static void (*s_cb)(void*) = nullptr;
static void* s_cb_user = nullptr;

void app_set_city(const char* city)
{
    if (!city) return;
    strncpy(s_city, city, sizeof(s_city)-1);
    s_city[sizeof(s_city)-1] = '\0';
    if (s_cb) s_cb(s_cb_user); // notify
}

const char* app_get_city()
{
    return s_city;
}

void app_register_city_cb(void (*cb)(void*), void* user_data)
{
    s_cb = cb;
    s_cb_user = user_data;
}