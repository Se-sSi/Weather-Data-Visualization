#pragma once
#include "BaseTile.hpp"

class HistoricalTile : public BaseTile {
public:
    HistoricalTile(lv_obj_t* parent);

private:
    lv_obj_t* title_;
};
