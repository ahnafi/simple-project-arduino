const int ldrPin = A0; // LDR sensor pin
const int redLedPin = 4;
const int yellowLedPin = 0;
const int greenLedPin = 2;

void setup()
{
  pinMode(ldrPin, INPUT);
  pinMode(redLedPin, OUTPUT);
  pinMode(yellowLedPin, OUTPUT);
  pinMode(greenLedPin, OUTPUT);
  Serial.begin(9600);
}

void loop()
{
  int ldrValue = analogRead(ldrPin);
  Serial.println(ldrValue);
  if (ldrValue > 1000)
  {
    digitalWrite(redLedPin, HIGH);
    digitalWrite(yellowLedPin, LOW);
    digitalWrite(greenLedPin, LOW);
  }
  else if (ldrValue > 500 && ldrValue < 1000)
  {
    digitalWrite(redLedPin, LOW);
    digitalWrite(yellowLedPin, HIGH);
    digitalWrite(greenLedPin, LOW);
  }
  else
  {
    digitalWrite(redLedPin, LOW);
    digitalWrite(yellowLedPin, LOW);
    digitalWrite(greenLedPin, HIGH);
  }
}
