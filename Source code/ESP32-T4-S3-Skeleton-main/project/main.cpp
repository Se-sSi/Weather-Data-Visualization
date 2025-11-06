#include "main.hpp"

#include "classes/Tiles.hpp"

// This file is where we work from. Don't touch the project.ino file.

static Tiles tiles;

/**
* @brief Code is only run once in startup()
*/
void startup()
{
    tiles.create_ui(); // Example
}

/**
* @brief Code is run every cycle in update()
*/
void update()
{

}