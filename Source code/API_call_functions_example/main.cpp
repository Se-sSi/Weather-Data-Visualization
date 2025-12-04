#include <curl/curl.h>
#include <nlohmann/json.hpp>
#include <iostream>
#include <string>
#include <vector>

size_t WriteCallback(void* contents, size_t size, size_t nmemb, std::string* s) {
    s->append((char*)contents, size * nmemb);
    return size * nmemb;
}

// Returns raw data as a string from the given URL
std::string get_raw_data(std::string url)
{
    CURL* curl = curl_easy_init();
    std::string response;
    if (curl) {
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);
        CURLcode res = curl_easy_perform(curl);
        curl_easy_cleanup(curl);
        
        return response;
    }
    else
    {
        return "ERROR";
    }
}

// Debug function to print JSON structure with types
void print_json(const nlohmann::json& j, int indent = 0) {
    const std::string pad(indent, ' ');

    if (j.is_object()) {
        for (auto it = j.begin(); it != j.end(); ++it) {
            std::cout << pad << it.key() << " : ";
            if (it.value().is_primitive()) {
                std::cout << it.value() << " (" << it.value().type_name() << ")\n";
            } else {
                std::cout << it.value().type_name() << "\n";
                print_json(it.value(), indent + 2);
            }
        }
    } else if (j.is_array()) {
        for (std::size_t i = 0; i < j.size(); ++i) {
            std::cout << pad << "[" << i << "] : ";
            if (j[i].is_primitive()) {
                std::cout << j[i] << " (" << j[i].type_name() << ")\n";
            } else {
                std::cout << j[i].type_name() << "\n";
                print_json(j[i], indent + 2);
            }
        }
    } else { // primitive (number, string, bool, null)
        std::cout << pad << j << " (" << j.type_name() << ")\n";
    }
}


// Converts epoch milliseconds to human-readable date-time string
std::string epoch_ms_to_datetime(long long ms_since_epoch)
{
    std::time_t t = static_cast<std::time_t>(ms_since_epoch / 1000);

    std::tm tm{};
#ifdef _WIN32
    localtime_s(&tm, &t);    // or gmtime_s for UTC
#else
    localtime_r(&t, &tm);    // or gmtime_r for UTC
#endif

    std::ostringstream oss;
    oss << std::put_time(&tm, "%Y-%m-%d %H:%M:%S");  // e.g. "2025-12-02 14:37:00"
    return oss.str();
}

// Data structure for historical samples
struct Historical_sample {
    long long time_ms;  // date from SMHI (ms since epoch)
    float value;     // temperature, humidity, etc.
};

// Data structure for forecast samples
struct Forecast_sample {
    std::string date;  // date from SMHI
    float temperature;
    int humidity;
    float wind_speed;
};

// Parses raw historical data JSON string into an array of Historical_sample
std::vector<Historical_sample> raw_historical_data_to_array(std::string data_string)
{
    nlohmann::json parsed = nlohmann::json::parse(data_string);

    std::vector<Historical_sample> data;

    const auto& arr = parsed.at("value");
    data.reserve(arr.size());
    for (const auto& item : arr)
    {
        Historical_sample sample;
        sample.time_ms = item.value("date", 0LL);
        sample.value = std::stof(item.value("value", "nan"));
        data.push_back(sample);
    }
    
    return data;
}

// Parses raw forecast data JSON string into an array of Forecast_sample
std::vector<Forecast_sample> raw_forecast_data_to_array(std::string data_string)
{
    nlohmann::json parsed = nlohmann::json::parse(data_string);

    std::vector<Forecast_sample> data;

    const auto& arr = parsed.at("timeSeries");
    data.reserve(arr.size());
    for (const auto& item : arr)
    {
        Forecast_sample sample;
        sample.date = item.value("time", std::string{});
        const auto& d = item.at("data");
        sample.temperature = d.value("air_temperature", 0.0f);
        sample.humidity    = d.value("relative_humidity", 0.0f);
        sample.wind_speed  = d.value("wind_speed", 0.0f);
        data.push_back(sample);
    }
    
    return data;
}


// Prints historical data samples
void print_historical_data(std::vector<Historical_sample> data)
{
    for (auto& sample : data)
    {
        std::cout << "Date: " << epoch_ms_to_datetime(sample.time_ms) << " Value: " << sample.value << "\n";
    }
}

// Prints forecast data samples
void print_forecast_data(std::vector<Forecast_sample> data)
{
    for (auto& sample : data)
    {
        std::cout << "Date: " << sample.date << " Temperature: " << sample.temperature << " Humidity: " << sample.humidity << " Wind speed: " << sample.wind_speed << "\n";
    }
}

// Maps city names to their corresponding IDs
int get_city_id(std::string city_name)
{
    if (city_name == "Karlskrona")       return 65090;
    if (city_name == "Stockholm")        return 98210;
    if (city_name == "Goteborg")         return 71420; 
    if (city_name == "Malmo")            return 52350;
    if (city_name == "Uppsala")          return 97510;
    if (city_name == "Vasteras")         return 96080;
    if (city_name == "orebro")           return 95160;
    if (city_name == "Linkoping")        return 85240;
    if (city_name == "Helsingborg")      return 62040;
    if (city_name == "Jonkoping")        return 74470;
    if (city_name == "Norrkoping")       return 86360;
}

