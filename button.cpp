#include <Arduino.h>
#include "config.h"
#include "button.h"
#include "buzzer.h"
#include "state.h"
#include "blynk_manager.h"

static bool lastScreenButton = HIGH;
static bool lastAlarmButton = HIGH;

static unsigned long lastScreenPress = 0;
static unsigned long lastAlarmPress = 0;

void initButton() {
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  pinMode(ALARM_BUTTON_PIN, INPUT_PULLUP);
}

void handleButton() {
  bool screenButton = digitalRead(BUTTON_PIN);
  bool alarmButton = digitalRead(ALARM_BUTTON_PIN);

  if (lastScreenButton == HIGH && screenButton == LOW) {
    if (millis() - lastScreenPress > 250) {
      setScreenState(!screenOn);
      beep(70);
      syncBlynkScreen();

      Serial.print("Screen button: ");
      Serial.println(screenOn ? "ON" : "OFF");

      lastScreenPress = millis();
    }
  }

  if (lastAlarmButton == HIGH && alarmButton == LOW) {
    if (millis() - lastAlarmPress > 250) {
      setAlarmState(!alarmEnabled);
      beep(70);
      syncBlynkAlarm();

      Serial.print("Alarm button: ");
      Serial.println(alarmEnabled ? "ON" : "OFF");

      lastAlarmPress = millis();
    }
  }

  lastScreenButton = screenButton;
  lastAlarmButton = alarmButton;
}

bool isScreenOn() {
  return screenOn;
}