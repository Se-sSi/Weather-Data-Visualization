#include "TemplateTile2.hpp"

// Code from skeleton template (some modifications). Not properly documented
void TemplateTile2::create_ui(lv_obj_t* tileview)
{
    // Fullscreen Tileview
    tileview_ = tileview;
    lv_obj_set_size(tileview_, lv_disp_get_hor_res(NULL), lv_disp_get_ver_res(NULL));
    lv_obj_set_scrollbar_mode(tileview_, LV_SCROLLBAR_MODE_OFF);

    // Add two horizontal tiles
    t1_ = lv_tileview_add_tile(tileview_, 0, 0, LV_DIR_ALL);
    t2_ = lv_tileview_add_tile(tileview_, 1, 0, LV_DIR_ALL);
    t3_ = lv_tileview_add_tile(tileview_, 0, 1, LV_DIR_ALL);


    // Tile #1
    {
        t1_label_ = lv_label_create(t1_);
        lv_label_set_text(t1_label_, "Example tile other class 1");
        lv_obj_set_style_text_font(t1_label_, &lv_font_montserrat_28, 0);
        lv_obj_center(t1_label_);
        apply_tile_colors(t1_, t1_label_, /*dark=*/false);
    }

    // Tile #2
    {
        t2_label_ = lv_label_create(t2_);
        lv_label_set_text(t2_label_, "Example tile other class 2");
        lv_obj_set_style_text_font(t2_label_, &lv_font_montserrat_28, 0);
        lv_obj_center(t2_label_);

        apply_tile_colors(t2_, t2_label_, /*dark=*/false);
        lv_obj_add_flag(t2_, LV_OBJ_FLAG_CLICKABLE);
        lv_obj_add_event_cb(t2_, &TemplateTile2::on_tile2_clicked, LV_EVENT_CLICKED, this);
    }

    // Tile #3
    {
        t3_label_ = lv_label_create(t3_);
        lv_label_set_text(t3_label_, "Example tile other class 3333");
        lv_obj_set_style_text_font(t3_label_, &lv_font_montserrat_28, 0);
        lv_obj_center(t3_label_);

        apply_tile_colors(t3_, t3_label_, /*dark=*/false);
        lv_obj_add_flag(t3_, LV_OBJ_FLAG_CLICKABLE);
        lv_obj_add_event_cb(t3_, &TemplateTile2::on_tile2_clicked, LV_EVENT_CLICKED, this);
    }
}

void TemplateTile2::apply_tile_colors(lv_obj_t* tile, lv_obj_t* label, bool dark)
{
    // Background
    lv_obj_set_style_bg_opa(tile, LV_OPA_COVER, 0);
    lv_obj_set_style_bg_color(tile, dark ? lv_color_black() : lv_color_white(), 0);

    // Text
    lv_obj_set_style_text_color(label, dark ? lv_color_white() : lv_color_black(), 0);
}

void TemplateTile2::on_tile2_clicked(lv_event_t* e)
{
  auto* self = static_cast<TemplateTile2*>(lv_event_get_user_data(e));
  self->t2_dark = !self->t2_dark;
  self->apply_tile_colors(self->t2_, self->t2_label_, self->t2_dark);
}