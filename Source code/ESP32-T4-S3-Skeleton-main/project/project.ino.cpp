# 1 "C:\\Users\\georg\\AppData\\Local\\Temp\\tmp3yh77i6a"
#include <Arduino.h>
# 1 "C:/Programmering/Programvarautveckling/Project/Weather-Data-Visualization/Source code/ESP32-T4-S3-Skeleton-main/project/project.ino"
#include <Arduino.h>
#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>
#include <TFT_eSPI.h>
#include <time.h>
#include <LilyGo_AMOLED.h>
#include <LV_Helper.h>
#include <lvgl.h>

#include "main.hpp"


static const char* WIFI_SSID = "SSID";
static const char* WIFI_PASSWORD = "PWD";

LilyGo_Class amoled;
static void connect_wifi();
void setup();
void loop();
#line 20 "C:/Programmering/Programvarautveckling/Project/Weather-Data-Visualization/Source code/ESP32-T4-S3-Skeleton-main/project/project.ino"
static void connect_wifi()
{
  Serial.printf("Connecting to WiFi SSID: %s\n", WIFI_SSID);
  WiFi.mode(WIFI_STA);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

  const uint32_t start = millis();
  while (WiFi.status() != WL_CONNECTED && (millis() - start) < 15000) {
    delay(250);
  }
  Serial.println();

  if (WiFi.status() == WL_CONNECTED) {
    Serial.print("WiFi connected.");
  } else {
    Serial.println("WiFi could not connect (timeout).");
  }
}


void setup()
{
  Serial.begin(115200);
  delay(200);

  if (!amoled.begin()) {
    Serial.println("Failed to init LilyGO AMOLED.");
    while (true) delay(1000);
  }

  beginLvglHelper(amoled);

  connect_wifi();

  startup();
}


void loop()
{
  lv_timer_handler();
  delay(5);

  update();
}