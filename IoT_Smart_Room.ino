#include "config.h"
#include "buzzer.h"
#include "display.h"
#include "sensor.h"
#include "button.h"
#include "wifi_manager.h"
#include "time_manager.h"
#include "blynk_manager.h"
#include "state.h"

void setup() {
  Serial.begin(115200);

  initBuzzer();
  initDisplay();
  bootScreen();

  initSensors();
  initButton();
  pinMode(ALARM_LED_PIN, OUTPUT);

  bool wifiOk = connectWifiAuto();

  if (wifiOk) {
    syncTime();
    initBlynk();
    beepSuccess();
  } else {
    beepError();
  }
}

void loop() {
  handleButton();

  updateSensors();
  updateBlynk();

  int lightPercent = getLightPercent();

  digitalWrite(ALARM_LED_PIN, alarmEnabled ? HIGH : LOW);

  if (alarmEnabled && lightPercent < LIGHT_LOW_PERCENT) {
    alarmOn();
  } else {
    alarmOff();
  }

  if (screenOn) {
    drawDashboard(
      getTemperature(),
      getHumidity(),
      lightPercent,
      getTimeString(),
      isWifiConnected()
    );
  }

  delay(200);
}