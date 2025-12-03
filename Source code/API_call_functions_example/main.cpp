#include <curl/curl.h>
#include <nlohmann/json.hpp>
#include <iostream>
#include <string>
#include <vector>

size_t WriteCallback(void* contents, size_t size, size_t nmemb, std::string* s) {
    s->append((char*)contents, size * nmemb);
    return size * nmemb;
}

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

struct Sample {
    long long time_ms;  // date from SMHI (ms since epoch)
    float value;     // temperature, humidity, etc.
};


std::vector<Sample> raw_data_to_array(std::string data_string)
{
    nlohmann::json parsed = nlohmann::json::parse(data_string);

    std::vector<Sample> data;

    const auto& arr = parsed.at("value");
    data.reserve(arr.size());
    for (const auto& item : arr)
    {
        Sample sample;
        sample.time_ms = item.value("date", 0LL);
        sample.value = std::stof(item.value("value", "nan"));
        data.push_back(sample);
    }
    
    return data;
}

void print_data(std::vector<Sample> data)
{
    for (auto& sample : data)
    {
        std::cout << "Date: " << epoch_ms_to_datetime(sample.time_ms) << " Value: " << sample.value << "\n";
    }
}


int get_city_id(std::string city_name)
{
    if (city_name == "Karlskrona")       return 65090;
    if (city_name == "Stockholm")        return 98210;
    if (city_name == "Göteborg")         return 71420; 
    if (city_name == "Malmö")            return 52350;
    if (city_name == "Uppsala")          return 97510;
    if (city_name == "Västerås")         return 96080;
    if (city_name == "Örebro")           return 95160;
    if (city_name == "Linköping")        return 85240;
    if (city_name == "Helsingborg")      return 62040;
    if (city_name == "Jönköping")        return 74470;
    if (city_name == "Norrköping")       return 86360;
}

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

std::string get_city_url(int city_id, int type_id)
{
    return "https://opendata-download-metobs.smhi.se/api/version/1.0/parameter/" + std::to_string(type_id) + "/station/" + std::to_string(city_id) + "/period/latest-months/data.json";
}

std::vector<Sample> get_city_data(std::string city_name, std::string type_name)
{
    std::string url = get_city_url(get_city_id(city_name), get_type_id(type_name));
    std::string raw_data = get_raw_data(url);
    return raw_data_to_array(raw_data);
}


int main() {
    std::string city_name = "Karlskrona";
    std::cout << "Enter city name (e.g., Stockholm, Göteborg, Malmö) or press Enter for default (Karlskrona): ";
    std::string input;
    std::getline(std::cin, input);
    
    if (!input.empty()) {
        city_name = input;
    }

    std::string type_name = "Temperature";
    std::cout << "Enter type name (e.g., Temperature, Humidity, Wind speed) or press Enter for default (Temperature): ";
    std::getline(std::cin, input);
    
    if (!input.empty()) {
        type_name = input;
    }

    std::vector<Sample> array_data = get_city_data(city_name, type_name); // function to use in project
    std::cout << type_name << " data for " << city_name << ":\n";

    print_data(array_data);

    std::cout << std::endl << "Press Enter to close.";
    std::cin.get();
    return 0;
}