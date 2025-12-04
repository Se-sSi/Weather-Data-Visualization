#pragma once
#include "BaseTile.hpp"
#include <string>
class OptionTile : public BaseTile
{
public:
    OptionTile(lv_obj_t *parent);
    lv_obj_t *title_;
    lv_obj_t *reset_text;
    lv_obj_t *selected_text;
    std::string selected_city = "Goteborg";
    std::string default_city = "Karlskrona";
    
    

private:
    static void btn_event_cb(lv_event_t *e);
    lv_obj_t *manager_;
};
