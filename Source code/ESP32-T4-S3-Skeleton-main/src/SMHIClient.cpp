#include "SMHIClient.hpp"
#include <HTTPClient.h>

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

String SMHIClient::fetchForecast(const char* city) {
  // map city to lat/lon (copy of mapping in API example)
  float lat = 56.1612, lon = 15.5869; // default Karlskrona; extend mapping if needed
  if (strcmp(city, "Goteborg") == 0) { lat = 57.7089; lon = 11.9746; }
  // ... add others as in API_call_functions_example/main.cpp
  String url = String("https://opendata-download-metfcst.smhi.se/api/category/snow1g/version/1/geotype/point/lon/") +
               String(lon, 6) + "/lat/" + String(lat, 6) + "/data.json";
  return http_get(url);
}

String SMHIClient::fetchHistorical(const char* city, const char* type) {
  // map city -> station id and type -> id (copy mappings from API example)
  int station = 65090; // default Karlskrona
  if (strcmp(city, "Goteborg") == 0) station = 71420;
  // map type string -> parameter id, e.g. "Humidity" -> 6
  int type_id = 6;
  if (strcmp(type, "Temperature") == 0) type_id = 1;
  String url = String("https://opendata-download-metobs.smhi.se/api/version/1.0/parameter/") +
               String(type_id) + "/station/" + String(station) + "/period/latest-months/data.json";
  return http_get(url);
}