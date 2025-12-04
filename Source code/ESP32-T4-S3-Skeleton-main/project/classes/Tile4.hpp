#pragma once

#include "BaseTile.hpp"
#include "lvgl.h"

// deklarera Cogwheel-bilden
LV_IMG_DECLARE(Cogwheel);

class WeekTile : public BaseTile {
public:
    WeekTile(lv_obj_t* parent);

    lv_obj_t* title_;
    void update_day(int index, const char* day, const char* temp, const lv_img_dsc_t* icon);

private:
    static void gesture_cb(lv_event_t* e);

    lv_obj_t* dayContainer[7];
    lv_obj_t* label_day[7];
    lv_obj_t* label_temp[7];
    lv_obj_t* icon_weather[7];
};
