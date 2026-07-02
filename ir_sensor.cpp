#include <Arduino.h>

#include "config.h"
#include "ir_sensor.h"

static bool irDetected = false;
static unsigned long lastDetectedAt = 0;

void initIrSensor() {
  pinMode(IR_SENSOR_PIN, INPUT);
}

void updateIrSensor() {
  bool pinState = digitalRead(IR_SENSOR_PIN);

  if (IR_ACTIVE_LOW) {
    irDetected = (pinState == LOW);
  } else {
    irDetected = (pinState == HIGH);
  }

  if (irDetected) {
    lastDetectedAt = millis();
  }
}

bool isIrDetectedNow() {
  return irDetected;
}

bool hasRecentPresence() {
  if (lastDetectedAt == 0) {
    return false;
  }

  return millis() - lastDetectedAt < SCREEN_AUTO_OFF_MS;
}