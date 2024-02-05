 #include <Wire.h>
 #include <Adafruit_GFX.h>
 #include <Adafruit_SSD1306.h>

 const int lebar = 128;
 const int tinggi = 64;
 const int reset = 4;
 int num = 0;

 Adafruit_SSD1306 oled(lebar,tinggi,&Wire,reset);

 void setup() {
   // put your setup code here, to run once:
   oled.begin(SSD1306_SWITCHCAPVCC,0x3C);
   oled.clearDisplay();
 }

 void loop() {
   // put your main code here, to run repeatedly:
   oled.setTextSize(1);
   oled.setTextColor(WHITE);
   oled.setCursor(0,0);
   oled.println("helo world ");
//   oled.print(num++);
   oled.display();
 }
