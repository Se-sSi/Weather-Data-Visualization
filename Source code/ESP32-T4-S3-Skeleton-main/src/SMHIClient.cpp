#include "SMHIClient.hpp"
#include <HTTPClient.h>

void SMHIClient::begin() { }

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
  float lat = 56.1612, lon = 15.5869;
  if (strcmp(city, "Goteborg") == 0) { lat = 57.7089; lon = 11.9746; }
  else if (strcmp(city, "Stockholm") == 0) { lat = 59.3293; lon = 18.0686; }
  else if (strcmp(city, "Malmo") == 0) { lat = 55.6049; lon = 13.0038; }

  String url = String("https://opendata-download-metfcst.smhi.se/api/category/pmp3g/version/2/geotype/point/lon/") +
               String(lon, 4) + "/lat/" + String(lat, 4) + "/data.json";
  return http_get(url);
}

// FIX: Använd JsonDocument&
bool SMHIClient::fetchHistoricalToDoc(const char* city, const char* type, JsonDocument& doc) {
  int station = 65090; // Karlskrona
  if (strcmp(city, "Goteborg") == 0) station = 71420;
  else if (strcmp(city, "Stockholm") == 0) station = 98210;
  else if (strcmp(city, "Malmo") == 0) station = 52350;

  int type_id = 1;
  // Använd Parameter 2 (Dygnsmedel)
  if (strcmp(type, "Temperature") == 0) type_id = 2;
  else if (strcmp(type, "Wind Speed") == 0) type_id = 4;
  else if (strcmp(type, "Humidity") == 0) type_id = 6;

  String url = String("https://opendata-download-metobs.smhi.se/api/version/1.0/parameter/") +
               String(type_id) + "/station/" + String(station) + "/period/latest-months/data.json";

  HTTPClient http;
  http.setTimeout(8000);
  http.begin(url);

  int code = http.GET();
  if (code == HTTP_CODE_OK) {
      // Filter för att spara minne
      JsonDocument filter; // Inget Static/Dynamic behövs i v7
      filter["value"][0]["date"] = true;
      filter["value"][0]["value"] = true;

      DeserializationError err = deserializeJson(doc, http.getStream(), DeserializationOption::Filter(filter));

      http.end();

      if (err) {
          Serial.print("JSON Error: "); Serial.println(err.c_str());
          return false;
      }
      return true;
  } else {
      Serial.printf("HTTP Error: %d\n", code);
  }

  http.end();
  return false;
}