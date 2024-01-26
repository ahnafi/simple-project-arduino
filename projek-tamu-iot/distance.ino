#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);
const int echoPin = 0;
const int trigPin = 2;

void setup()
{
    pinMode(trigPin, OUTPUT);
    pinMode(echoPin, INPUT);
    lcd.init();
    lcd.begin(16, 2);
    lcd.clear();
    lcd.backlight();
}
void loop()
{
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);
    long duration = pulseIn(echoPin, HIGH);
    long distance = duration / 58;

    lcd.setCursor(0, 0);
    lcd.print("distance");
    lcd.setCursor(0, 1);
    lcd.print(distance);
    lcd.println("cm               .");
    delay(50);
}