#include "Tiles.hpp"

// Code from skeleton template (some modifications). Not properly documented
void Tiles::create_ui()
{
    // Fullscreen Tileview
    tileview_ = lv_tileview_create(lv_scr_act());
    lv_obj_set_size(tileview_, lv_disp_get_hor_res(NULL), lv_disp_get_ver_res(NULL));
    lv_obj_set_scrollbar_mode(tileview_, LV_SCROLLBAR_MODE_OFF);

    // Add tiles
    t1_ = lv_tileview_add_tile(tileview_, 0, 0, LV_DIR_HOR);
    t2_ = lv_tileview_add_tile(tileview_, 1, 0, LV_DIR_HOR);

    // Tile #1
    {
        // Title: Weather App
        t1_title_label_ = lv_label_create(t1_);
        lv_label_set_text(t1_title_label_, "Weather App");
        lv_obj_set_style_text_font(t1_title_label_, &lv_font_montserrat_30, 0);
        lv_obj_align(t1_title_label_, LV_ALIGN_CENTER, 0, -60); // Top position

        // Version: V0.1
        t1_ver_label_ = lv_label_create(t1_);
        lv_label_set_text(t1_ver_label_, "V0.1");
        lv_obj_set_style_text_font(t1_ver_label_, &lv_font_montserrat_24, 0);
        lv_obj_align(t1_ver_label_, LV_ALIGN_CENTER, 0, -10); // Slightly above center

        // Group: Group 18
        t1_group_label_ = lv_label_create(t1_);
        lv_label_set_text(t1_group_label_, "Group 18");
        lv_obj_set_style_text_font(t1_group_label_, &lv_font_montserrat_24, 0);
        lv_obj_align(t1_group_label_, LV_ALIGN_CENTER, 0, 25); // Below version text

        lv_obj_add_flag(t1_, LV_OBJ_FLAG_CLICKABLE);
        lv_obj_add_event_cb(t1_, &Tiles::on_tile_clicked, LV_EVENT_CLICKED, this);

        // Apply colors
        apply_tile_colors(t1_, t1_title_label_, /*dark=*/false);
        apply_tile_colors(t1_, t1_ver_label_, /*dark=*/false);
        apply_tile_colors(t1_, t1_group_label_, /*dark=*/false);
        

    }

    // Tile #2
    {
        t2_label_ = lv_label_create(t2_);
        lv_label_set_text(t2_label_, "Weather Forecast!!");
        lv_obj_set_style_text_font(t2_label_, &lv_font_montserrat_48, 0);
        lv_obj_center(t2_label_);

        apply_tile_colors(t2_, t2_label_, /*dark=*/false);
        lv_obj_add_flag(t2_, LV_OBJ_FLAG_CLICKABLE);
        lv_obj_add_event_cb(t2_, &Tiles::on_tile_clicked, LV_EVENT_CLICKED, this);
    }
}

void Tiles::apply_tile_colors(lv_obj_t* tile, lv_obj_t* label, bool dark)
{
    // Background
    lv_obj_set_style_bg_opa(tile, LV_OPA_COVER, 0);
    lv_obj_set_style_bg_color(tile, 
    dark ? lv_color_make(30, 30, 60)    // dark mode color (R,G,B)
         : lv_color_make(172, 192, 226), // light mode color (R,G,B)
    0);;

    // Text
    lv_obj_set_style_text_color(label, dark ? lv_color_white() : lv_color_black(), 0);
}

void Tiles::on_tile_clicked(lv_event_t* e)
{
    auto* self = static_cast<Tiles*>(lv_event_get_user_data(e));
    self->dark = !self->dark;
    self->apply_tile_colors(self->t2_, self->t2_label_, self->dark);
    self->apply_tile_colors(self->t1_, self->t1_title_label_, self->dark);
    self->apply_tile_colors(self->t1_, self->t1_ver_label_, self->dark);
    self->apply_tile_colors(self->t1_, self->t1_group_label_, self->dark);
}
