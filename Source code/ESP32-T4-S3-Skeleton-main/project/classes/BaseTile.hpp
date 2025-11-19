#pragma once
#include <lvgl.h>

class BaseTile {
public:
    virtual ~BaseTile() = default;
    lv_obj_t* get_obj() const { return tile_; }

    static void InitGlobalOverlay();
    static void ShowGlobalOverlay(const char* text, lv_color_t color);
    static void HideGlobalOverlay();

protected:
    lv_obj_t* tile_ = nullptr;

    static lv_obj_t* global_overlay_;
    static lv_obj_t* global_overlay_label_;

    void apply_bg_color(bool dark);
    void apply_text_color(lv_obj_t* label, bool dark);
};
