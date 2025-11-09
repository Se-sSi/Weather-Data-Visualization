#pragma once

#include <lvgl.h>

class Tiles
{
    public:
        void create_ui();

    private:
        static void on_tile_clicked(lv_event_t* e);
        void apply_bg_color(lv_obj_t* tile, bool dark);
        void apply_text_color(lv_obj_t* label, bool dark);
    
        lv_obj_t* tileview_ = nullptr;

        lv_obj_t* t2_ = nullptr;
        lv_obj_t* t2_title_label_ = nullptr;
        lv_obj_t* t2_ver_label_ = nullptr;
        lv_obj_t* t2_group_label_ = nullptr;

        lv_obj_t* t3_left = nullptr;
        lv_obj_t* t3_left_label_ = nullptr;
        lv_obj_t* t3_mid = nullptr;
        lv_obj_t* t3_mid_label_ = nullptr;
        lv_obj_t* t3_right = nullptr;
        lv_obj_t* t3_right_label_ = nullptr;

        lv_obj_t* t5_ = nullptr;
        lv_obj_t* t5_label_ = nullptr;

        lv_obj_t* t4_ = nullptr;
        lv_obj_t* t4_label_ = nullptr;

        lv_obj_t* t1_ = nullptr;
        lv_obj_t* t1_label_ = nullptr;
        

        bool dark = false;  // start in light
};