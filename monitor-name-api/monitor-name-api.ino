#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <ArduinoJson.h>


// wifi
const char *ssid = "abcd";
const char *pass = "qwertyui";
const String url = "http://sulthon.dion-zebua.my.id/api/data";

// lcd init
LiquidCrystal_I2C lcd(0x27, 16, 2);

//wifi client and http clinet object
WiFiClient wifi;
HTTPClient http;

// name
String name = "slebew";

void setup() {
  // serail
  Serial.begin(9600);

  // lcd
  lcd.init();
  lcd.begin(16, 2);
  lcd.backlight();
  // wifi
  WiFi.begin(ssid, pass);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(". ");
    lcd.setCursor(0, 0);
    lcd.print("wifi is ");
    lcd.setCursor(0, 1);
    lcd.print("not connected");
  }

  lcd.setCursor(0, 1);
  lcd.print("connected");
  lcd.clear();
}

void loop() {
  if (WiFi.status() == WL_CONNECTED) {
    // http
    http.begin(wifi, url);
    http.addHeader("Content-Type", "application/json");

    int requestStatus = http.GET();

      String response = http.getString();
    if (requestStatus == 200) {
      JsonDocument doc;
      deserializeJson(doc, response);
      const char* newName = doc["name"];

      // 
      lcd.setCursor(0, 0);
      lcd.print("name: ");
      lcd.print(newName);
      lcd.setCursor(0, 1);
      lcd.print("by SHELBEW!!!");

    }else{
      Serial.println(response);
      Serial.println("gagal");
      lcd.setCursor(0, 0);
      lcd.print("ASSALAMUALAIKUM");
      lcd.setCursor(0, 1);
      lcd.print("by SHELBEW!!!");
    }
    //
  }
  delay(5000);
  lcd.clear();
}
