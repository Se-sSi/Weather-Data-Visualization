#pragma once
#include "BaseTile.hpp"

// Weather app Tile
class WeatherTile : public BaseTile {
public:
    // Constructor: creates a WeatherTile
    WeatherTile(lv_obj_t* parent);

    // Labels to the WeatherTile
    lv_obj_t* title_;
    lv_obj_t* version_;
    lv_obj_t* group_;

private:
    // Overlay (the one not in use)
    lv_obj_t* overlay_ = nullptr;
    
    // Check if clicked funktion (also not in use)
    static void tile_clicked_cb(lv_event_t* e);
};
