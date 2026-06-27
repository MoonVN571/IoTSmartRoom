#include <Arduino.h>
#include <DHT.h>
#include "config.h"
#include "sensor.h"

static DHT dht(DHT_PIN, DHT_TYPE);

static float temperature = 0;
static float humidity = 0;
static int lightRaw = 0;
static int lightPercent = 0;

void initSensors() {
  dht.begin();
  pinMode(LIGHT_PIN, INPUT);
}

void updateSensors() {
  float t = dht.readTemperature();
  float h = dht.readHumidity();

  if (!isnan(t)) temperature = t;
  if (!isnan(h)) humidity = h;

  lightRaw = analogRead(LIGHT_PIN);
  lightPercent = map(lightRaw, 0, 4095, 100, 0);
  lightPercent = constrain(lightPercent, 0, 100);

  Serial.print("Temp: ");
  Serial.print(temperature);
  Serial.print(" | Hum: ");
  Serial.print(humidity);
  Serial.print(" | Light raw: ");
  Serial.print(lightRaw);
  Serial.print(" | Light %: ");
  Serial.println(lightPercent);
}

float getTemperature() {
  return temperature;
}

float getHumidity() {
  return humidity;
}

int getLightRaw() {
  return lightRaw;
}

int getLightPercent() {
  return lightPercent;
}