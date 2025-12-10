#pragma once

#include "BaseTile.hpp"
#include "lvgl.h"

// deklarera Cogwheel-bilden
LV_IMG_DECLARE(Cogwheel);
//LV_IMG_DECLARE(Cloudy);

// Week Tile
class WeekTile : public BaseTile {
public:
    // Constructer: Creates the WeekTile
    WeekTile(lv_obj_t* parent);

    // UI - elements
    lv_obj_t* title_;
    void update_day(int index, const char* day, const char* temp, const lv_img_dsc_t* icon);

private:
    // Array with UI elements
    lv_obj_t* dayContainer[7];
    lv_obj_t* label_day[7];
    lv_obj_t* label_temp[7];
    lv_obj_t* icon_weather[7];
};
