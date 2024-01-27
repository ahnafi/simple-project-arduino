#include <WiFi.h>
#include <LiquidCrystal_I2C.h>
#include <Servo.h>
// #include <HCSR04.h>

// variabel
const char *ssid = "abcd";
const char *pass = "qwertyui";
const char *url = "http://192.168.63.29:3000/api/payment";
const int redlamp = 19;
const int yellow = 18;
const int green = 5;
const int trigPin = 14;
const int echoPin = 12;

// initialisasi
LiquidCrystal_I2C lcd(0x27, 16, 2);
Servo myservo;

long getDistance()
{
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

void onRedLamp()
{
    digitalWrite(redlamp, HIGH);
    digitalWrite(yellow, LOW);
    digitalWrite(green, LOW);
}
void onYellowLamp()
{
    digitalWrite(redlamp, LOW);
    digitalWrite(yellow, HIGH);
    digitalWrite(green, LOW);
}
void onGreenLamp()
{
    digitalWrite(redlamp, LOW);
    digitalWrite(yellow, LOW);
    digitalWrite(green, HIGH);
}

void printRed()
{
    lcd.setCursor(0, 0);
    lcd.print("hello");
    lcd.setCursor(0, 1);
    lcd.print("hari .. tgl ..");
}
void printYellow()
{
    lcd.setCursor(0, 0);
    lcd.print("selamat datang :)");
    lcd.setCursor(0, 1);
    lcd.print("silahkan bayar");
}
void printGreen()
{
    lcd.setCursor(0, 0);
    lcd.print("selamat melanjutkan");
    lcd.setCursor(0, 1);
    lcd.print("perjalanan");
}

void stopServo(){
    myservo.write(90);
    delay(15);
}

void setup()
{
    Serial.begin(9600);
    lcd.init();
    lcd.begin(16, 2);
    lcd.backlight();
    pinMode(redlamp, OUTPUT);
    pinMode(yellow, OUTPUT);
    pinMode(green, OUTPUT);
    pinMode(trigPin, OUTPUT);
    pinMode(echoPin, INPUT);
    myservo.attach(26);
    WiFi.begin(ssid, pass);
    while (WiFi.status() != WL_CONNECTED)
    {
        Serial.print(".");
    }
    Serial.println("connected");
}

void loop()
{
    lcd.clear();
    long distance = getDistance();
    if (distance >= 20)
    {
        onRedLamp();
        printRed();
        myservo.write(90);
    }
    else if (distance >= 0 && distance <= 20)
    {
        onYellowLamp();
        printYellow();
        myservo.write(30);
        delay(2000);
        myservo.write(90);
        delay(2000);
        myservo.write(0);
        delay(2000);
        myservo.write(90);
        delay(2000);

        
        
    }
    delay(1000);
}