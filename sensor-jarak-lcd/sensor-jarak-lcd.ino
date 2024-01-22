#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

#define lampu 4
#define trigPin 2
#define echoPin 3

long duration;
int distance;

void setup() {
  // put your setup code here, to run once:
  lcd.init();
  lcd.backlight();
  lcd.begin(16, 2);
  lcd.print("hello");

  Serial.begin(9600);
  pinMode(lampu, OUTPUT);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);

  distance = duration * 0.034 / 2;


    // lcd.clear();

  if (distance < 10) {
    pinMode(lampu, LOW);
    // delay(200);

    lcd.setCursor(5,0);
    lcd.print("iqfi ulul");
    lcd.scrollDisplayLeft();
    Serial.println("sangat dekat.....");
  } else {
    pinMode(lampu, HIGH);
    // delay(200);
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("jarak:");
    lcd.print(distance);
    lcd.print(" cm");
  }
  delay(500);
}
