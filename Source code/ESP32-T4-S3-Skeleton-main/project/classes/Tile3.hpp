#pragma once
#include "BaseTile.hpp"

class OptionTile : public BaseTile
{
public:
    OptionTile(lv_obj_t *parent);
    lv_obj_t *title_;

private:
    static void btn_event_cb(lv_event_t *e);
    lv_obj_t *manager_;
};
