#pragma once
#include <lvgl.h>

class BaseTile {
public:
    virtual ~BaseTile() = default;
    lv_obj_t* get_obj() const { return tile_; }

    void apply_bg_color(bool dark);
    void apply_text_color(lv_obj_t* label, bool dark);
    
protected:
    lv_obj_t* tile_ = nullptr;
};
