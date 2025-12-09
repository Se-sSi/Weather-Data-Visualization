#pragma once

#include <string>
#include <vector>
#include <nlohmann/json.hpp>

// ------------------------
// Data structures
// ------------------------

// Historical data sample
struct Historical_sample
{
    long long time_ms; // date from SMHI (ms since epoch)
    float value;       // temperature, humidity, etc.
};

// Forecast data sample
struct Forecast_sample
{
    std::string date; // date from SMHI
    float temperature;
    int humidity;
    float wind_speed;
};

// ------------------------
// Utility functions
// ------------------------

// Callback for CURL to write data
size_t WriteCallback(void *contents, size_t size, size_t nmemb, std::string *s);

// Get raw data from a URL as a string
std::string get_raw_data(std::string url);

// Debug: print JSON structure with types
void print_json(const nlohmann::json &j, int indent = 0);

// ------------------------
// Historical data functions
// ------------------------

// Parse raw historical data JSON into array of Historical_sample
std::vector<Historical_sample> raw_historical_data_to_array(std::string data_string);

// Get historical data for a city and type
std::vector<Historical_sample> get_city_historical_data(std::string city_name, std::string type_name);

// Generate URL for historical data
std::string get_city_historical_url(int city_id, int type_id);

// ------------------------
// Forecast data functions
// ------------------------

// Parse raw forecast data JSON into array of Forecast_sample
std::vector<Forecast_sample> raw_forecast_data_to_array(std::string data_string);

// Print forecast data
void print_forecast_data(std::vector<Forecast_sample> data);

// Get forecast data for a city
std::vector<Forecast_sample> get_city_forecast_data(std::string city_name);

// Generate URL for forecast data based on latitude and longitude
std::string get_city_forecast_url(float lat, float lon);

// ------------------------
// City / Type mappings
// ------------------------

// Map city name to SMHI station ID
int get_city_id(std::string city_name);

// Map data type name to type ID
int get_type_id(std::string type_name);

// Get city latitude / longitude
float get_city_lat(std::string city_name);
float get_city_lon(std::string city_name);
