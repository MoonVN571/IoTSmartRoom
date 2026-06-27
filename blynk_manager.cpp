#include "config.h"

#include <Arduino.h>
#include <WiFi.h>
#include <BlynkSimpleEsp32.h>

#include "sensor.h"
#include "state.h"
#include "buzzer.h"

void initBlynk() {
  if (WiFi.status() != WL_CONNECTED) {
    Serial.println("Blynk Skipped: No WiFi");
    return;
  }

  Serial.println("Connecting Blynk...");

  Blynk.config(BLYNK_AUTH_TOKEN);

  bool ok = Blynk.connect(5000);

  if (ok) {
    Serial.println("Blynk Connected");

    Blynk.virtualWrite(V3, alarmEnabled);
    Blynk.virtualWrite(V4, screenOn);
  } else {
    Serial.println("Blynk Failed");
  }
}

void updateBlynk() {
  if (WiFi.status() != WL_CONNECTED) return;

  Blynk.run();

  static unsigned long lastSend = 0;

  if (millis() - lastSend > 2000) {
    Blynk.virtualWrite(V0, getTemperature());
    Blynk.virtualWrite(V1, getHumidity());
    Blynk.virtualWrite(V2, getLightPercent());

    lastSend = millis();
  }
}

BLYNK_WRITE(V3) {
  setAlarmState(param.asInt());
  beep(70);
}

BLYNK_WRITE(V4) {
  setScreenState(param.asInt());
  beep(70);
}

void syncBlynkScreen() {
  if (WiFi.status() == WL_CONNECTED && Blynk.connected()) {
    Blynk.virtualWrite(V4, screenOn);
    Serial.println("Sync V4 screen to Blynk");
  } else {
    Serial.println("Skip sync V4: Blynk not connected");
  }
}

void syncBlynkAlarm() {
  if (WiFi.status() == WL_CONNECTED && Blynk.connected()) {
    Blynk.virtualWrite(V3, alarmEnabled);
    Serial.println("Sync V3 alarm to Blynk");
  } else {
    Serial.println("Skip sync V3: Blynk not connected");
  }
}