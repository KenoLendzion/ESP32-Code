#include <DHT.h>
#include <WiFi.h>
#include <HTTPClient.h>

#define DHT_SENSOR_PIN 21
#define DHT_SENSOR_TYPE DHT22
DHT dht_sensor(DHT_SENSOR_PIN, DHT_SENSOR_TYPE);

const char* ssid = "FRITZ!Box 7530 MP";
const char* password = "06533451280163751744";
String serverName = "http://173.212.229.204/addtemp/";

void setup() {
  Serial.begin(9600);
  dht_sensor.begin();
  
  WiFi.begin(ssid, password);
  Serial.println("Connecting");
  while(WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to WiFi network with IP Address: ");
  Serial.println(WiFi.localIP());
 
  Serial.println("Timer set to 5 seconds (timerDelay variable), it will take 5 seconds before publishing the first reading.");
}

void loop() {
  
  
  int temp = dht_sensor.readTemperature();
  if ( isnan(temp) ) {
    Serial.println("Failed to read from DHT sensor!");
  }

  Serial.println(temp);
  String serverPath = serverName + temp;
  String httpRequestData = "temperature=2345";  
  HTTPClient http;
  http.begin(serverPath.c_str());
  int httpResponseCode = http.POST(httpRequestData);
  if (httpResponseCode>0) {
        Serial.print("HTTP Response code: ");
        Serial.println(httpResponseCode);
        String payload = http.getString();
        Serial.println(payload);
      }
      else {
        Serial.print("Error code: ");
        Serial.println(httpResponseCode);
      }
  http.end();
  
  delay(10000);
}
