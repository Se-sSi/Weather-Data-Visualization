#include "Tiles.hpp"

// Code from skeleton template (some modifications). Not properly documented
void Tiles::create_ui()
{
    // Fullscreen Tileview
    tileview_ = lv_tileview_create(lv_scr_act());
    lv_obj_set_size(tileview_, lv_disp_get_hor_res(NULL), lv_disp_get_ver_res(NULL));
    lv_obj_set_scrollbar_mode(tileview_, LV_SCROLLBAR_MODE_OFF);

    // Add tiles
    t1_ = lv_tileview_add_tile(tileview_, 0, 0, LV_DIR_NONE);


    t2_ = lv_tileview_add_tile(tileview_, 0, 0, LV_DIR_ALL);
    lv_obj_add_flag(t2_, LV_OBJ_FLAG_HIDDEN);

    t3_left = lv_tileview_add_tile(tileview_, -1, -1, LV_DIR_ALL);
    t3_mid = lv_tileview_add_tile(tileview_, 0, -1, LV_DIR_ALL);
    t3_right = lv_tileview_add_tile(tileview_, 1, -1, LV_DIR_ALL);

    t4_ = lv_tileview_add_tile(tileview_, 1, 0, LV_DIR_ALL);

    t5_ = lv_tileview_add_tile(tileview_, -1, 0, LV_DIR_ALL);

        // Tile #1
    {
        t1_label_ = lv_label_create(t1_);
        lv_label_set_text(t1_label_, "Group 18");
        lv_obj_set_style_text_font(t1_label_, &lv_font_montserrat_48, 0);
        lv_obj_center(t1_label_);

        //apply_tile_colors(t1_, t1_label_, /*dark=*/false);
        lv_obj_add_flag(t1_, LV_OBJ_FLAG_CLICKABLE);
        lv_obj_add_event_cb(t1_, &Tiles::on_tile_clicked, LV_EVENT_CLICKED, this);

        lv_obj_move_foreground(t1_);
    }

    // Tile #2
    {
        // Title: Weather App
        t2_title_label_ = lv_label_create(t2_);
        lv_label_set_text(t2_title_label_, "Weather App");
        lv_obj_set_style_text_font(t2_title_label_, &lv_font_montserrat_30, 0);
        lv_obj_align(t2_title_label_, LV_ALIGN_CENTER, 0, -60); // Top position

        // Version: V0.1
        t2_ver_label_ = lv_label_create(t2_);
        lv_label_set_text(t2_ver_label_, "V0.1");
        lv_obj_set_style_text_font(t2_ver_label_, &lv_font_montserrat_24, 0);
        lv_obj_align(t2_ver_label_, LV_ALIGN_CENTER, 0, -10); // Slightly above center

        // Group: Group 18
        t2_group_label_ = lv_label_create(t2_);
        lv_label_set_text(t2_group_label_, "Group 18");
        lv_obj_set_style_text_font(t2_group_label_, &lv_font_montserrat_24, 0);
        lv_obj_align(t2_group_label_, LV_ALIGN_CENTER, 0, 25); // Below version text

        lv_obj_add_flag(t2_, LV_OBJ_FLAG_CLICKABLE);
        lv_obj_add_event_cb(t2_, &Tiles::on_tile_clicked, LV_EVENT_CLICKED, this);

        // Apply colors
        apply_bg_color(t2_, /*dark=*/false);
        apply_text_color(t2_title_label_, /*dark=*/false);
        apply_text_color(t2_ver_label_, /*dark=*/false);
        apply_text_color(t2_group_label_, /*dark=*/false);
        

    }

        // Tile #3 left
    {
        t3_left_label_ = lv_label_create(t3_left);
        lv_label_set_text(t3_left_label_, "Location Selectino");
        lv_obj_set_style_text_font(t3_left_label_, &lv_font_montserrat_48, 0);
        lv_obj_center(t3_left_label_);

        //apply_tile_colors(t4_, t4_label_, /*dark=*/false);
        lv_obj_add_flag(t3_left, LV_OBJ_FLAG_CLICKABLE);
        lv_obj_add_event_cb(t3_left, &Tiles::on_tile_clicked, LV_EVENT_CLICKED, this);

        apply_bg_color(t3_left, /*dark=*/false);
        apply_text_color(t3_left_label_, /*dark=*/false);
    }

        // Tile #3 mid
    {
        t3_mid_label_ = lv_label_create(t3_mid);
        lv_label_set_text(t3_mid_label_, "Location Selectino");
        lv_obj_set_style_text_font(t3_mid_label_, &lv_font_montserrat_48, 0);
        lv_obj_center(t3_mid_label_);

        //apply_tile_colors(t4_, t4_label_, /*dark=*/false);
        lv_obj_add_flag(t3_mid, LV_OBJ_FLAG_CLICKABLE);
        lv_obj_add_event_cb(t3_mid, &Tiles::on_tile_clicked, LV_EVENT_CLICKED, this);

        apply_bg_color(t3_mid, /*dark=*/false);
        apply_text_color(t3_mid_label_, /*dark=*/false);
    }

        // Tile #3 right
    {
        t3_right_label_ = lv_label_create(t3_right);
        lv_label_set_text(t3_right_label_, "Location Selectino");
        lv_obj_set_style_text_font(t3_right_label_, &lv_font_montserrat_48, 0);
        lv_obj_center(t3_right_label_);

        //apply_tile_colors(t4_, t4_label_, /*dark=*/false);
        lv_obj_add_flag(t3_right, LV_OBJ_FLAG_CLICKABLE);
        lv_obj_add_event_cb(t3_right, &Tiles::on_tile_clicked, LV_EVENT_CLICKED, this);

        apply_bg_color(t3_right, /*dark=*/false);
        apply_text_color(t3_right_label_, /*dark=*/false);
    }

    // Tile #4
    {
        t4_label_ = lv_label_create(t4_);
        lv_label_set_text(t4_label_, "7 Days Weather Forecast!!");
        lv_obj_set_style_text_font(t4_label_, &lv_font_montserrat_48, 0);
        lv_obj_center(t4_label_);

        //apply_tile_colors(t4_, t4_label_, /*dark=*/false);
        lv_obj_add_flag(t4_, LV_OBJ_FLAG_CLICKABLE);
        lv_obj_add_event_cb(t4_, &Tiles::on_tile_clicked, LV_EVENT_CLICKED, this);

        apply_bg_color(t4_, /*dark=*/false);
        apply_text_color(t4_label_, /*dark=*/false);
    }

        // Tile #5
    {
        t5_label_ = lv_label_create(t5_);
        lv_label_set_text(t5_label_, "Historical Data");
        lv_obj_set_style_text_font(t5_label_, &lv_font_montserrat_48, 0);
        lv_obj_center(t5_label_);

        //apply_tile_colors(t4_, t4_label_, /*dark=*/false);
        lv_obj_add_flag(t5_, LV_OBJ_FLAG_CLICKABLE);
        lv_obj_add_event_cb(t5_, &Tiles::on_tile_clicked, LV_EVENT_CLICKED, this);

        apply_bg_color(t5_, /*dark=*/false);
        apply_text_color(t5_label_, /*dark=*/false);
    }
    
}

