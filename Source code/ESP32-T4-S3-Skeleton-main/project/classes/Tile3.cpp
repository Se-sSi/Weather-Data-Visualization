#include "Tile3.hpp"


OptionTile::OptionTile(lv_obj_t *parent)
{
    tile_ = lv_tileview_add_tile(parent, 1, 0, LV_DIR_ALL);

    title_ = lv_label_create(tile_);
    lv_label_set_text(title_, "Options");
    lv_obj_align(title_, LV_ALIGN_TOP_MID, 0, 60);
    lv_obj_set_style_text_font(title_, &lv_font_montserrat_48, 0);

    /* Create the button inside your tile */
    lv_obj_t *btn = lv_btn_create(tile_);
    lv_obj_set_size(btn, 150, 75);
    lv_obj_align(btn, LV_ALIGN_BOTTOM_MID, 0, -10);
    lv_obj_set_style_bg_color(btn, lv_color_make(30, 30, 50), LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(btn, 3, LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(btn, lv_color_make(0, 0, 0), LV_STATE_DEFAULT);

    reset_text = lv_label_create(btn);
    lv_label_set_text(reset_text, "Reset");
    lv_obj_align(reset_text, LV_ALIGN_CENTER, 0, 0);

    selected_text = lv_label_create(tile_);
    lv_label_set_text(selected_text, ("Current selected city: " + selected_city).c_str());
    lv_obj_set_style_text_font(selected_text, &lv_font_montserrat_30, 0);
    lv_obj_align(selected_text, LV_ALIGN_CENTER, 0, 0);

    apply_bg_color(false);
    apply_text_color(title_, false);

    lv_obj_add_event_cb(btn, OptionTile::btn_event_cb, LV_EVENT_CLICKED, this);
}

/* Callback */
void OptionTile::btn_event_cb(lv_event_t *e)
{
    OptionTile* self = static_cast<OptionTile*>(lv_event_get_user_data(e));
    self->selected_city = self->default_city;

    lv_label_set_text(self->selected_text, ("Current selected city: " + self->selected_city).c_str());
}
