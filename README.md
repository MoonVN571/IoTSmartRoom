# IoT Smart Room

An ESP32-based smart room monitor that reads temperature, humidity, and ambient light, displays data on an OLED screen, and sends telemetry to the Blynk mobile app over WiFi. Includes a low-light alarm with buzzer and LED feedback.

**Version:** 1.1

## Features

- **Environmental sensing** — DHT11 for temperature and humidity; analog light sensor for ambient brightness (0–100%)
- **OLED dashboard** — Real-time display of time, WiFi status, temperature, humidity, and a light level bar
- **Blynk IoT** — Remote monitoring and control via the Blynk app
- **Low-light alarm** — Buzzer and LED activate when light drops below 20% (configurable)
- **Local controls** — Physical buttons to toggle the OLED screen and alarm on/off
- **Multi-WiFi** — Auto-connects to the first available network from a configured list
- **NTP time sync** — Clock display synced via NTP (GMT+7)

## Hardware Requirements

| Component | Notes |
|-----------|-------|
| ESP32 Dev Board | Main microcontroller |
| SSD1306 OLED (128×64, I2C) | Address `0x3C` |
| DHT11 | Temperature & humidity sensor |
| Light sensor (analog) | e.g. photoresistor module |
| Active buzzer | Feedback & alarm |
| Push buttons (×2) | Screen toggle & alarm toggle |
| LED | Alarm status indicator |

## Pin Configuration

| Function | GPIO |
|----------|------|
| OLED SDA | 21 |
| OLED SCL | 22 |
| DHT11 data | 4 |
| Screen button | 15 |
| Alarm button | 13 |
| Buzzer | 26 |
| Alarm buzzer | 25 |
| Alarm LED | 14 |
| Light sensor (analog) | 34 |
| Light sensor (digital) | 27 |

> Pin definitions are in `config.h`. Adjust them if your wiring differs.

## Software Requirements

Install these libraries via the Arduino Library Manager:

- [Adafruit SSD1306](https://github.com/adafruit/Adafruit_SSD1306)
- [Adafruit GFX Library](https://github.com/adafruit/Adafruit-GFX-Library)
- [DHT sensor library](https://github.com/adafruit/DHT-sensor-library) (Adafruit)
- [Blynk](https://github.com/blynkkk/blynk-library)

**Board:** ESP32 (select the correct board variant in the Arduino IDE)

## Setup

### 1. Clone or download the project

Open the `IoT_Smart_Room` folder in the Arduino IDE.

### 2. Configure credentials

Copy the example secrets file and fill in your values:

```bash
cp secrets.example.h secrets.h
```

Edit `secrets.h`:

```cpp
#define WIFI_SSID_1 "YourWiFiName"
#define WIFI_PASS_1 "YourWiFiPassword"

#define WIFI_SSID_2 "BackupWiFiName"   // optional second network
#define WIFI_PASS_2 "BackupPassword"

#define BLYNK_TEMPLATE_ID "TMPLxxxx"
#define BLYNK_TEMPLATE_NAME "Smart Room"
#define BLYNK_AUTH_TOKEN "YourBlynkAuthToken"
```

> **Important:** Do not commit `secrets.h` — keep your WiFi and Blynk credentials private.

### 3. Blynk app setup

Create a new device in the [Blynk IoT](https://blynk.io/) console using your template ID. Map virtual pins as follows:

| Virtual Pin | Direction | Purpose |
|-------------|-----------|---------|
| V0 | Device → App | Temperature (°C) |
| V1 | Device → App | Humidity (%) |
| V2 | Device → App | Light level (%) |
| V3 | App → Device | Alarm enable (0/1) |
| V4 | App → Device | Screen enable (0/1) |

Sensor data is pushed every 2 seconds when WiFi is connected.

### 4. Upload firmware

1. Connect the ESP32 via USB
2. Select the correct COM port and ESP32 board
3. Click **Upload**
4. Open Serial Monitor at **115200 baud** to view debug output

## Usage

### Boot sequence

1. OLED shows the project name and version
2. ESP32 scans for configured WiFi networks and connects automatically
3. On success: NTP time sync, Blynk connection, double beep
4. On failure: single long error beep; local features still work without cloud

### Local buttons

| Button | GPIO | Action |
|--------|------|--------|
| Screen | 15 | Toggle OLED display on/off |
| Alarm | 13 | Enable/disable low-light alarm |

State changes sync to Blynk when connected.

### Alarm behavior

When the alarm is **enabled** and light level drops below **20%** (`LIGHT_LOW_PERCENT` in `config.h`):

- Alarm buzzer (GPIO 25) turns on
- Alarm LED (GPIO 14) turns on

The alarm turns off automatically when light rises above the threshold or the alarm is disabled.

## Project Structure

```
IoT_Smart_Room/
├── IoT_Smart_Room.ino   # Main entry point
├── config.h             # Pin map, WiFi list, constants
├── secrets.h            # Credentials (not in repo)
├── secrets.example.h    # Credentials template
├── sensor.cpp/h         # DHT11 & light sensor
├── display.cpp/h        # SSD1306 OLED UI
├── button.cpp/h         # Physical button handling
├── buzzer.cpp/h         # Buzzer & alarm output
├── wifi_manager.cpp/h   # Multi-WiFi auto-connect
├── time_manager.cpp/h   # NTP time sync
├── blynk_manager.cpp/h  # Blynk IoT integration
└── state.cpp/h          # Screen & alarm state
```

## Configuration

Key constants in `config.h`:

| Constant | Default | Description |
|----------|---------|-------------|
| `LIGHT_LOW_PERCENT` | 20 | Alarm triggers below this light % |
| `GMT_OFFSET_SEC` | 25200 (UTC+7) | Timezone offset |
| `VERSION` | 1.1 | Firmware version |

## Troubleshooting

| Issue | Possible fix |
|-------|--------------|
| OLED stays blank | Check I2C wiring (SDA/SCL) and address `0x3C` |
| DHT11 reads NaN | Verify data pin (GPIO 4) and 3.3 V power |
| WiFi won't connect | Confirm SSID/password in `secrets.h`; check Serial Monitor scan results |
| Blynk not updating | Verify auth token; ensure device is online in Blynk console |
| Time shows `--:--:--` | WiFi must be connected for NTP sync |

## License

This project is provided as-is for educational and personal use.
