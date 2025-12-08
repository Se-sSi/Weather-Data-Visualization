#include "Tile5.hpp"
#include <string>
#include <vector>
#include <climits>
#include "../../src/SMHIClient.hpp"
#include "../../src/AppState.hpp"
#include <ArduinoJson.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include <map>
#include <ctime>

// --- Hjälpstrukturer ---
struct AsyncHistUpdate {
    HistoricalTile* self;
    int* data;
    size_t length;
};

// --- Callback för Y-axel formatering ---
static void chart_draw_event_cb(lv_event_t * e)
{
    lv_obj_draw_part_dsc_t * dsc = lv_event_get_draw_part_dsc(e);
    if(lv_obj_draw_part_check_type(dsc, &lv_chart_class, LV_CHART_DRAW_PART_TICK_LABEL)) {
        if(dsc->id == LV_CHART_AXIS_PRIMARY_Y && dsc->text) {
            int value = dsc->value;
            lv_snprintf(dsc->text, dsc->text_length, "%d.%d", value / 10, abs(value % 10));
        }
    }
}

// --- Async Update ---
static void apply_hist_update(void* arg)
{
    AsyncHistUpdate* a = static_cast<AsyncHistUpdate*>(arg);
    if (!a) return;
    HistoricalTile* self = a->self;
    if (self) self->replace_hist_data_from_heap(a->data, a->length);
    else free(a->data);
    free(a);
}

// --- Background Task ---
static void hist_fetch_task(void* pv)
{
    HistoricalTile* self = static_cast<HistoricalTile*>(pv);
    if (!self) { vTaskDelete(NULL); return; }

    const char* city = app_get_city();

    // FIX: Använd JsonDocument istället för DynamicJsonDocument (ArduinoJson v7)
    JsonDocument doc;

    // Anropa SMHI (Se till att SMHIClient också är uppdaterad, se nedan)
    bool success = SMHIClient::fetchHistoricalToDoc(city, "Temperature", doc);

    if (!success) {
        Serial.println("Fetch failed");
        vTaskDelete(NULL);
        return;
    }

    JsonArray arr = doc["value"].as<JsonArray>();
    if (arr.isNull() || arr.size() == 0) {
        Serial.println("No values");
        vTaskDelete(NULL);
        return;
    }

    std::map<std::string, double> daily;
    for (JsonVariant vv : arr) {
        JsonObject o = vv.as<JsonObject>();
        long long date_ms = o["date"].as<long long>();
        time_t secs = (time_t)((date_ms / 1000LL) + 3600);
        struct tm tm;
        gmtime_r(&secs, &tm);
        char key[12];
        snprintf(key, sizeof(key), "%04d-%02d-%02d", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday);

        double val = 0.0;
        if (o["value"].is<const char*>()) val = atof(o["value"].as<const char*>());
        else val = o["value"].as<double>();

        daily[key] = val;
    }

    size_t n = daily.size();
    if (n > 0) {
        int* buf = (int*)malloc(sizeof(int) * n);
        if (buf) {
            int i = 0;
            for (auto const& [key, val] : daily) buf[i++] = (int)round(val * 10.0);

            AsyncHistUpdate* a = (AsyncHistUpdate*)malloc(sizeof(AsyncHistUpdate));
            a->self = self;
            a->data = buf;
            a->length = n;
            lv_async_call(apply_hist_update, a);
        }
    }
    vTaskDelete(NULL);
}

// ============================================
// HistoricalTile Implementation
// ============================================

