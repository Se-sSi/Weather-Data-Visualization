#include "BaseTile.hpp"

// Set the background colour of the tile
void BaseTile::apply_bg_color(bool dark)
{
    lv_color_t color;

    // Different colours
    if(dark) {
        color = lv_color_make(30, 30, 60);
    } else {
        color = lv_color_make(172, 192, 226);
    }

    // Sets the background colour
    lv_obj_set_style_bg_color(tile_, color, 0);
    lv_obj_set_style_bg_opa(tile_, LV_OPA_COVER, 0);
}

// Sets the text colour of the tile
void BaseTile::apply_text_color(lv_obj_t* label, bool dark)
{
    // Uses with text for dark background and black text for ligth background
    lv_color_t color = dark ? lv_color_white() : lv_color_black();
    lv_obj_set_style_text_color(label, color, 0);
}
