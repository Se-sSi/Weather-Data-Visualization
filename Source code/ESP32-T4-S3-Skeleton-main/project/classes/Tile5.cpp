#include "Tile5.hpp"

HistoricalTile::HistoricalTile(lv_obj_t* parent)
{
    tile_ = lv_tileview_add_tile(parent, 2, 1, LV_DIR_ALL);

    title_ = lv_label_create(tile_);
    lv_label_set_text(title_, "Historical Data");
    lv_obj_set_style_text_font(title_, &lv_font_montserrat_48, 0);
    lv_obj_center(title_);

    apply_bg_color(false);
    apply_text_color(title_, false);
}
