#pragma once
#include <lvgl.h>

#include "BaseTile.hpp"
#include "Tile2.hpp"
#include "Tile3.hpp"
#include "Tile4.hpp"
#include "Tile5.hpp"

class Tiles {
public:
    void create_ui();

private:
    lv_obj_t* tileview_ = nullptr;

    WeatherTile* weatherTile_ = nullptr;
    OptionTile* optionTile_ = nullptr;
    WeekTile* weekTile_ = nullptr;
    HistoricalTile* historicalTile_ = nullptr;

    static void on_tile_clicked(lv_event_t* e);
};
