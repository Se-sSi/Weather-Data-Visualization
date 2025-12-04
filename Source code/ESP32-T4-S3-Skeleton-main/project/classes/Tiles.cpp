#include "Tiles.hpp"

void Tiles::create_ui()
{
    tileview_ = lv_tileview_create(lv_scr_act());
    lv_obj_set_size(tileview_, LV_HOR_RES, LV_VER_RES);
    lv_obj_set_scrollbar_mode(tileview_, LV_SCROLLBAR_MODE_OFF);

    // Skapa tiles
    weatherTile_ = new WeatherTile(tileview_);
    optionTile_ = new OptionTile(tileview_);
    weekTile_ = new WeekTile(tileview_);
    historicalTile_ = new HistoricalTile(tileview_);

    // Lägg till event callbacks för klick
    lv_obj_add_event_cb(weatherTile_->get_obj(), Tiles::on_tile_clicked, LV_EVENT_CLICKED, this);
    lv_obj_add_event_cb(optionTile_->get_obj(), Tiles::on_tile_clicked, LV_EVENT_CLICKED, this);
    lv_obj_add_event_cb(weekTile_->get_obj(), Tiles::on_tile_clicked, LV_EVENT_CLICKED, this);
    lv_obj_add_event_cb(historicalTile_->get_obj(), Tiles::on_tile_clicked, LV_EVENT_CLICKED, this);

    // Sätt starttile
    lv_obj_set_tile(tileview_, weatherTile_->get_obj(), LV_ANIM_OFF);
}

void Tiles::on_tile_clicked(lv_event_t *e)
{
    Tiles *self = static_cast<Tiles *>(lv_event_get_user_data(e));
    self->dark = !self->dark;

    self->weatherTile_->apply_bg_color(self->dark);
    self->optionTile_->apply_bg_color(self->dark);
    self->weekTile_->apply_bg_color(self->dark);
    self->historicalTile_->apply_bg_color(self->dark);

    self->weatherTile_->apply_text_color(self->weatherTile_->title_, self->dark);
    self->weatherTile_->apply_text_color(self->weatherTile_->version_, self->dark);
    self->weatherTile_->apply_text_color(self->weatherTile_->group_, self->dark);

    self->optionTile_->apply_text_color(self->optionTile_->title_, self->dark);
    self->optionTile_->apply_text_color(self->optionTile_->selected_text, self->dark);


    self->weekTile_->apply_text_color(self->weekTile_->title_, self->dark);
    self->historicalTile_->apply_text_color(self->historicalTile_->title_, self->dark);
}

//NOT IN USE, SHOULD REPLACE "on_tile_clicked"
void Tiles::on_theme_change(lv_event_t *e)
{
    Tiles *self = static_cast<Tiles *>(lv_event_get_user_data(e));
    self->dark = !self->dark;

    self->weatherTile_->apply_bg_color(self->dark);
    self->optionTile_->apply_bg_color(self->dark);
    self->weekTile_->apply_bg_color(self->dark);
    self->historicalTile_->apply_bg_color(self->dark);

    self->weatherTile_->apply_text_color(self->weatherTile_->title_, self->dark);
    self->weatherTile_->apply_text_color(self->weatherTile_->version_, self->dark);
    self->weatherTile_->apply_text_color(self->weatherTile_->group_, self->dark);

    self->optionTile_->apply_text_color(self->optionTile_->title_, self->dark);
    self->weekTile_->apply_text_color(self->weekTile_->title_, self->dark);
    self->historicalTile_->apply_text_color(self->historicalTile_->title_, self->dark);
}

// void Tiles::on_tile_clicked(lv_event_t* e)
// {
//     Tiles* self = static_cast<Tiles*>(lv_event_get_user_data(e));
//     lv_obj_t* clicked = lv_event_get_target(e);

//     if (clicked == self->weatherTile_->get_obj() or clicked == self->historicalTile_->get_obj())
//         lv_obj_set_tile(self->tileview_, self->optionTile_->get_obj(), LV_ANIM_ON);

