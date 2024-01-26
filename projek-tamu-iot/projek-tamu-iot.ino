#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <ArduinoJson.h>

// global variabel
// wifi
const char *ssid = "abcd";
const char *pass = "qwertyui";
const String url = "http://sulthon.dion-zebua.my.id/";
WiFiClient wifi;

//
HTTPClient http;

//
LiquidCrystal_I2C lcd(0x27, 16, 2);
// ultrasonic
const int echoPin = D3;
const int trigPin = D4;
// buzzer
const int buzzerPin = D5;

// servo

// sensor ultrasonic hc sr04
long distance() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Reading the echo time
  long duration = pulseIn(echoPin, HIGH);

  // Calculating distance in centimeters
  long distance = duration / 58;

  return distance;
}

// buzzer call
void buzzerCall() {
  pinMode(buzzerPin, HIGH);
  delay(200);
  pinMode(buzzerPin, LOW);
  delay(200);
}

//say hello
void sayHello() {
  lcd.setCursor(0, 0);
  lcd.print("(...WELCOME...)");
  lcd.setCursor(0, 1);
  lcd.print("sulthon dirumah");
}

// hello
void createdBy() {
  lcd.setCursor(0, 0);
  lcd.print("sulthon");
  lcd.setCursor(0, 1);
  lcd.print("shelbew");
}

// setup
void setup() {
  // serial
  Serial.begin(9600);

  //lcd
  lcd.init();
  lcd.begin(16, 2);
  lcd.backlight();
  lcd.clear();

  //
  WiFi.begin(ssid, pass);
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(". ");
    lcd.setCursor(0, 0);
    lcd.print("wifi is ");
    lcd.setCursor(0, 1);
    lcd.print("not connected");
    lcd.clear();
    delay(500);
  }

  // ultrasonic
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

 
}

// loop
void loop() {
  if (WiFi.status() == WL_CONNECTED) {
    //
    http.begin(wifi, url);
    http.addHeader("Content-Type", "application/json");
    //
    lcd.clear();
    long distance_cm = distance();

    // Displaying the distance
    Serial.print("Distance: ");
    Serial.print(distance_cm);
    Serial.println(" cm");

    if (distance_cm < 50) {
      buzzerCall();
      sayHello();
      String payload = "{\"tamu\":\"true\"}";
      int statusCode = http.POST(payload);
      if (statusCode > 0) {
        Serial.println("http post success");
        String response = http.getString();
        Serial.println(response);
      } else {
        Serial.print("HTTP POST request failed, error code: ");
        Serial.println(statusCode);
      }
    } else {
      String payload = "{\"tamu\":\"false\"}";
      int statusCode = http.POST(payload);
      if (statusCode > 0) {
        Serial.println("http post success");
        String response = http.getString();
        Serial.println(response);
      } else {
        Serial.print("HTTP POST request failed, error code: ");
        Serial.println(statusCode);
      }
      createdBy();
    }
  }

  delay(1000);
}
