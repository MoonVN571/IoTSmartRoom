#pragma once

void initSensors();
void updateSensors();

float getTemperature();
float getHumidity();
int getLightRaw();
int getLightPercent();