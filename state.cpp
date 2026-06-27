#include "state.h"
#include "display.h"

bool screenOn = true;
bool alarmEnabled = true;

void setScreenState(bool state) {
  screenOn = state;
  setDisplayPower(screenOn);
}

void setAlarmState(bool state) {
  alarmEnabled = state;
}