#pragma once
#include <Arduino.h>

void initDisplay();
void bootScreen();
void setDisplayPower(bool on);

void drawDashboard(
  float temperature,
  float humidity,
  int lightPercent,
  String timeText,
  bool wifiConnected
);