HistoricalTile::HistoricalTile(lv_obj_t *parent)
{
    SMHIClient::begin();

    tile_ = lv_tileview_add_tile(parent, 2, 1, LV_DIR_LEFT);

    title_ = lv_label_create(tile_);
    lv_label_set_text(title_, "Historical Temp");
    lv_obj_set_style_text_font(title_, &lv_font_montserrat_48, 0);
    lv_obj_align(title_, LV_ALIGN_TOP_MID, 0, 20);

    lv_obj_t *dd = lv_dropdown_create(tile_);
    fill_dropdown_with_params(dd);
    lv_obj_set_size(dd, 180, 40);
    lv_obj_align(dd, LV_ALIGN_TOP_RIGHT, -10, 10);

    chart_ = lv_chart_create(tile_);
    lv_obj_set_size(chart_, 600, 280);
    lv_obj_align(chart_, LV_ALIGN_CENTER, 0, 20);
    lv_chart_set_type(chart_, LV_CHART_TYPE_LINE);
    lv_chart_set_update_mode(chart_, LV_CHART_UPDATE_MODE_CIRCULAR);
    lv_chart_set_point_count(chart_, 30);

    // Axlar och Padding
    lv_obj_set_style_pad_left(chart_, 60, 0);
    lv_obj_set_style_pad_bottom(chart_, 40, 0);
    lv_obj_set_style_pad_right(chart_, 20, 0);
    lv_chart_set_axis_tick(chart_, LV_CHART_AXIS_PRIMARY_Y, 10, 5, 6, 2, true, 40);
    lv_chart_set_axis_tick(chart_, LV_CHART_AXIS_PRIMARY_X, 10, 5, 5, 1, true, 20);
    lv_obj_add_event_cb(chart_, chart_draw_event_cb, LV_EVENT_DRAW_PART_BEGIN, NULL);

    series_ = lv_chart_add_series(chart_, lv_palette_main(LV_PALETTE_BLUE), LV_CHART_AXIS_PRIMARY_Y);

    slider_ = lv_slider_create(tile_);
    lv_obj_set_size(slider_, 400, 20);
    lv_obj_align(slider_, LV_ALIGN_BOTTOM_MID, 0, -20);
    lv_slider_set_range(slider_, 0, 100);
    lv_obj_add_event_cb(slider_, slider_event_cb, LV_EVENT_VALUE_CHANGED, this);

    window_size_ = lv_chart_get_point_count(chart_);

    // Initiera färger (Nu finns funktionerna tack vare uppdateringen i .hpp)
    apply_bg_color(false);
    apply_text_color(title_, false);

    lv_timer_t* t = lv_timer_create([](lv_timer_t* timer){
        HistoricalTile* self = (HistoricalTile*)timer->user_data;
        xTaskCreate(hist_fetch_task, "hist_fetch", 12*1024, self, 1, NULL);
        lv_timer_del(timer);
    }, 500, this);
}

// --- IMPLEMENTATION AV FUNKTIONERNA SOM SAKNADES ---

void HistoricalTile::apply_bg_color(bool dark) {
    if (dark) {
        lv_obj_set_style_bg_color(tile_, lv_color_hex(0x000000), LV_PART_MAIN);
    } else {
        lv_obj_set_style_bg_color(tile_, lv_color_hex(0xFFFFFF), LV_PART_MAIN);
    }
}

void HistoricalTile::apply_text_color(lv_obj_t* obj, bool dark) {
    if (!obj) return;
    if (dark) {
        lv_obj_set_style_text_color(obj, lv_color_hex(0xFFFFFF), 0);
    } else {
        lv_obj_set_style_text_color(obj, lv_color_hex(0x000000), 0);
    }
}

// --- Slider & Graph Logic ---

void HistoricalTile::slider_event_cb(lv_event_t* e)
{
    lv_obj_t* s = lv_event_get_target(e);
    HistoricalTile* self = (HistoricalTile*)lv_event_get_user_data(e);
    if (!s || !self || self->hist_data_.empty()) return;

    int v = lv_slider_get_value(s);
    size_t total = self->hist_data_.size();
    size_t start_idx = 0;

    if (total > self->window_size_) {
        size_t max_start = total - self->window_size_;
        start_idx = (size_t)((uint64_t)v * max_start / 100);
    }
    self->apply_window(start_idx, "Temperature");
}

void HistoricalTile::apply_window(size_t start_idx, const char* param)
{
    if (hist_data_.empty()) return;
    size_t total = hist_data_.size();
    size_t count = window_size_;

    if (start_idx + count > total) {
        if (total >= count) start_idx = total - count;
        else { start_idx = 0; count = total; }
    }

    int min_val = INT_MAX, max_val = INT_MIN;
    for (size_t i = 0; i < count; i++) {
        int val = hist_data_[start_idx + i];
        if (val < min_val) min_val = val;
        if (val > max_val) max_val = val;
        lv_chart_set_value_by_id(chart_, series_, i, val);
    }
    for (size_t i = count; i < window_size_; i++) {
        lv_chart_set_value_by_id(chart_, series_, i, LV_CHART_POINT_NONE);
    }

    if (min_val == INT_MAX) { min_val = 0; max_val = 100; }
    else if (min_val == max_val) { min_val -= 10; max_val += 10; }

    int padding = 10;
    lv_chart_set_range(chart_, LV_CHART_AXIS_PRIMARY_Y, min_val - padding, max_val + padding);
    lv_chart_refresh(chart_);
}

void HistoricalTile::replace_hist_data_from_heap(int *data, size_t length)
{
    hist_data_.clear();
    hist_data_.reserve(length);
    for (size_t i = 0; i < length; ++i) hist_data_.push_back(data[i]);
    free(data);

    lv_slider_set_value(slider_, 100, LV_ANIM_ON);
    size_t start = (length > window_size_) ? length - window_size_ : 0;
    apply_window(start, "Temperature");
    Serial.printf("Graph updated with %d points\n", (int)length);
}

void HistoricalTile::fill_dropdown_with_params(lv_obj_t *dd) {
     lv_dropdown_set_options(dd, "Temperature\nHumidity\nWind");
}

void HistoricalTile::update_chart(lv_obj_t *chart, lv_chart_series_t *series, int *data, size_t length) {}