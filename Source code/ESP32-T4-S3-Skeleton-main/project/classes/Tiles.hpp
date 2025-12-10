#pragma once
#include <lvgl.h>

#include "BaseTile.hpp"
#include "Tile2.hpp"
#include "Tile3.hpp"
#include "Tile4.hpp"
#include "Tile5.hpp"


// Manager class
class Tiles
{
public:
    // Created the UI
    void create_ui();

private:
    // Creates the tileview container 
    lv_obj_t *tileview_ = nullptr;

    // Different Tiles
    WeatherTile *weatherTile_ = nullptr;
    OptionTile *optionTile_ = nullptr;
    WeekTile *weekTile_ = nullptr;
    HistoricalTile *historicalTile_ = nullptr;

    // Events
    static void on_tile_clicked(lv_event_t *e);
    static void on_theme_change(lv_event_t *e);

    // Current state
    bool dark = false;
};
