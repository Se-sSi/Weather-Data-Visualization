#include "Tile5.hpp"
#include <string>

HistoricalTile::HistoricalTile(lv_obj_t *parent)
{
    // --- Tile ---
    tile_ = lv_tileview_add_tile(parent, 2, 1, LV_DIR_ALL);

    // --- Title ---
    title_ = lv_label_create(tile_);
    lv_label_set_text(title_, "Historical Data");
    lv_obj_set_style_text_font(title_, &lv_font_montserrat_48, 0);
    lv_obj_align(title_, LV_ALIGN_TOP_MID, 0, 60);

    // --- Create dropdown ---
    lv_obj_t *dd = lv_dropdown_create(tile_);
    fill_dropdown_with_params(dd);
    lv_obj_set_size(dd, 200, 40);
    lv_obj_align(dd, LV_ALIGN_TOP_RIGHT, -10, 10);

    // Chart
    chart_ = lv_chart_create(tile_);
    lv_obj_set_size(chart_, 560, 320);
    lv_obj_align(chart_, LV_ALIGN_BOTTOM_MID, 0, -10);

    lv_chart_set_type(chart_, LV_CHART_TYPE_LINE);
    lv_chart_set_update_mode(chart_, LV_CHART_UPDATE_MODE_SHIFT);
    lv_chart_set_point_count(chart_, 30);
    lv_obj_set_style_line_rounded(chart_, true, LV_PART_ITEMS);

    // Series
    series_ = lv_chart_add_series(chart_, lv_palette_main(LV_PALETTE_BLUE), LV_CHART_AXIS_PRIMARY_Y);
    lv_chart_set_range(chart_, LV_CHART_AXIS_PRIMARY_Y, 180, 260);

    // Y-axis min / max
    lv_chart_set_range(chart_, LV_CHART_AXIS_PRIMARY_Y, 180, 260);

    // Example temp values (°C ×10)
    int temp_data_Humidity[30] = {
        223, 221, 218, 216, 215,
        217, 220, 224, 228, 232,
        231, 229, 224, 220, 219,
        222, 225, 229, 234, 230,
        228, 223, 220, 219, 221,
        224, 226, 229, 233, 236};

    update_chart(this->chart_, this->series_, temp_data_Humidity, 30);

    apply_bg_color(false);
    apply_text_color(title_, false);
}

void HistoricalTile::update_chart(lv_obj_t *chart, lv_chart_series_t *series, int *data, size_t length) // Kan ändras så att man skickar in en parameter som är namnet på det som ska visas t.ex. "humidity" och så anropar denna funktionen api funktionen
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

void HistoricalTile::fill_dropdown_with_params(lv_obj_t *dd)
{
    const char *arr[3] = {"Humidity", "Temperature", "Wind Speed"};
    size_t count = 3;

    std::string out;
    for (size_t i = 0; i < count; i++)
    {
        out += arr[i];
        if (i < count - 1)
            out += '\n';
    }

    lv_dropdown_set_options(dd, out.c_str());
}
