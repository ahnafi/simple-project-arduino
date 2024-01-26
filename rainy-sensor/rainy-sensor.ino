#define rainAnalog A0
#define rainDigital 5

#define buzzer 4

void setup()
{
    Serial.begin(9600);
    pinMode(rainDigital, INPUT);
    pinMode(buzzer, OUTPUT);
}
void loop()
{
    pinMode(buzzer, LOW);
    int rainAnalogVal = analogRead(rainAnalog);
    int rainDigitalVal = digitalRead(rainDigital);

    if (rainDigitalVal == 0)
    {
        pinMode(buzzer, HIGH);
        digitalWrite(buzzer, HIGH);
        delay(200);
        digitalWrite(buzzer, LOW);
        delay(200);
    }

    Serial.print(rainAnalogVal);
    Serial.print("\t");
    Serial.println(rainDigitalVal);
    delay(200);
}