//     // ... fortsätt med fler navigationer som du vill
// }

/*
// Code from skeleton template (some modifications). Not properly documented
void Tiles::create_ui()
{
    // Fullscreen Tileview
    tileview_ = lv_tileview_create(lv_scr_act());
    lv_obj_set_size(tileview_, lv_disp_get_hor_res(NULL), lv_disp_get_ver_res(NULL));
    lv_obj_set_scrollbar_mode(tileview_, LV_SCROLLBAR_MODE_OFF);

    // Add tiles
    t2_ = lv_tileview_add_tile(tileview_, 0, 0, LV_DIR_ALL);

    t3_ = lv_tileview_add_tile(tileview_, 0, -1, LV_DIR_ALL);

    t4_ = lv_tileview_add_tile(tileview_, -1, 0, LV_DIR_ALL);

    t5_ = lv_tileview_add_tile(tileview_, 1, 0, LV_DIR_ALL);

    lv_obj_add_flag(t2_, LV_OBJ_FLAG_HIDDEN);
    t1_ = lv_tileview_add_tile(tileview_, 0, 0, LV_DIR_NONE);
        // Tile #1
    {
        t1_label_ = lv_label_create(t1_);
        lv_label_set_text(t1_label_, "Group 18");
        lv_obj_set_style_text_font(t1_label_, &lv_font_montserrat_48, 0);
        lv_obj_center(t1_label_);


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

        apply_text_color(t2_title_label_, false);
        apply_text_color(t2_ver_label_, false);
        apply_text_color(t2_group_label_,false);


    }

        // Tile #3
    {
        t3_label_ = lv_label_create(t3_);
        lv_label_set_text(t3_label_, "Location Selectino");
        lv_obj_set_style_text_font(t3_label_, &lv_font_montserrat_48, 0);
        lv_obj_center(t3_label_);


        lv_obj_add_flag(t3_, LV_OBJ_FLAG_CLICKABLE);
        lv_obj_add_event_cb(t3_, &Tiles::on_tile_clicked, LV_EVENT_CLICKED, this);

        apply_bg_color(t3_,false);
        apply_text_color(t3_label_,false);
    }

    // Tile #4
    {
        t4_label_ = lv_label_create(t4_);
        lv_label_set_text(t4_label_, "7 Day Weather Forecast");
        lv_obj_set_style_text_font(t4_label_, &lv_font_montserrat_48, 0);
        lv_obj_center(t4_label_);

        lv_obj_add_flag(t4_, LV_OBJ_FLAG_CLICKABLE);
        lv_obj_add_event_cb(t4_, &Tiles::on_tile_clicked, LV_EVENT_CLICKED, this);

        apply_bg_color(t4_,false);
        apply_text_color(t4_label_,false);
    }

        // Tile #5
    {
        t5_label_ = lv_label_create(t5_);
        lv_label_set_text(t5_label_, "Historical Data");
        lv_obj_set_style_text_font(t5_label_, &lv_font_montserrat_48, 0);
        lv_obj_center(t5_label_);

        lv_obj_add_flag(t5_, LV_OBJ_FLAG_CLICKABLE);
        lv_obj_add_event_cb(t5_, &Tiles::on_tile_clicked, LV_EVENT_CLICKED, this);

        apply_bg_color(t5_,false);
        apply_text_color(t5_label_, false);
    }
    // Gör t2_ till aktiv tile (startpunkt)
    //lv_obj_set_tile(tileview_, t2_, LV_ANIM_OFF);

    // För säkerhets skull – stäng av scroll chain som kan störa swipe
    lv_obj_clear_flag(tileview_, LV_OBJ_FLAG_SCROLL_CHAIN_HOR);
    lv_obj_clear_flag(tileview_, LV_OBJ_FLAG_SCROLL_CHAIN_VER);
    lv_obj_set_tile(tileview_, t1_, LV_ANIM_OFF);  // Gör t1_ till aktiv tile


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

    if (clicked_tile == self->t1_)
{
    lv_obj_set_tile(self->tileview_, self->t2_, LV_ANIM_ON);
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

*/