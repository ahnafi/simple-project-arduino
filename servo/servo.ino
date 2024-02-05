#include <ESP32Servo.h>

Servo myServo;  // Create a servo object

void setup() {
  myServo.attach(18);
  Serial.begin(9600);
}

void loop() {
  //  int speed = Serial.read();

    myServo.write(50);
    delay(1000);
    myServo.write(359);
    delay(1000);
}
