#include "config.h"
#include "buzzer.h"
#include "display.h"
#include "sensor.h"
#include "ir_sensor.h"
#include "button.h"
#include "wifi_manager.h"
#include "time_manager.h"
#include "blynk_manager.h"
#include "state.h"
bool fanOn = false;

void setFan(bool state) {
  fanOn = state;

  if (RELAY_ACTIVE_LOW) {
    digitalWrite(FAN_RELAY_PIN, state ? LOW : HIGH);
  } else {
    digitalWrite(FAN_RELAY_PIN, state ? HIGH : LOW);
  }
}

void setup() {
  Serial.begin(115200);

  initBuzzer();
  initDisplay();
  bootScreen();

  initSensors();
  initIrSensor();
  initButton();
  pinMode(ALARM_LED_PIN, OUTPUT);
  pinMode(AUTO_LIGHT_LED_PIN, OUTPUT);

  pinMode(FAN_RELAY_PIN, OUTPUT);

  // Tắt relay/quạt khi ESP32 vừa khởi động
  setFan(false);

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
  float humidity = getHumidity();

  bool isLowLight = lightPercent < LIGHT_LOW_PERCENT;

  // LED đỏ: báo chế độ cảnh báo đang bật
  digitalWrite(ALARM_LED_PIN, alarmEnabled ? HIGH : LOW);

  // LED trắng: chỉ sáng khi tắt cảnh báo và trời tối
  bool autoLightOn = !alarmEnabled && isLowLight;
  digitalWrite(AUTO_LIGHT_LED_PIN, autoLightOn ? HIGH : LOW);

  // Còi: chỉ kêu khi cảnh báo bật và trời tối
  if (alarmEnabled && isLowLight) {
    alarmOn();
  } else {
    alarmOff();
  }

  // Quạt: bật khi độ ẩm > 60%
  if (humidity > HUMIDITY_FAN_ON) {
    setFan(true);
  }
  // Chỉ tắt khi độ ẩm xuống dưới 58%
  else if (humidity < HUMIDITY_FAN_OFF) {
    setFan(false);
  }

  // OLED
  if (screenOn) {
    drawDashboard(
      getTemperature(),
      humidity,
      lightPercent,
      getTimeString(),
      isWifiConnected()
    );
  }

  delay(200);
}