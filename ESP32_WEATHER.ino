#include <Arduino.h>
#include <U8g2lib.h>
#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>
#include "time.h"
#include "config.h" // Ez hívja be a nyelvet is!

U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, U8X8_PIN_NONE);

float currentTemp = 0, tMin = 0, tMax = 0;
String wDesc = "...", tDesc = "...";
unsigned long lastW = 0, lastS = 0;
bool isTomorrow = false;

String fix(String s) {
  String f = "áéíóöőúüűÁÉÍÓÖŐÚÜŰ", t = "aeiooouuuAEIOOOUUU";
  for (int i = 0; i < f.length(); i++) s.replace(f.substring(i, i+1), t.substring(i, i+1));
  return s;
}

char getI(String d) {
  d.toUpperCase();
  if (d.indexOf(KW_THUNDER) >= 0) return 69;
  if (d.indexOf(KW_RAIN) >= 0 || d.indexOf(KW_ZAPOR) >= 0) return 67;
  if (d.indexOf(KW_SNOW) >= 0)   return 70;
  if (d.indexOf(KW_CLOUDY) >= 0) return 66;
  if (d.indexOf(KW_PARTLY) >= 0) return 65;
  if (d.indexOf(KW_FOG) >= 0)    return 68;
  return 64;
}

void fetch() {
  if (WiFi.status() != WL_CONNECTED) return;
  HTTPClient h;
  // Ma
  h.begin("http://api.openweathermap.org/data/2.5/weather?q="+city+"&appid="+apiKey+"&units=metric&lang=hu");
  if (h.GET() == 200) {
    StaticJsonDocument<1024> doc; deserializeJson(doc, h.getString());
    currentTemp = doc["main"]["temp"];
    wDesc = fix(doc["weather"][0]["description"]);
  }
  h.end();
  // Holnap
  h.begin("http://api.openweathermap.org/data/2.5/forecast?q="+city+"&appid="+apiKey+"&units=metric&lang=hu");
  if (h.GET() == 200) {
    StaticJsonDocument<4096> doc; deserializeJson(doc, h.getString());
    tMin = doc["list"][8]["main"]["temp_min"];
    tMax = doc["list"][8]["main"]["temp_max"];
    tDesc = fix(doc["list"][8]["weather"][0]["description"]);
  }
  h.end();
}

void setup() {
  u8g2.begin();
  WiFi.begin(ssid, password);
  u8g2.setFont(u8g2_font_6x10_tf);
  u8g2.drawStr(10, 35, L_WIFI_CONNECT); u8g2.sendBuffer();
  while (WiFi.status() != WL_CONNECTED) delay(500);
  configTzTime("CET-1CEST,M3.5.0,M10.5.0/3", "pool.ntp.org");
  fetch();
}

void loop() {
  if (millis() - lastW >= 600000 || lastW == 0) { fetch(); lastW = millis(); }
  if (millis() - lastS >= 10000) { isTomorrow = !isTomorrow; lastS = millis(); }

  struct tm ti; if(!getLocalTime(&ti)) return;
  String curD = isTomorrow ? tDesc : wDesc; curD.toUpperCase();

  u8g2.clearBuffer();
  u8g2.setFont(u8g2_font_6x10_tf);
  u8g2.setCursor(0, 10);
  
  if (isTomorrow) u8g2.print(String(tMin,0)+"/"+String(tMax,0)+"C "+curD.substring(0,14));
  else u8g2.print(String(currentTemp,0)+"C "+curD.substring(0,18));

  // Térerő
  int b = constrain(map(WiFi.RSSI(), -100, -40, 0, 5), 0, 5);
  for(int i=0; i<b; i++) u8g2.drawBox(115+(i*3), 10-(i*2), 2, i*2+2);
  u8g2.drawHLine(0, 13, 128);

  // Óra
  char h[3], m[3], s[3]; strftime(h,3,"%H",&ti); strftime(m,3,"%M",&ti); strftime(s,3,"%S",&ti);
  u8g2.setFont(u8g2_font_logisoso24_tn);
  u8g2.drawStr(5, 45, h); u8g2.drawStr(41, 43, ":"); u8g2.drawStr(51, 45, m);
  u8g2.setFont(u8g2_font_6x10_tf); u8g2.drawStr(85, 45, s);

  // Ikon
  u8g2.setFont(u8g2_font_open_iconic_weather_2x_t);
  u8g2.drawGlyph(105, 45, getI(curD));

  // Dátum
  char dS[20]; strftime(dS, 20, L_DATE_FMT, &ti);
  String f = String(dS) + " " + fix(days[ti.tm_wday]); f.toUpperCase();
  u8g2.setFont(u8g2_font_6x10_tf);
  u8g2.setCursor(64-(u8g2.getStrWidth(f.c_str())/2), 62); u8g2.print(f);

  u8g2.sendBuffer();
  delay(500);
}