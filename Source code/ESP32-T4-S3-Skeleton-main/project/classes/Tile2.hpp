#pragma once
#include "BaseTile.hpp"

class WeatherTile : public BaseTile {
public:
    WeatherTile(lv_obj_t* parent);

private:
    lv_obj_t* title_;
    lv_obj_t* version_;
    lv_obj_t* group_;

    lv_obj_t* overlay_ = nullptr;
    
    static void tile_clicked_cb(lv_event_t* e);
    static void tile_swipe_up(lv_event_t* e);
};
