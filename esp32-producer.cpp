#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>

// Sends JSON data to a Python API, which will forward it to Kafka.
// Receives data from ESP32 via HTTP.
// Publishes it to Kafka

const char* ssid = getenv("WIFI_SSID");;  
const char* password = getenv("WIFI_PASSWORD");

// djanfo api end point
const char* api_url = getenv("API_URL");


void setup(){
    Serial.begin(115200);
    Wifi.begin(ssid, passwrd);

    while (WiFi.status() != WL_CONNECTED) {
        delay(1000);
        Serial.println("Connecting to WiFi...");
    }
    Serial.println("Connected to WiFi");
}

void loop(){
    float humidity = random(30, 80);  
    if (WiFi.status() == WL_CONNECTED) {
        // HTTP client object 
        HTTPClient http;

        // Starts http request 
        http.begin(api_url);
        http.addHeader("Content-Type", "application/json");

        StaticJsonDocument<200> jsonDoc;
        jsonDoc["sensor_id"] = "sensor_001"; 
        jsonDoc["humidity"] = humidity;
        
        // Convert json doc into string, flask expects a string 
        String jsonStr;
        serializeJson(jsonDoc, jsonStr);
        
        // Send json data using http post request 
        int httpResponseCode = http.POST(jsonStr);
        if (httpResponseCode > 0) {
            Serial.println("Data sent: " + jsonStr);
        } else {
            Serial.println("Error sending data: " + String(httpResponseCode));
        }
        http.end();
    }

    // delay(14400000);  // Send data every 4 hours
    delay(1000)
}

