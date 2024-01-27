// #include <wifi.h>
#include <LiquidCrystal_I2C.h>
#include <Servo.h>
#include <HCSR04.h>

// variabel
const char *ssid = "abcd";
const char *pass = "qwertyui";
const char *url = "http://";
const int redlamp = 34;
const int yellow = 35;
const int green = 32;

// initialisasi
LiquidCrystal_I2C lcd(0x27, 16, 2);
UltraSonicDistanceSensor distanceSensor(14, 12); // trig , echo
Servo myservo;

void setup()
{
    Serial.begin(9600);
    lcd.init();
    lcd.begin(16, 2);
    lcd.backlight();
    pinMode(redlamp, OUTPUT);
    pinMode(yellow, OUTPUT);
    pinMode(green, OUTPUT);
    myservo.attach(26);
}

void loop()
{
   for(int posDegrees = 0; posDegrees <= 180; posDegrees++) {
        myservo.write(posDegrees);
        Serial.println(posDegrees);
        delay(20);
    }

    for(int posDegrees = 180; posDegrees >= 0; posDegrees--) {
        myservo.write(posDegrees);
        Serial.println(posDegrees);
        delay(20);
    }
}