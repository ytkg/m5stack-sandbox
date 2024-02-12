#include <M5Unified.h>
#include <WiFi.h>
#include <HTTPClient.h>

const char* ssid = "ssid";
const char* password = "password";

void connectWiFi() {
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    M5.Lcd.print('.');
  }
  M5.Lcd.println("\nWiFi connected.\n");
}

String getGlobalIP() {
  HTTPClient http;
  String payload;

  http.begin("https://ifconfig.me/ip");
  if (http.GET() == HTTP_CODE_OK) {
    payload = http.getString();
  } else {
    payload = "Error";
  }
  http.end();

  return payload;
}

void setup() {
  M5.begin();

  M5.Lcd.setTextSize(1.5);
  M5.Lcd.setRotation(3);

  connectWiFi();

  M5.Lcd.print("Local IP: ");
  M5.Lcd.println(WiFi.localIP());

  M5.Lcd.print("Global IP: ");
  M5.Lcd.print(getGlobalIP());
}

void loop() {
}
