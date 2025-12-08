#pragma once

#include <lvgl.h>
#include <vector>
#include <string>

class HistoricalTile {
public:
    // Konstruktor
    HistoricalTile(lv_obj_t *parent);

    // --- FUNKTIONER FÖR TILES.CPP (FIXAR "NO MEMBER" FELEN) ---
    lv_obj_t* get_obj() { return tile_; } // Returnerar själva tile-objektet
    void apply_bg_color(bool dark);       // Hanterar dark mode bakgrund
    void apply_text_color(lv_obj_t* obj, bool dark); // Hanterar textfärg

    // --- VARIABLER SOM TILES.CPP BEHÖVER KOMMA ÅT ---
    lv_obj_t *title_; // Måste vara public för att Tiles.cpp ska kunna ändra färg på den

    // --- FUNKTIONER FÖR GRAFEN ---
    void replace_hist_data_from_heap(int *data, size_t length);

private:
    // UI-element
    lv_obj_t *tile_;
    lv_obj_t *chart_;
    lv_chart_series_t *series_;
    lv_obj_t *slider_;

    // Data
    std::vector<int> hist_data_;
    size_t window_size_;

    // Interna hjälpfunktioner
    void fill_dropdown_with_params(lv_obj_t *dd);
    void update_chart(lv_obj_t *chart, lv_chart_series_t *series, int *data, size_t length);
    void apply_window(size_t start_idx, const char* param);

    // Callbacks
    static void slider_event_cb(lv_event_t* e);
};