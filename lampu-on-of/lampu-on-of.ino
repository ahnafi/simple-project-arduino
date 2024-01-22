void setup()
{
   // menjadikan PIN 4 sebagai OUTPUT
   pinMode(D4, OUTPUT);
}

void loop()
{
   // Menyalakan PIN 4 (HIGH = Memberi tegangan pada PIN 4)
   digitalWrite(D4, HIGH);
   // Pause selama 1 detik
   delay(1000);

   // Mematikan PIN 4 (LOW = Tidak Memberi tegangan pada PIN 4)
   digitalWrite(D4, LOW);
   // Pause selama 1 detik
   delay(1000);
}