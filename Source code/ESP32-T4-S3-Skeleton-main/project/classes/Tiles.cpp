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

// void Tiles::on_tile_clicked(lv_event_t* e)
// {
//     Tiles* self = static_cast<Tiles*>(lv_event_get_user_data(e));
//     lv_obj_t* clicked = lv_event_get_target(e);

//     if (clicked == self->weatherTile_->get_obj() or clicked == self->historicalTile_->get_obj())
//         lv_obj_set_tile(self->tileview_, self->optionTile_->get_obj(), LV_ANIM_ON);

//     // ... fortsätt med fler navigationer som du vill
// }

/*
