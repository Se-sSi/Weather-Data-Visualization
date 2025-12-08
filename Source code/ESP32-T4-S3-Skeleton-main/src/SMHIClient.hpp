#pragma once
#include <Arduino.h>
#include <ArduinoJson.h>

class SMHIClient {
public:
    static void begin();

    // Hämta prognos
    static String fetchForecast(const char* city);

    // FIX: Byt till JsonDocument& doc
    static bool fetchHistoricalToDoc(const char* city, const char* type, JsonDocument& doc);
};