void Tiles::apply_bg_color(lv_obj_t* tile, bool dark)
{
    lv_obj_set_style_bg_opa(tile, LV_OPA_COVER, 0);
    lv_obj_set_style_bg_color(tile, 
    dark ? lv_color_make(30, 30, 60)    // dark mode color (R,G,B)
         : lv_color_make(172, 192, 226), // light mode color (R,G,B)
    0);;

}

void Tiles::apply_text_color(lv_obj_t* label, bool dark)
{
    lv_obj_set_style_text_color(label, dark ? lv_color_white() : lv_color_black(), 0);
}

void Tiles::on_tile_clicked(lv_event_t* e)
{
    auto* self = static_cast<Tiles*>(lv_event_get_user_data(e));
    lv_obj_t* clicked_tile = lv_event_get_target(e);

    // Om t1_ klickas → navigera till t2_ (0,0)
    //if (clicked_tile == self->t1_)
    //{
        // Hämta storlek på tileview
    //    lv_coord_t w = lv_obj_get_width(self->tileview_);
     //   lv_coord_t h = lv_obj_get_height(self->tileview_);

        // t2 ligger på kolumn 0, rad 0
    //    lv_obj_scroll_to(self->tileview_, 0 * w, 0 * h, LV_ANIM_ON);
    //    lv_obj_del(self->t1_);

      //  return;
    //}

    if (clicked_tile == self->t1_)
{
    // Ta bort tile 1 när den klickas
    lv_obj_del(self->t1_);
    self->t1_ = nullptr; // säkerhetsåtgärd
    lv_obj_clear_flag(self->t2_, LV_OBJ_FLAG_HIDDEN);
    return;
}

    // Växla mörkt/ljust tema
    self->dark = !self->dark;

    // Uppdatera bakgrundsfärger
    self->apply_bg_color(self->t2_, self->dark);
    self->apply_bg_color(self->t4_, self->dark);

    // Uppdatera textfärger
    self->apply_text_color(self->t2_title_label_, self->dark);
    self->apply_text_color(self->t2_ver_label_, self->dark);
    self->apply_text_color(self->t2_group_label_, self->dark);
    self->apply_text_color(self->t4_label_, self->dark);
}

