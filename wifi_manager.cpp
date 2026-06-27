#include <Arduino.h>
#include <WiFi.h>

#include "config.h"
#include "wifi_manager.h"
#include "display.h"

bool connectWifiAuto() {
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  delay(300);

  Serial.println("Scanning WiFi...");
  int n = WiFi.scanNetworks();

  if (n <= 0) {
    Serial.println("No WiFi found");
    return false;
  }

  for (int i = 0; i < WIFI_COUNT; i++) {
    for (int j = 0; j < n; j++) {
      if (WiFi.SSID(j) == WIFI_LIST[i].ssid) {
        Serial.print("Connecting to ");
        Serial.println(WIFI_LIST[i].ssid);

        WiFi.begin(WIFI_LIST[i].ssid, WIFI_LIST[i].password);

        unsigned long start = millis();

        while (WiFi.status() != WL_CONNECTED && millis() - start < 12000) {
          delay(300);
          Serial.print(".");
        }

        Serial.println();

        if (WiFi.status() == WL_CONNECTED) {
          Serial.print("Connected IP: ");
          Serial.println(WiFi.localIP());
          return true;
        }
      }
    }
  }

  Serial.println("WiFi connect failed");
  return false;
}

bool isWifiConnected() {
  return WiFi.status() == WL_CONNECTED;
}