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
#include "../../src/SMHIClient.hpp"
#include <ArduinoJson.h>

WeekTile::WeekTile(lv_obj_t* parent)
{
    SMHIClient::begin();

    // --- Tile ---
    tile_ = lv_tileview_add_tile(parent, 0, 1, LV_DIR_RIGHT);
    
    // --- Title ---
    title_ = lv_label_create(tile_);
    lv_label_set_text(title_, "7 Day Forecast");
    lv_obj_set_style_text_font(title_, &lv_font_montserrat_48, 0);
    lv_obj_align(title_, LV_ALIGN_TOP_MID, 0, 60);

    // --- Week Container ---
    lv_obj_t* weekContainer = lv_obj_create(tile_);
    lv_obj_set_size(weekContainer, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
    lv_obj_set_style_bg_opa(weekContainer, LV_OPA_TRANSP, 0);
    lv_obj_set_style_border_width(weekContainer, 0, 0);
    lv_obj_align(weekContainer, LV_ALIGN_TOP_MID, 0, 120);

    lv_obj_set_flex_flow(weekContainer, LV_FLEX_FLOW_COLUMN);
    lv_obj_set_flex_align(weekContainer, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);

    // --- Variables In Containers --- (will be filled from API)
    const char* weekDays[7] = {"", "", "", "", "", "", ""};
    const char* temperatures[7] = {"", "", "", "", "", "", ""};
    const void* symbols[7] = {nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr};

    // --- One Day Container ---
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

    // --- Day ---
    label_day[i] = lv_label_create(dayContainer[i]);
    lv_label_set_text(label_day[i], weekDays[i]); // initially empty
    lv_obj_add_style(label_day[i], &style_day, 0);
    lv_obj_align(label_day[i], LV_ALIGN_CENTER, 70, 20);

    // --- Temp ---
    label_temp[i] = lv_label_create(dayContainer[i]);
    lv_label_set_text(label_temp[i], temperatures[i]); // initially empty
    lv_obj_add_style(label_temp[i], &style_temp, 0);
    lv_obj_align(label_temp[i], LV_ALIGN_TOP_MID, 70, 50);

    // --- Icon ---
    icon_weather[i] = lv_img_create(dayContainer[i]);
    lv_img_set_src(icon_weather[i], symbols[i]);            // initially null
    lv_obj_align(icon_weather[i], LV_ALIGN_BOTTOM_MID, -90, -15);  // Placera längst ner
    }

    // Setting the tile background color and tile text colors
    apply_bg_color(false);
    apply_text_color(title_, false);

    // --- Events ---
    lv_obj_add_event_cb(tile_, WeekTile::gesture_cb, LV_EVENT_GESTURE, this);

    // --- Timer: fetch forecast and update the UI (placed after UI creation) ---
    lv_timer_t* t = lv_timer_create([](lv_timer_t* timer){
        WeekTile* self = (WeekTile*)timer->user_data;
        String raw = SMHIClient::fetchForecast("Karlskrona");
        if (raw.length() == 0) {
            return;
        }

        DynamicJsonDocument doc(48 * 1024);
        DeserializationError err = deserializeJson(doc, raw);
        if (err) return;

        JsonArray ts = doc["timeSeries"].as<JsonArray>();
        if (ts.isNull()) return;

        // collect up to 7 distinct dates at hour 12
        int found = 0;
        const int MAXD = 7;
        char seenDates[MAXD][11]; // "YYYY-MM-DD"
        for (int i = 0; i < MAXD; ++i) seenDates[i][0] = '\0';

        for (JsonObject item : ts) {
            if (found >= MAXD) break;

            // time field may be "validTime" or "time"
            const char* timestr = item["validTime"] | item["time"] | "";
            if (!timestr || strlen(timestr) < 13) continue;

            int y=0, m=0, d=0, h=0;
            if (sscanf(timestr, "%4d-%2d-%2dT%2d", &y, &m, &d, &h) < 4) continue;

            if (h != 12) continue; // only noon

            char dateKey[11];
            snprintf(dateKey, sizeof(dateKey), "%04d-%02d-%02d", y, m, d);

            // check if date already taken
            bool already = false;
            for (int k=0;k<found;k++) if (strcmp(seenDates[k], dateKey) == 0) { already = true; break; }
            if (already) continue;

            // extract temperature and Wsymb2 if present
            float ta = 0.0f;
            bool gotTemp = false;
            int wsymb = -1;

            if (item.containsKey("data") && item["data"].is<JsonObject>()) {
                ta = item["data"]["air_temperature"] | item["data"]["t"] | 0.0f;
                gotTemp = true;
            } else if (item.containsKey("parameters") && item["parameters"].is<JsonArray>()) {
                for (JsonObject p : item["parameters"].as<JsonArray>()) {
                    const char* name = p["name"] | p["param"] | "";
                    if (name && (strcmp(name, "t")==0 || strcmp(name, "air_temperature")==0 || strcmp(name,"temperature")==0)) {
                        ta = (p["values"][0] | p["value"] | 0.0f);
                        gotTemp = true;
                    } else if (name && (strcmp(name, "Wsymb2")==0 || strcmp(name, "Wsymb")==0)) {
                        // value may be number or string
                        wsymb = p["values"][0] | p["value"] | -1;
                    }
                }
            }

            if (!gotTemp) {
                // fallback: try top-level fields
                ta = item["t"] | item["air_temperature"] | 0.0f;
            }

            // update UI (we are in LVGL timer, safe)
            lv_label_set_text(self->label_day[found], dateKey);

            char tempbuf[16];
            snprintf(tempbuf, sizeof(tempbuf), "%d°C", (int)round(ta));
            lv_label_set_text(self->label_temp[found], tempbuf);

            // map wsymb to icon (approx mapping)
            const void* icon = nullptr;
            if (wsymb > 0) {
                if (wsymb == 1) icon = &Clear;
                else if (wsymb <= 4) icon = &MostlyClear;      // 2-4 mostly clear/variable
                else if (wsymb <= 6) icon = &Cloudy;           // 5-6 cloudy/overcast
                else if (wsymb == 7) icon = &Fog;              // fog
                else if (wsymb >= 8 && wsymb <= 11) icon = &LightRain;  // showers
                else if (wsymb >= 12 && wsymb <= 16) icon = &HeavyRain; // heavier rain/thunder
                else if (wsymb >= 17 && wsymb <= 20) icon = &Snow;      // snow-ish
                else icon = &Cloudy;
            }

            if (icon) lv_img_set_src(self->icon_weather[found], icon);

            // mark date seen
            strncpy(seenDates[found], dateKey, sizeof(seenDates[found]) - 1);
            seenDates[found][10] = '\0';
            found++;
        }

        // if you want repeated updates, don't delete timer
        lv_timer_del(timer);
    }, 1000, this);
}

// Recognises the swipe motion
void WeekTile::gesture_cb(lv_event_t* e)
{
    WeekTile* self = static_cast<WeekTile*>(lv_event_get_user_data(e));

    lv_dir_t dir = lv_indev_get_gesture_dir(lv_indev_get_act());

    if (dir == LV_DIR_TOP)
    {
        BaseTile::ShowGlobalOverlay("No Internet!", lv_color_hex(0xe74c3c));
    }
}
