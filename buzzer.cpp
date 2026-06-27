#include <Arduino.h>
#include "config.h"
#include "buzzer.h"

void initBuzzer() {
  pinMode(BUZZER_PIN, OUTPUT);
  pinMode(ALARM_PIN, OUTPUT);

  digitalWrite(BUZZER_PIN, LOW);
  digitalWrite(ALARM_PIN, LOW);
}

void beep(int ms) {
  digitalWrite(BUZZER_PIN, HIGH);
  delay(ms);
  digitalWrite(BUZZER_PIN, LOW);
}

void beepSuccess() {
  beep(70);
  delay(80);
  beep(70);
}

void beepError() {
  beep(300);
}

void alarmOn() {
  digitalWrite(ALARM_PIN, HIGH);
}

void alarmOff() {
  digitalWrite(ALARM_PIN, LOW);
}