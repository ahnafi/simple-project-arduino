#include <Servo.h>

Servo myServo;  // Create a servo object

void setup() {
  myServo.attach(D8);  // Attach the servo to pin 9
}

void loop() {
  // Move the servo to the starting position (0 degrees)
  myServo.write(0);
  delay(1000);  // Wait for 1 second

  // Move the servo to the middle position (90 degrees)
  myServo.write(160);
  delay(1000);  // Wait for 1 second

  // Move the servo to the end position (180 degrees)
  myServo.write(180);
  delay(1000);  // Wait for 1 second
}
