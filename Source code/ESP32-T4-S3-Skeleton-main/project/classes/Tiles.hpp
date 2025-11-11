#pragma once

#include <lvgl.h>

class Tiles
{
    public:
        void create_ui();

    private:
        static void on_tile_clicked(lv_event_t* e);
        void create_option_tile();
        static void gesture_event_cb(lv_event_t* e);
        static void show_option_tile_cb(lv_event_t* e);
        void apply_bg_color(lv_obj_t* tile, bool dark);
        void apply_text_color(lv_obj_t* label, bool dark);
    
        lv_obj_t* tileview_ = nullptr;

        lv_obj_t* t2_;
        lv_obj_t* t2_title_label_ = nullptr;
        lv_obj_t* t2_ver_label_ = nullptr;
        lv_obj_t* t2_group_label_ = nullptr;


        lv_obj_t* t3_;
        lv_obj_t* t3_label_ = nullptr;


        lv_obj_t* t5_;
        lv_obj_t* t5_label_ = nullptr;

        lv_obj_t* t4_;
        lv_obj_t* t4_label_ = nullptr;

        lv_obj_t* t1_;
        lv_obj_t* t1_label_ = nullptr;

        lv_obj_t* option_tile_;
        

        bool dark = false;  // start in light
};