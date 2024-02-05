#include <WiFi.h>
#include <LiquidCrystal_I2C.h>
#include <HTTPClient.h>
// #include <ESP32Servo.h>
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
const int touchPin = T0;
long numberPayment = 0;

// initialisasi
LiquidCrystal_I2C lcd(0x27, 16, 2);
HTTPClient http;

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
    lcd.print("semangat!!");
}
void printYellow(long payment)
{
    lcd.setCursor(2, 0);
    lcd.print("code payment");
    lcd.setCursor(0, 1);
    lcd.print("    " + payment);
}
void printGreen()
{
    lcd.setCursor(0, 0);
    lcd.print("hati hati");
    lcd.setCursor(0, 1);
    lcd.print("dijalan :)");
}

long generateRandomNumber()
{
    // Use random() to generate a random number in the range [10000000, 99999999]
    return random(10000000, 100000000);
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
    WiFi.begin(ssid, pass);
    while (WiFi.status() != WL_CONNECTED)
    {
        Serial.print(".");
        lcd.print(".");
        delay(15);
    }
    Serial.println("connected");
}

void loop()
{
    lcd.clear();
    long distance = getDistance();
    int touch = touchRead(touchPin);
    http.begin(url);
    http.addHeader("Content-Type", "application/json");

    if (touch < 15)
    {
        onGreenLamp();
        printGreen();
        numberPayment = 0; // succes pay , number payment set 0
    }
    else
    {
        if (distance >= 20) // red
        {
            onRedLamp();
            printRed();
        }
        else if (distance >= 0 && distance <= 20) // yellow
        {
            onYellowLamp();
            if (numberPayment > 0)
            {
                printYellow(numberPayment);
            }
            else
            {
                numberPayment = generateRandomNumber();
                printYellow(numberPayment);
            }
            String request = "{\"numPay\":\"" + String(numberPayment) + "\"}";
            int statusCode = http.POST(request);
            if (statusCode > 0)
            {
                Serial.print(http.getString());
            }else{
                Serial.println("http err");
            }
        }
    }

    delay(1000);
}