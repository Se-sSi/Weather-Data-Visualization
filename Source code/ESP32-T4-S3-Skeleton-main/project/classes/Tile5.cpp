#include "Tile5.hpp"

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
    lv_dropdown_set_options(dd, "Humidity\nTemperature\nWind Speed");
    lv_obj_set_size(dd, 200, 40);
    lv_obj_align(dd, LV_ALIGN_TOP_RIGHT, -10, 10);

    // *************************************************************
    //                       CHART WIDGET
    // *************************************************************

    lv_obj_t *chart = lv_chart_create(tile_);
    lv_obj_set_size(chart, 560, 320);
    lv_obj_align(chart, LV_ALIGN_BOTTOM_MID, 0, -10);

    lv_chart_set_type(chart, LV_CHART_TYPE_LINE);
    lv_chart_set_update_mode(chart, LV_CHART_UPDATE_MODE_SHIFT);
    lv_chart_set_point_count(chart, 30);

    // Enable line smoothing (LVGL v8 style-based method)
    lv_obj_set_style_line_rounded(chart, true, LV_PART_ITEMS);

    // --- Add data series ---
    lv_chart_series_t *ser = lv_chart_add_series(
        chart,
        lv_palette_main(LV_PALETTE_BLUE),
        LV_CHART_AXIS_PRIMARY_Y);

    // Y-axis min / max
    lv_chart_set_range(chart, LV_CHART_AXIS_PRIMARY_Y, 180, 260);

    // Example temp values (°C ×10)
    int temp_data[30] = {
        223, 221, 218, 216, 215,
        217, 220, 224, 228, 232,
        231, 229, 224, 220, 219,
        222, 225, 229, 234, 230,
        228, 223, 220, 219, 221,
        224, 226, 229, 233, 236};

    for (int i = 0; i < 30; i++)
    {
        ser->y_points[i] = temp_data[i];
    }

    lv_chart_refresh(chart);

    apply_bg_color(false);
    apply_text_color(title_, false);
}
