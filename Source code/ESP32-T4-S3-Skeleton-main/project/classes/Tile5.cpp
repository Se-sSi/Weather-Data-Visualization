#include "Tile5.hpp"
#include "SMHIClient.hpp"
#include <string>

HistoricalTile::HistoricalTile(lv_obj_t *parent)
{
    const int HISTORICAL_DATA_POINTS = 130;

    // --- Tile ---
    tile_ = lv_tileview_add_tile(parent, 2, 1, LV_DIR_LEFT);

    // --- Title ---
    title_ = lv_label_create(tile_);
    lv_label_set_text(title_, "Historical Data");
    lv_obj_set_style_text_font(title_, &lv_font_montserrat_30, 0);
    lv_obj_align(title_, LV_ALIGN_TOP_MID, 0, 50);

    // --- Create ---
    lv_obj_t *dd = lv_dropdown_create(tile_);
    fill_dropdown_with_params(dd);
    lv_obj_set_size(dd, 200, 40);
    lv_obj_align(dd, LV_ALIGN_TOP_RIGHT, -10, 10);

    // --- Chart ---
    chart_ = lv_chart_create(tile_);
    lv_obj_set_size(chart_, 560, 300);
    lv_obj_align(chart_, LV_ALIGN_BOTTOM_MID, 0, -30);

    lv_chart_set_type(chart_, LV_CHART_TYPE_LINE);
    lv_chart_set_update_mode(chart_, LV_CHART_UPDATE_MODE_SHIFT);
    lv_chart_set_point_count(chart_, HISTORICAL_DATA_POINTS);
    lv_obj_set_style_line_rounded(chart_, true, LV_PART_ITEMS);

    // --- Slider ---
    slider_ = lv_slider_create(tile_);
    lv_slider_set_range(slider_, 0, HISTORICAL_DATA_POINTS - 1);
    lv_obj_set_width(slider_, 560);
    lv_obj_align(slider_, LV_ALIGN_BOTTOM_MID, 0, 0);   // placerad under grafen

    cursor_line_ = lv_obj_create(chart_);
    lv_obj_set_size(cursor_line_, 2, lv_obj_get_height(chart_));
    lv_obj_set_style_bg_color(cursor_line_, lv_palette_main(LV_PALETTE_RED), 0);
    lv_obj_set_style_bg_opa(cursor_line_, LV_OPA_COVER, 0);
    lv_obj_add_flag(cursor_line_, LV_OBJ_FLAG_IGNORE_LAYOUT); 
    lv_obj_align(cursor_line_, LV_ALIGN_TOP_LEFT, 0, 0);

    value_label_ = lv_label_create(tile_);
    lv_label_set_text(value_label_, "");
    lv_obj_align(value_label_, LV_ALIGN_BOTTOM_MID, 0, 10);

    lv_obj_add_event_cb(slider_, [](lv_event_t *e){
    HistoricalTile *self = static_cast<HistoricalTile*>(lv_event_get_user_data(e));
    self->on_slider_changed(e);
    }, LV_EVENT_VALUE_CHANGED, this);

    // --- Series ---
    // Used in creating the chart object
    series_ = lv_chart_add_series(chart_, lv_palette_main(LV_PALETTE_BLUE), LV_CHART_AXIS_PRIMARY_Y);

    // Example temp values (°C ×10)
    int temperature_data[HISTORICAL_DATA_POINTS] = {0};


    // Fetch temperature data
    SMHIClient::begin();
    std::vector<float> temperature_data_float = SMHIClient::fetchHistoricalTemperatures("Karlskrona", "Temperature");

    int i = 0;
    int ymin = 1000;
    int ymax = -1000;
    for(float temp: temperature_data_float) {
        temperature_data[i] = (int) temp*10;
        if(temperature_data[i]>ymax) ymax = temperature_data[i];
        if(temperature_data[i]<ymin) ymin = temperature_data[i];
        
        if(++i >= sizeof(temperature_data)) break;
    }
    
    lv_chart_set_range(chart_, LV_CHART_AXIS_PRIMARY_Y, ymin, ymax);

    // Own created function to update the chart
    update_chart(chart_, series_, temperature_data, HISTORICAL_DATA_POINTS); //sizeof(temperature_data));

    // Setting the tile background color and tile text colors
    apply_bg_color(false);
    apply_text_color(title_, false);
}

void HistoricalTile::on_slider_changed(lv_event_t *e)
{
    HistoricalTile *self = static_cast<HistoricalTile*>(lv_event_get_user_data(e));
    int idx = lv_slider_get_value(self->slider_);

    // Skydda mot out-of-range
    if (idx < 0 || idx >= lv_chart_get_point_count(self->chart_)) return;

    // Hämta y-värde
    int y = self->series_->y_points[idx];

    // Uppdatera label
    lv_label_set_text_fmt(self->value_label_, "Value: %.1f°C", y / 10.0f);

    // Flytta cursor-linjen
    int chart_w = lv_obj_get_width(self->chart_);
    int point_count = lv_chart_get_point_count(self->chart_);

    int x = (idx * chart_w) / point_count;
    lv_obj_set_x(self->cursor_line_, x);
}


// Function that is supposed to update the series with the data and refreshes the chart
void HistoricalTile::update_chart(lv_obj_t *chart, lv_chart_series_t *series, int *data, size_t length)
{
    if (!chart || !series)
        return;

    size_t max_points = lv_chart_get_point_count(chart);
    size_t count = (length < max_points) ? length : max_points;

    for (size_t i = 0; i < count; i++)
    {
        series->y_points[i] = data[i];
    }

    // Fill remaining points with 0
    for (size_t i = count; i < max_points; i++)
    {
        series->y_points[i] = 0;
    }

    lv_chart_refresh(chart);
}

// Creates the string needed for the dropdown
void HistoricalTile::fill_dropdown_with_params(lv_obj_t *dd)
{
    const char *arr[4] = {"Temperature", "Humidity", "Wind Speed", "Air Pressure"}; //REDIGERA DETTA UTAN TEST, KAN VARA FEL HÄR (LA TILL DEN AIR PRESSURE DÅ DET OCKSÅ ÄR EN PARAMETER SOM BEHÖVS)
    size_t count = 4; //REDIGERA DETTA UTAN TEST, KAN VARA FEL HÄR (FRÅN 3 -> 4)

    std::string out;
    for (size_t i = 0; i < count; i++)
    {
        out += arr[i];
        if (i < count - 1)
            out += '\n';
    }

    lv_dropdown_set_options(dd, out.c_str());
}
