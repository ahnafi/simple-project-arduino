#include <ESP8266WiFi.h>
#include <DHT.h>
#include <ESP8266HTTPClient.h>

const char *ssid = "abcd";
const char *password = "qwertyui";

#define LAMPU D1

#define dhtpin D4
#define dhttype DHT11

WiFiClient client;
HTTPClient http;

String serverip = "http://192.168.238.29:3000";
String path = "/api/post";

DHT dht(dhtpin, dhttype);

float temperature = 0;
float humidity = 0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  WiFi.begin(ssid, password);

  pinMode(LAMPU, OUTPUT);

  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }
  Serial.println("connect");
  Serial.println(WiFi.localIP());
  //
}

void loop() {
  // put your main code here, to run repeatedly:
  temperature = dht.readTemperature();
  humidity = dht.readHumidity();
  if (WiFi.status() == WL_CONNECTED) {
    //
    http.begin(client, serverip + path);
    http.addHeader("Content-Type", "application/json");
    //
    String text = "{\"temperature\":" + String(temperature) + ",\"humidity\":" + String(humidity) + "}";
    //
    int httpStatusCode = http.POST(text);

    if (httpStatusCode > 0) {
      String payload = http.getString();
      Serial.println(payload);
      pinMode(LAMPU, LOW);
      delay(400);
      pinMode(LAMPU, HIGH);
      delay(400);
    } else {
      Serial.println("error http");
    }
    //
    http.end();
  }
  delay(5000);
  // delay(600000);
}
