#include "Tile2.hpp"

WeatherTile::WeatherTile(lv_obj_t *parent)
{
    tile_ = lv_tileview_add_tile(parent, 1, 1, LV_DIR_ALL);

    // UI-element
    title_ = lv_label_create(tile_);
    lv_label_set_text(title_, "Weather App");
    lv_obj_set_style_text_font(title_, &lv_font_montserrat_30, 0);
    lv_obj_align(title_, LV_ALIGN_CENTER, 0, -60);

    version_ = lv_label_create(tile_);
    lv_label_set_text(version_, "V0.2");
    lv_obj_set_style_text_font(version_, &lv_font_montserrat_24, 0);
    lv_obj_align(version_, LV_ALIGN_CENTER, 0, -10);

    group_ = lv_label_create(tile_);
    lv_label_set_text(group_, "Group 18");
    lv_obj_set_style_text_font(group_, &lv_font_montserrat_24, 0);
    lv_obj_align(group_, LV_ALIGN_CENTER, 0, 25);

    // overlay_ = lv_obj_create(tile_);
    // lv_obj_set_size(overlay_, lv_obj_get_width(tile_), lv_obj_get_height(tile_));
    // lv_obj_set_style_bg_color(overlay_, lv_color_hex(0x3498db), 0);
    // lv_obj_set_style_bg_opa(overlay_, LV_OPA_COVER, 0);
    // lv_obj_move_foreground(overlay_);

    // // Add label on overlay
    // lv_obj_t* overlay_label = lv_label_create(overlay_);
    // lv_label_set_text(overlay_label, "Grupp 18");
    // lv_obj_set_style_text_color(overlay_label, lv_color_white(), 0);
    // lv_obj_center(overlay_label);

    // Färger
    apply_bg_color(false);
    apply_text_color(title_, false);
    apply_text_color(version_, false);
    apply_text_color(group_, false);

    // lv_obj_add_event_cb(overlay_, WeatherTile::tile_clicked_cb, LV_EVENT_CLICKED, this);
}

// void WeatherTile::tile_clicked_cb(lv_event_t* e)
// {
//     WeatherTile* self = static_cast<WeatherTile*>(lv_event_get_user_data(e));
//     lv_obj_t* clicked = lv_event_get_target(e);

//     if (clicked)
//     {
//         lv_obj_add_flag(self->overlay_, LV_OBJ_FLAG_HIDDEN);
//     }
// }