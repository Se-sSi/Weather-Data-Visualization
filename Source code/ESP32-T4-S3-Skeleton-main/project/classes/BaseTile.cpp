#include "BaseTile.hpp"

lv_obj_t* BaseTile::global_overlay_ = nullptr;
lv_obj_t* BaseTile::global_overlay_label_ = nullptr;


// ----------------------------
// Skapa global overlay
// ----------------------------
void BaseTile::InitGlobalOverlay()
{
    if (global_overlay_ != nullptr)
        return;

    // Skapa helskärms-overlay
    global_overlay_ = lv_obj_create(lv_scr_act());
    lv_obj_set_size(global_overlay_, LV_PCT(100), LV_PCT(100));
    lv_obj_set_style_bg_opa(global_overlay_, LV_OPA_COVER, 0);

    // Ingen border, inga scrollbars
    lv_obj_clear_flag(global_overlay_, LV_OBJ_FLAG_SCROLLABLE);

    // Label
    global_overlay_label_ = lv_label_create(global_overlay_);
    lv_label_set_text(global_overlay_label_, "");
    lv_obj_set_style_text_color(global_overlay_label_, lv_color_black(), 0);
    lv_obj_set_style_text_font(global_overlay_label_, &lv_font_montserrat_28, 0);
    lv_obj_center(global_overlay_label_);

    // Starta som dold
    lv_obj_add_flag(global_overlay_, LV_OBJ_FLAG_HIDDEN);
}


// ----------------------------
// Visa overlay med valfri text & färg
// ----------------------------
void BaseTile::ShowGlobalOverlay(const char* text, lv_color_t color)
{
    if (!global_overlay_)
        InitGlobalOverlay();

    lv_label_set_text(global_overlay_label_, text);

    // Sätt bakgrundsfärg
    lv_obj_set_style_bg_color(global_overlay_, color, 0);

    // Visa overlay
    lv_obj_clear_flag(global_overlay_, LV_OBJ_FLAG_HIDDEN);

    // Flytta till fronten ifall andra objekt ligger ovanpå
    lv_obj_move_foreground(global_overlay_);
}


// ----------------------------
// Dölj overlay
// ----------------------------
void BaseTile::HideGlobalOverlay()
{
    if (!global_overlay_) return;

    lv_obj_add_flag(global_overlay_, LV_OBJ_FLAG_HIDDEN);
}


void BaseTile::apply_bg_color(bool dark)
{
    lv_color_t color;

    if(dark) {
        color = lv_color_make(30, 30, 60);
    } else {
        color = lv_color_make(172, 192, 226);
    }

    lv_obj_set_style_bg_color(tile_, color, 0);
    lv_obj_set_style_bg_opa(tile_, LV_OPA_COVER, 0);
}

void BaseTile::apply_text_color(lv_obj_t* label, bool dark)
{
    lv_color_t color = dark ? lv_color_white() : lv_color_black();
    lv_obj_set_style_text_color(label, color, 0);
}
