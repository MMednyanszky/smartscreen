# 🌤️ ESP32 Multi-Language Weather Station & Clock

A lightweight, modular, and easy-to-use Weather Station and Clock framework for ESP32, optimized for the SSD1306 OLED display (128x64).

## ✨ Features
- **Real-time Clock:** NTP synchronization ensures the time is always accurate.
- **Weather Forecast:** Displays current temperature and tomorrow's min/max forecast via OpenWeather API.
- **Dynamic Icons:** Large 16x16 weather icons displayed alongside the clock.
- **Multi-language Support:** Easily switch between Hungarian and English (modular header files).
- **WiFi Signal Indicator:** Real-time RSSI (Signal strength) bars.
- **Smart Formatting:** Automatic accent removal for OLED compatibility and custom date formats per language.

## 🛠️ Hardware Requirements
- **ESP32** (NodeMCU, DevKit, or any standard ESP32 variant)
- **SSD1306 0.96" OLED Display** (I2C version)
- Jumper wires

### Wiring (Standard ESP32):
| OLED Pin | ESP32 Pin |
| :--- | :--- |
| **VCC** | 3.3V |
| **GND** | GND |
| **SCL** | GPIO 22 |
| **SDA** | GPIO 21 |

## 🚀 Installation
1. Clone this repository: `git clone https://github.com/MMednyanszky/smartscreen.git`
2. Open `ESP32_Weather_OS.ino` in Arduino IDE.
3. Install the required libraries via Library Manager:
   - `U8g2`
   - `ArduinoJson`
4. Get a free API Key from [OpenWeatherMap](https://openweathermap.org/).
5. Open `config.h` and fill in:
   - Your WiFi credentials.
   - Your City.
   - Your API Key.
   - Select your language by uncommenting the desired `#include`.

## 📁 Project Structure
- **`ESP32_Weather_OS.ino`**: The core logic and display engine.
- **`config.h`**: User configuration and language selector.
- **`lang_hu.h` / `lang_en.h`**: Language dictionaries and date format definitions.

## 📄 License
This project is licensed under the MIT License - feel free to use and modify it!
