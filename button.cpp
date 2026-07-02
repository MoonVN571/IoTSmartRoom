#include <Arduino.h>

#include "config.h"
#include "button.h"
#include "state.h"
#include "blynk_manager.h"

static bool lastScreenButton = HIGH;
static bool lastAlarmButton = HIGH;

static unsigned long lastScreenPress = 0;
static unsigned long lastAlarmPress = 0;

const unsigned long DEBOUNCE_MS = 250;

void initButton() {
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  pinMode(ALARM_BUTTON_PIN, INPUT_PULLUP);
}

void handleButton() {
  bool screenButton = digitalRead(BUTTON_PIN);
  bool alarmButton = digitalRead(ALARM_BUTTON_PIN);

  // Nút bật/tắt màn hình - D15
  if (lastScreenButton == HIGH &&
      screenButton == LOW &&
      millis() - lastScreenPress > DEBOUNCE_MS) {

    setScreenState(!screenOn);
    syncBlynkScreen();

    lastScreenPress = millis();
  }

  // Nút bật/tắt cảnh báo - D13
  if (lastAlarmButton == HIGH &&
      alarmButton == LOW &&
      millis() - lastAlarmPress > DEBOUNCE_MS) {

    setAlarmState(!alarmEnabled);
    syncBlynkAlarm();

    Serial.print("Alarm: ");
    Serial.println(alarmEnabled ? "ON" : "OFF");

    lastAlarmPress = millis();
  }

  lastScreenButton = screenButton;
  lastAlarmButton = alarmButton;
}