#include "Tile2.hpp"

// -------------
// Starting Tile
// -------------

// Constructor, creates a WeatherTile
WeatherTile::WeatherTile(lv_obj_t *parent)
{
    // Creates a tile at the position 1, 1
    tile_ = lv_tileview_add_tile(parent, 1, 1, LV_DIR_ALL);

    // Title
    title_ = lv_label_create(tile_);
    lv_label_set_text(title_, "Weather App");
    lv_obj_set_style_text_font(title_, &lv_font_montserrat_30, 0);
    lv_obj_align(title_, LV_ALIGN_CENTER, 0, -60);

    // Version
    version_ = lv_label_create(tile_);
    lv_label_set_text(version_, "V1.0");
    lv_obj_set_style_text_font(version_, &lv_font_montserrat_24, 0);
    lv_obj_align(version_, LV_ALIGN_CENTER, 0, -10);

    // Group
    group_ = lv_label_create(tile_);
    lv_label_set_text(group_, "Group 18");
    lv_obj_set_style_text_font(group_, &lv_font_montserrat_24, 0);
    lv_obj_align(group_, LV_ALIGN_CENTER, 0, 25);

    // Applying colors
    apply_bg_color(false);
    apply_text_color(title_, false);
    apply_text_color(version_, false);
    apply_text_color(group_, false);
}