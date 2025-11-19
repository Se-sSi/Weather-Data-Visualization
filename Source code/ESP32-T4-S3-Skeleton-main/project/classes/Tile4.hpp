#pragma once
#include "BaseTile.hpp"

class WeekTile : public BaseTile {
public:
    WeekTile(lv_obj_t* parent);

private:
    lv_obj_t* title_;
    static void gesture_cb(lv_event_t* e);
};
