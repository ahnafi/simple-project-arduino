const int sensorPin = A0;  // Connect the sensor to analog pin A0

void setup() {
  Serial.begin(9600);  // Initialize serial communication
}

void loop() {
  // Read the sensor value
  int sensorValue = analogRead(sensorPin);

  // Print the sensor value to the Serial Monitor
  Serial.print("Light Intensity: ");
  Serial.println(sensorValue);

  delay(1000);  // Wait for 1 second before reading the sensor again
}
