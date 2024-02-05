#include <WiFi.h>
#include <HTTPClient.h>

const char *ssid = "abcd";
const char *password = "qwertyui";
const char *postEndpoint = "http://192.168.63.29:3000/api/payment";

void setup()
{
    Serial.begin(115200);

    // Connect to Wi-Fi
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED)
    {
        delay(1000);
        Serial.println("Connecting to WiFi...");
    }
    Serial.println("Connected to WiFi");

    // Perform HTTP POST
    performHttpPost();
}

void loop()
{
    // Your main code here
    performHttpPost();
    delay(5000);
}

void performHttpPost()
{
    // Create an HTTPClient object
    HTTPClient http;

    // Specify the target URL
    http.begin(postEndpoint);

    // Set content type to application/json
    http.addHeader("Content-Type", "application/json");

    // Prepare the payload for the POST request
    int numPay = 123412;
    String payload = "{\"numPay\":\" " + String(numPay) + " \"}";

    // Send the POST request
    int httpResponseCode = http.POST(payload);

    // Check for a successful response
    if (httpResponseCode > 0)
    {
        Serial.print("HTTP POST Success, Response code: ");
        Serial.println(httpResponseCode);

        // Print the response payload
        String responsePayload = http.getString();
        Serial.println("Response payload: " + responsePayload);
    }
    else
    {
        Serial.print("HTTP POST Failed, Response code: ");
        Serial.println(httpResponseCode);
    }

    // Close the connection
    http.end();
}
