#include "Tile4.hpp"
#include "../../src/Cogwheel.hpp"
#include "../../src/Cloudy.h"
#include "../../src/Clear.h"
#include "../../src/HeavyRain.h"
#include "../../src/LightRain.h"
#include "../../src/Snow.h"
#include "../../src/Thunderstorm.h"
#include "../../src/MostlyClear.h"
#include "../../src/Fog.h"


WeekTile::WeekTile(lv_obj_t* parent)
{
    tile_ = lv_tileview_add_tile(parent, 0, 1, LV_DIR_ALL);
    
    title_ = lv_label_create(tile_);
    lv_label_set_text(title_, "7 Day Forecast");
    lv_obj_set_style_text_font(title_, &lv_font_montserrat_48, 0);
    lv_obj_align(title_, LV_ALIGN_TOP_MID, 0, 60);

    lv_obj_t* weekContainer = lv_obj_create(tile_); // <-- ändrat från parent till tile_
    // Hämta nuvarande Y-position och höjd
    //lv_coord_t old_y = lv_obj_get_y(weekContainer);
    //lv_coord_t old_h = lv_obj_get_height(weekContainer);

    
    //lv_obj_set_height(weekContainer, lv_pct(80));  // eller annan ny höjd

    lv_obj_set_size(weekContainer, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
    lv_obj_set_style_bg_opa(weekContainer, LV_OPA_TRANSP, 0);
    lv_obj_set_style_border_width(weekContainer, 0, 0);
    lv_obj_align(weekContainer, LV_ALIGN_TOP_MID, 0, 120);

    // Beräkna skillnaden och flytta objektet uppåt
    //lv_coord_t new_h = lv_obj_get_height(weekContainer);
    //lv_obj_set_y(weekContainer, old_y + (old_h - new_h));

    //lv_obj_set_flex_flow(weekContainer, LV_FLEX_FLOW_ROW);
    lv_obj_set_flex_flow(weekContainer, LV_FLEX_FLOW_COLUMN);

    lv_obj_set_flex_align(weekContainer, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);

    const char* weekDays[7] = {"Mon", "Tue", "Wed", "Thu", "Fri", "Sat", "Sun"};
    const char* temperatures[7] = {"12°C", "7°C", "0°C", "18°C", "20°C", "16°C", "14°C"};
    const void* symbols[7] = { &Cloudy, &Fog, &Snow, &HeavyRain, &LightRain, &Thunderstorm, &Clear};



    for(int i = 0; i < 7; i++) 
    {
    dayContainer[i] = lv_obj_create(weekContainer);
    lv_obj_set_size(dayContainer[i], 400, 200); // fast bredd eller procent
    lv_obj_set_style_pad_all(dayContainer[i], 8, 0);
    lv_obj_set_style_bg_color(dayContainer[i], lv_color_make(220, 235, 255), 0);
    lv_obj_set_style_radius(dayContainer[i], 10, 0);

    static lv_style_t style_day;
    static lv_style_t style_temp;

    lv_style_init(&style_day);
    lv_style_init(&style_temp);

    lv_style_set_text_font(&style_day, &lv_font_montserrat_34);
    lv_style_set_text_font(&style_temp, &lv_font_montserrat_48);

    label_day[i] = lv_label_create(dayContainer[i]);
    lv_label_set_text(label_day[i], weekDays[i]);
    lv_obj_add_style(label_day[i], &style_day, 0);
    lv_obj_align(label_day[i], LV_ALIGN_CENTER, 70, 20);

    label_temp[i] = lv_label_create(dayContainer[i]);
    lv_label_set_text(label_temp[i], temperatures[i]);
    lv_obj_add_style(label_temp[i], &style_temp, 0);
    lv_obj_align(label_temp[i], LV_ALIGN_TOP_MID, 70, 50);

    icon_weather[i] = lv_img_create(dayContainer[i]);
    lv_img_set_src(icon_weather[i], symbols[i]);            // Använd C-arrayen
    lv_obj_align(icon_weather[i], LV_ALIGN_BOTTOM_MID, -90, -15);  // Placera längst ner
    }


    apply_bg_color(false);
    apply_text_color(title_, false);

    lv_obj_add_event_cb(tile_, WeekTile::gesture_cb, LV_EVENT_GESTURE, this);

}


void WeekTile::gesture_cb(lv_event_t* e)
{
    WeekTile* self = static_cast<WeekTile*>(lv_event_get_user_data(e));

    lv_dir_t dir = lv_indev_get_gesture_dir(lv_indev_get_act());

    if (dir == LV_DIR_TOP)
    {
        BaseTile::ShowGlobalOverlay("No Internet!", lv_color_hex(0xe74c3c));
    }
}
