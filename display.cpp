#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#include "config.h"
#include "display.h"

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

static Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

void initDisplay() {
  Wire.begin(OLED_SDA, OLED_SCL);

  if (!display.begin(SSD1306_SWITCHCAPVCC, OLED_ADDR)) {
    while (true);
  }

  display.clearDisplay();
  display.display();
}

void bootScreen() {
  display.clearDisplay();
  display.setTextColor(SSD1306_WHITE);
  display.setTextSize(1);

  display.setCursor(28, 20);
  display.println(BLYNK_TEMPLATE_NAME);

  display.setCursor(38, 36);
  display.println(VERSION);

  display.display();
  delay(800);
}

void setDisplayPower(bool on) {
  if (on) {
    display.ssd1306_command(SSD1306_DISPLAYON);
  } else {
    display.ssd1306_command(SSD1306_DISPLAYOFF);
  }
}

static void drawLightBar(int x, int y, int width, int height, int percent) {
  percent = constrain(percent, 0, 100);

  display.drawRect(x, y, width, height, SSD1306_WHITE);

  int fillWidth = map(percent, 0, 100, 0, width - 2);
  display.fillRect(x + 1, y + 1, fillWidth, height - 2, SSD1306_WHITE);
}

void drawDashboard(
  float temperature,
  float humidity,
  int lightPercent,
  String timeText,
  bool wifiConnected
) {
  display.clearDisplay();
  display.setTextColor(SSD1306_WHITE);

  display.drawRoundRect(0, 0, 128, 64, 6, SSD1306_WHITE);

  display.setTextSize(1);
  display.setCursor(8, 6);
  display.print(timeText);

  display.setCursor(86, 6);
  display.print("WiFi ");
  display.print(wifiConnected ? "O" : "X");

  display.setTextSize(2);

  display.setCursor(10, 20);
  display.print(temperature, 1);
  display.print("C");

  display.setCursor(10, 40);
  display.print(humidity, 0);
  display.print("%");

  display.setTextSize(1);
  display.setCursor(70, 42);
  display.print("Light");

  drawLightBar(70, 52, 42, 8, lightPercent);

  display.setCursor(114, 52);
  display.print(lightPercent);

  display.display();
}