#include "main.hpp"

#include "classes/TemplateTile.hpp"
#include "classes/TemplateTile2.hpp"

// This file is where we work from. Don't touch the project.ino file.

static TemplateTile template_tile;
static TemplateTile2 template_tile2;
lv_obj_t* tileview_ = nullptr;

/**
* @brief Code is only run once in startup()
*/
void startup()
{
    //template_tile.create_ui(); // Example
    template_tile2.create_ui(tileview_); // Example
}

/**
* @brief Code is run every cycle in update()
*/
void update()
{

}