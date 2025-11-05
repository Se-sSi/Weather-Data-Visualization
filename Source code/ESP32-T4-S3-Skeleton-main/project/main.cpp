#include "main.hpp"

#include "classes/TemplateTile.hpp"

// This file is where we work from. Don't touch the project.ino file.

static TemplateTile template_tile;

/**
* @brief Code is only run once in startup()
*/
void startup()
{
    template_tile.create_ui(); // Example
}

/**
* @brief Code is run every cycle in update()
*/
void update()
{

}