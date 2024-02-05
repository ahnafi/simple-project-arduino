#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

const int lebar = 128;
const int tinggi = 64;
const int reset = 4;

#define rainAnalog 12
#define rainDigital 13

#define buzzer 2

Adafruit_SSD1306 oled(lebar, tinggi, &Wire, reset);

void setup()
{
  Serial.begin(9600);
  pinMode(rainDigital, INPUT);
  pinMode(buzzer, OUTPUT);
  oled.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  oled.clearDisplay();
  oled.setTextSize(2);
  oled.setTextColor(WHITE);
}
void loop()
{
  oled.clearDisplay();
  int rainAnalogVal = analogRead(rainAnalog);
  int rainDigitalVal = digitalRead(rainDigital);
  digitalWrite(buzzer, HIGH);
  if (rainDigitalVal == 0)
  {
    digitalWrite(buzzer, HIGH);
    delay(250);
    digitalWrite(buzzer, LOW);
    delay(250);
  }

  String hujan ;
  // 0-4000
  if (!rainDigitalVal && rainAnalogVal < 500)
  {
    hujan = "cuaca : hujan besar";
  }
  else if (!rainDigitalVal && (rainAnalogVal > 500 || rainAnalogVal < 1500))
  {
    hujan = "cuaca : hujan gerimis kecil";
  }
  else
  {
    hujan = "cuaca terang";
  }

  oled.setCursor(0, 0);
  oled.print(hujan);
  // oled.setCursor(0, 20);
  // oled.print("kekuatan ");
  // oled.println(rainAnalogVal);
  oled.display();
  delay(250);
}
