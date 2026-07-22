#pragma once
#include <secrets.h>

#define VERSION "1.1"

#define OLED_SDA 21
#define OLED_SCL 22
#define OLED_ADDR 0x3C

#define DHT_PIN 4
#define DHT_TYPE DHT11

#define BUTTON_PIN 15

#define BUZZER_PIN 26
#define ALARM_PIN 25
#define ALARM_BUTTON_PIN 13
#define ALARM_LED_PIN 14

#define LIGHT_PIN 34
#define LIGHT_DO_PIN 27
#define LIGHT_LOW_PERCENT 20

#define BUTTON_PIN 15
#define AUTO_LIGHT_LED_PIN 26

#define GMT_OFFSET_SEC 7 * 3600
#define DAYLIGHT_OFFSET_SEC 0

#define IR_SENSOR_PIN 32
#define IR_ACTIVE_LOW true

#define SCREEN_AUTO_OFF_MS 30000UL

#define FAN_RELAY_PIN 18

#define TEMPERATURE_FAN_ON 35.0
#define HUMIDITY_LIGHT_ON 70.0

// Relay thường kích khi LOW
#define RELAY_ACTIVE_LOW true

struct WifiInfo {
  const char* ssid;
  const char* password;
};

static WifiInfo WIFI_LIST[] = {
    {WIFI_SSID_1, WIFI_PASS_1},
    {WIFI_SSID_2, WIFI_PASS_2}
};

static const int WIFI_COUNT = sizeof(WIFI_LIST) / sizeof(WIFI_LIST[0]);