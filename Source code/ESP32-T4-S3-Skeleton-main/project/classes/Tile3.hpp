#pragma once
#include "BaseTile.hpp"
#include <string>

// Option Tile
class OptionTile : public BaseTile
{
public:

    // Constructer: Creates the OptionTile
    OptionTile(lv_obj_t *parent);

    // UI elements
    lv_obj_t *title_;
    lv_obj_t *reset_text;
    lv_obj_t *selected_text;

    // Different citys
    std::string selected_city = "Goteborg";
    std::string default_city = "Karlskrona";
    
    

private:
    // Event for button
    static void btn_event_cb(lv_event_t *e);
    lv_obj_t *manager_;
};
