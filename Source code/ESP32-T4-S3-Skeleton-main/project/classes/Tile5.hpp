#include "BaseTile.hpp"

class HistoricalTile : public BaseTile
{
public:
    HistoricalTile(lv_obj_t *parent);
    lv_obj_t *title_;
    lv_obj_t *chart_;
    lv_chart_series_t *series_;

private:
    static void update_chart(lv_obj_t *chart, lv_chart_series_t *series, int *data, size_t length);
    void fill_dropdown_with_params(lv_obj_t *dd);
};
