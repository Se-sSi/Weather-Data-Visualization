#pragma once
#include <Arduino.h>

class SMHIClient {
public:
  // call once to init (no-op here, but keep for future)
  static void begin();

  // returns raw JSON as String or empty on error
  static String fetchForecast(const char* city);
  static String fetchHistorical(const char* city, const char* type);
};