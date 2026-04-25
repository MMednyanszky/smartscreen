# 🌤️ ESP32 Multi-Language Weather Station & Clock

Ez egy ESP32-alapú okosóra és időjárás-állomás keretrendszer, amely SSD1306 OLED kijelzőre (128x64) lett optimalizálva. A projekt különlegessége a moduláris felépítés és a többnyelvű támogatás.

## ✨ Funkciók
- **Valós idejű óra:** NTP szinkronizációval (mindig pontos idő).
- **Időjárás előrejelzés:** Aktuális hőmérséklet és holnapi min/max adatok az OpenWeather API-ról.
- **Dinamikus ikonok:** 16x16-os időjárás ikonok az óra mellett.
- **Többnyelvűség:** Egyszerűen váltható magyar és angol nyelv (külön header fájlokban).
- **Térerő kijelzés:** Valós idejű WiFi jel erősség (RSSI) indikátor.

## 🛠️ Szükséges hardverek
- **ESP32** (NodeMCU vagy bármilyen standard változat)
- **SSD1306 0.96" OLED kijelző** (I2C kommunikációval)
- 4 db összekötő kábel (Jumper wire)

### Bekötés (Standard ESP32):
| OLED Pin | ESP32 Pin |
| :--- | :--- |
| **VCC** | 3.3V |
| **GND** | GND |
| **SCL** | GPIO 22 |
| **SDA** | GPIO 21 |

## 🚀 Telepítés
1. Töltsd le a tárolót (vagy klónozd: `git clone`).
2. Nyisd meg az `ESP32_Weather_OS.ino` fájlt az Arduino IDE-ben.
3. Telepítsd a szükséges könyvtárakat az IDE Library Manageréből:
   - `U8g2`
   - `ArduinoJson`
4. Regisztrálj egy ingyenes API kulcsért a [OpenWeatherMap](https://openweathermap.org/) oldalon.
5. Nyisd meg a `config.h` fájlt és add meg:
   - A WiFi adataidat.
   - A városodat.
   - Az API kulcsodat.
   - Válaszd ki a kívánt nyelvet az `#include` sor módosításával.

## 📁 Projekt struktúra
- **`ESP32_Weather_OS.ino`**: A projekt motorja és logikája.
- **`config.h`**: Személyes beállítások és nyelvválasztás.
- **`lang_hu.h` / `lang_en.h`**: Nyelvi szótárak és dátumformátumok.

## 📄 Licenc
Ez a projekt MIT licenc alatt áll - bárki szabadon használhatja és módosíthatja!