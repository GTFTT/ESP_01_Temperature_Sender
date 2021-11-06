#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>
#include <ArduinoJson.h>
#include <Chrono.h>
#include <DHT.h>

#define sendInterval 1000
#define DHT11_PIN 2

const char* ssid = "Nataliya";
const char* password = "08061961";
String      requestPath = "http://rtc-api-server.herokuapp.com/updateDeviceData/44rDuq17";

Chrono      senderChrono;
DHT         dht(DHT11_PIN, DHT11);


void setup() {
  Serial.begin(115200);
  connectToWiFi();
  dht.begin();
}

void loop() {
  if(senderChrono.hasPassed(sendInterval, true)) {
    //Check WiFi connection status
    if(WiFi.status() == WL_CONNECTED){
      WiFiClient client;
      HTTPClient http;

      http.begin(client, requestPath.c_str());

      String message = getDataMessage();
//      String message = "{\"data\": {\"val\": 12}}";
      Serial.println((String)"Message: " + message);
      
      // Send HTTP GET request
      int httpCode = http.PATCH(message.c_str());   //Send the request
      String payload = http.getString();                  //Get the response payload
  
      Serial.println(httpCode);   //Print HTTP return code
      Serial.println(payload);    //Print request response payload
  
      http.end();  //Close connection
    } else {
      Serial.println(F("WiFi connection lost/not connected. Atrtempt to reconnect."));
      connectToWiFi();
    }
  }
}

//Generate json ready to be sent
//Notice that huminity has to be mesured once per second maximum for DHT11
String getDataMessage() {
  DynamicJsonDocument doc(512);
  float temperature = dht.readTemperature();
  float humidity = dht.readHumidity();
  
  if (isnan(temperature) || isnan(humidity)) {
    Serial.println("Failed to read from DHT sensor!");
  } else {
    Serial.println((String)"Temperature = " + temperature);
    Serial.println((String)"Humidity = " + humidity);
    doc["data"]["temperature"] = temperature;
    doc["data"]["humidity"] = humidity;
  }

  String message;
  serializeJson(doc, message);

  return message;
}

void connectToWiFi() {
  // Connect to wifi
  WiFi.begin(ssid, password);

  // Wait some time to connect to wifi
  Serial.print("Connecting");
  while(WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println();

  // Check if connected to wifi
  if (WiFi.status() == WL_CONNECTED) {
    Serial.print(F("Connected to WiFi network with IP Address: "));
    Serial.println(WiFi.localIP());
  } else {
    Serial.println("Failded to connect to Wifi!");
  }
}
