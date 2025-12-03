#include "Tile4.hpp"

WeekTile::WeekTile(lv_obj_t* parent)
{
    tile_ = lv_tileview_add_tile(parent, 0, 1, LV_DIR_ALL);

    title_ = lv_label_create(tile_);
    lv_label_set_text(title_, "7 Day Weather Forecast");
    lv_obj_set_style_text_font(title_, &lv_font_montserrat_48, 0);
    lv_obj_center(title_);

    apply_bg_color(false);
    apply_text_color(title_, false);

    lv_obj_add_event_cb(tile_, WeekTile::gesture_cb, LV_EVENT_GESTURE, this);

}


void WeekTile::gesture_cb(lv_event_t* e)
{
    WeekTile* self = static_cast<WeekTile*>(lv_event_get_user_data(e));

    lv_dir_t dir = lv_indev_get_gesture_dir(lv_indev_get_act());

    if (dir == LV_DIR_TOP)
    {
        BaseTile::ShowGlobalOverlay("No Internet!", lv_color_hex(0xe74c3c));
    }
}
