#pragma once

#include <lvgl.h>

class TemplateTile
{
    public:
        void create_ui();

    private:
        static void on_tile2_clicked(lv_event_t* e);
        void apply_tile_colors(lv_obj_t* tile, lv_obj_t* label, bool dark);
    
        lv_obj_t* tileview_ = nullptr;
        lv_obj_t* t1_ = nullptr;
        lv_obj_t* t2_ = nullptr;
        lv_obj_t* t1_label_ = nullptr;
        lv_obj_t* t2_label_ = nullptr;
        bool t2_dark = false;  // start tile #2 in light mode
};