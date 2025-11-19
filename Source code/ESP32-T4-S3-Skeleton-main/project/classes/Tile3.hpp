#pragma once
#include "BaseTile.hpp"

class OptionTile : public BaseTile {
public:
    OptionTile(lv_obj_t* parent);

private:
    lv_obj_t* title_;
};
