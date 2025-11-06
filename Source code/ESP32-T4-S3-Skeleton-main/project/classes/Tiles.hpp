#pragma once

#include <lvgl.h>

class Tiles
{
    public:
        void create_ui();

    private:
        static void on_tile_clicked(lv_event_t* e);
        void apply_tile_colors(lv_obj_t* tile, lv_obj_t* label, bool dark);
    
        lv_obj_t* tileview_ = nullptr;

        lv_obj_t* t1_ = nullptr;
        lv_obj_t* t1_title_label_ = nullptr;
        lv_obj_t* t1_ver_label_ = nullptr;
        lv_obj_t* t1_group_label_ = nullptr;

        

        lv_obj_t* t2_ = nullptr;
        lv_obj_t* t2_label_ = nullptr;

        bool dark = false;  // start in light
};