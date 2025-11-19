#pragma once
#include "BaseTile.hpp"

class HistoricalTile : public BaseTile {
public:
    HistoricalTile(lv_obj_t* parent);
    lv_obj_t* title_;

private:
};
