#include "SMHIClient.hpp"
#include <HTTPClient.h>
#include <ArduinoJson.h>

void SMHIClient::begin() { /* nothing for now */ }

static String http_get(const String& url) {
  HTTPClient http;
  http.begin(url);
  int code = http.GET();
  if (code != HTTP_CODE_OK) {
    http.end();
    return String();
  }
  String body = http.getString();
  http.end();
  return body;
}

// Created with AI help
String SMHIClient::fetchForecast(const char* city) {
  // map city to lat/lon (copy of mapping in API example)
  float lat = 56.1612, lon = 15.5869; // default Karlskrona; extend mapping if needed
  if (strcmp(city, "Goteborg") == 0) { lat = 57.7089; lon = 11.9746; }
  // ... add others as in API_call_functions_example/main.cpp
  String url = String("https://opendata-download-metfcst.smhi.se/api/category/snow1g/version/1/geotype/point/lon/") +
               String(lon, 6) + "/lat/" + String(lat, 6) + "/data.json";
  return http_get(url);
}

// Created with AI help
String SMHIClient::fetchHistorical(const char* city, const char* type) { 
  // map city -> station id and type -> id (copy mappings from API example)
  int station = 65090; // default Karlskrona
  if (strcmp(city, "Goteborg") == 0) station = 71420;
  // map type string -> parameter id, e.g. "Humidity" -> 6
  int type_id = 6;
  if (strcmp(type, "Temperature") == 0) type_id = 2;
  String url = String("https://opendata-download-metobs.smhi.se/api/version/1.0/parameter/") +
               String(type_id) + "/station/" + String(station) + "/period/latest-months/data.json";
  return http_get(url);
}

std::vector<float> SMHIClient::fetchHistoricalTemperatures(const char* city, const char* type) {
    std::vector<float> result;

    String payload = fetchHistorical(city, type);
    if (payload.length() == 0) return result;

    DynamicJsonDocument doc(48 * 1024);

    auto err = deserializeJson(doc, payload);
    if (err) return result;

    // Doc["value"] must be an array
    JsonVariant v = doc["value"];
    if (!v.is<JsonArray>()) return result;

    JsonArray arr = v.as<JsonArray>();

    for (JsonObject item : arr) {
        JsonVariant val = item["value"];
        result.push_back(val.as<float>());
    }

    return result;
}
