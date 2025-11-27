#include "Tile3.hpp"

OptionTile::OptionTile(lv_obj_t *parent)
{
    tile_ = lv_tileview_add_tile(parent, 1, 0, LV_DIR_ALL);

    title_ = lv_label_create(tile_);
    lv_label_set_text(title_, "Location Selection");
    lv_obj_set_style_text_font(title_, &lv_font_montserrat_48, 0);
    lv_obj_center(title_);

    /* Create the button inside your tile */
    lv_obj_t *btn = lv_btn_create(tile_);
    lv_obj_set_size(btn, 75, 75);
    lv_obj_align(btn, LV_ALIGN_TOP_LEFT, 10, 10);
    lv_obj_set_style_bg_color(btn, lv_color_make(200, 200, 200), LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(btn, 3, LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(btn, lv_color_make(0, 0, 0), LV_STATE_DEFAULT);

    apply_bg_color(false);
    apply_text_color(title_, false);

    lv_obj_add_event_cb(btn, OptionTile::btn_event_cb, LV_EVENT_CLICKED, this);
}

/* Callback */
void OptionTile::btn_event_cb(lv_event_t *e)
{
    // Denna funktionen ska kalla på Tiles objektets function som heter on_theme_change, lyckades inte implementera
}