// Maps data type names to their corresponding type IDs
int get_type_id(std::string type_name)
{
    if (type_name == "Temperature")         return 1;   // Temperature every hour
    if (type_name == "Median temperature")  return 2;   // median temperature every day 00:00
    if (type_name == "Wind direction")      return 3;   // median 10 min, every an hour
    if (type_name == "Wind speed")          return 4;   // wind speed median 10 min every an hour
    if (type_name == "Rain")                return 5;   // sum every day by hour 06:00 in mm
    if (type_name == "Humidity")            return 6;   // humidity every hour
    if (type_name == "Rain every hour")     return 7;   // rain every hour in mm
    if (type_name == "Pressure")            return 9;   // pressure every hour in hPa
    if (type_name == "Clarity")             return 12;  // clairity every hour in hPa
    if (type_name == "Comming weather")     return 13;  // Uppcomming weather? once per hour, 8 times per day?
    if (type_name == "Total cloudyness")    return 16;  // Total cloudyness, once per hour
    if (type_name == "Min temperature")     return 19;  // min temperature, once per day, 4 months
    if (type_name == "Max temperature")     return 20;  // max temperature, once per day, 4 months
    // etc
}


// Constructs the URL for historical data based on city ID and type ID
std::string get_city_historical_url(int city_id, int type_id)
{
    return "https://opendata-download-metobs.smhi.se/api/version/1.0/parameter/" + std::to_string(type_id) + "/station/" + std::to_string(city_id) + "/period/latest-months/data.json";
}

// Constructs the URL for forecast data based on latitude and longitude
std::string get_city_forecast_url(float lat, float lon)
{
    return "https://opendata-download-metfcst.smhi.se/api/category/snow1g/version/1/geotype/point/lon/" + std::to_string(lon) + "/lat/" +  std::to_string(lat) + "/data.json";
}


// Retrieves historical data for a given city and data type
std::vector<Historical_sample> get_city_historical_data(std::string city_name, std::string type_name)
{
    std::string url = get_city_historical_url(get_city_id(city_name), get_type_id(type_name));
    std::string raw_data = get_raw_data(url);
    return raw_historical_data_to_array(raw_data);
}


// Maps city names to their corresponding latitude
float get_city_lat(std::string city_name)
{
    if (city_name == "Karlskrona")       return 56.1612;
    if (city_name == "Stockholm")        return 59.3293;
    if (city_name == "Goteborg")         return 57.7089; 
    if (city_name == "Malmo")            return 55.6049;
    if (city_name == "Uppsala")          return 59.8586;
    if (city_name == "Vasteras")         return 59.6099;
    if (city_name == "orebro")           return 59.2753;
    if (city_name == "Linkoping")        return 58.4109;
    if (city_name == "Helsingborg")      return 56.0465;
    if (city_name == "Jonkoping")        return 57.7826;
    if (city_name == "Norrkoping")       return 58.5877;
}

// Maps city names to their corresponding longitude
float get_city_lon(std::string city_name)
{
    if (city_name == "Karlskrona")       return 15.5869;
    if (city_name == "Stockholm")        return 18.0686;
    if (city_name == "Goteborg")         return 11.9746; 
    if (city_name == "Malmo")            return 13.0038;
    if (city_name == "Uppsala")          return 17.6389;
    if (city_name == "Vasteras")         return 16.5448;
    if (city_name == "orebro")           return 15.2133;
    if (city_name == "Linkoping")        return 15.6167;
    if (city_name == "Helsingborg")      return 12.6945;
    if (city_name == "Jonkoping")        return 14.1618;
    if (city_name == "Norrkoping")       return 16.1771;
}


// Retrieves forecast data for a given city
std::vector<Forecast_sample> get_city_forecast_data(std::string city_name)
{
    std::string url = get_city_forecast_url(get_city_lat(city_name), get_city_lon(city_name));
    std::string raw_data = get_raw_data(url);
    return raw_forecast_data_to_array(raw_data);
}


int main() {
    // Forecast data example
    std::cout << std::endl << "Forecast data example:\n";
    std::string city_name_forecast = "Karlskrona";
    std::cout << "Enter city name (e.g., Stockholm, Goteborg, Malmo) or press Enter for default (Karlskrona): ";
    std::string input_city_forecast;
    std::getline(std::cin, input_city_forecast);
    
    if (!input_city_forecast.empty()) {
        city_name_forecast = input_city_forecast;
    }

    std::vector<Forecast_sample> array_data_forecast = get_city_forecast_data(city_name_forecast); // function to use in project
    std::cout << city_name_forecast << ":\n";
    print_forecast_data(array_data_forecast);



    // Historical data example
    std::cout << std::endl << "Historical data example:\n";
    std::string city_name_historical = "Karlskrona";
    std::cout << "Enter city name (e.g., Stockholm, Goteborg, Malmo) or press Enter for default (Karlskrona): ";
    std::string input_city_historical;
    std::getline(std::cin, input_city_historical);
    
    if (!input_city_historical.empty()) {
        city_name_historical = input_city_historical;
    }

    std::string type_name_historical = "Temperature";
    std::cout << "Enter data type (e.g., Temperature, Humidity) or press Enter for default (Temperature): ";
    std::string input_type_historical;
    std::getline(std::cin, input_type_historical);
    
    if (!input_type_historical.empty()) {
        type_name_historical = input_type_historical;
    }

    std::vector<Historical_sample> array_data_historical = get_city_historical_data(city_name_historical, type_name_historical); // function to use in project
    std::cout << city_name_historical << ":\n";
    print_historical_data(array_data_historical);



    std::cout << std::endl << "Press Enter to close.";
    std::cin.get();
    
    return 0;
}