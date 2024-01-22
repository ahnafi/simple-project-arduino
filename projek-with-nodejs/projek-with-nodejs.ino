#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <ESPAsyncWebServer.h>


const char *ssid = "abcd";
const char *password = "qwertyui";
const char *serverIp = "192.168.238.29:3000";
const char *endpoint = "/api/data";

#define lampuPin D4

// void setup() {
//   // put your setup code here, to run once:
//   Serial.begin(9600);
//   WiFi.begin(ssid, password);
//   pinMode(lampu, OUTPUT);

//   while (WiFi.status() != WL_CONNECTED) {
//     delay(1000);
//     Serial.println("Connecting wifi ssid -> " + String(ssid));
//   }
// }

// void loop() {
//   // put your main code here, to run repeatedly:
//   if (WiFi.status() == WL_CONNECTED) {

//     // class dari esp8266 httpclient
//     WiFiClient client;
//     HTTPClient http;

//     String url = "http://" + String(serverIp) + endpoint;

//     http.begin(client, url);
//     http.addHeader("Content-Type", "application/json");

//     int httpStatus = http.GET();

//     if (httpStatus > 0) {
//       String response = http.getString();
//       Serial.println(response);
//     } else {
//       Serial.println(http.getString());
//       Serial.println("Error on http request");
//     }

//     http.end();
//     delay(5000);
//     // digitalWrite(lampu, HIGH);
//     // delay(2500);
//     // digitalWrite(lampu, LOW);
//     // delay(2500);
//   }
// }


AsyncWebServer server(80);

void setup() {
  Serial.begin(115200);
  Serial.println(WiFi.localIP());
  pinMode(lampuPin, OUTPUT);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }

  // Handle endpoint untuk menghidupkan lampu
  server.on("/api/lampu/on", HTTP_POST, [](AsyncWebServerRequest *request){
    digitalWrite(lampuPin, HIGH);
    request->send(200, "text/plain", "Lampu dinyalakan");
  });

  // Handle endpoint untuk mematikan lampu
  server.on("/api/lampu/off", HTTP_POST, [](AsyncWebServerRequest *request){
    digitalWrite(lampuPin, LOW);
    request->send(200, "text/plain", "Lampu dimatikan");
  });

  // Inisialisasi server
  server.begin();
}

void loop() {
  // Kode utama dapat ditambahkan di sini
  Serial.println(WiFi.localIP());
  delay(5000);
}

