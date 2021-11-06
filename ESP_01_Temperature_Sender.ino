#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>
#include <ArduinoJson.h>
#include <Chrono.h>

#define sendInterval 1000

const char* ssid = "Nataliya";
const char* password = "08061961";

Chrono      senderChrono;

String requestPath = "http://a2b7-92-112-198-38.ngrok.io/updateDeviceData/44rDuq17";

void setup() {
  Serial.begin(115200);
  connectToWiFi();
  pinMode(2, OUTPUT);
  digitalWrite(2, HIGH); //Indicate that all is ready
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
String getDataMessage() {
  DynamicJsonDocument doc(512);
  doc["temperature"] = 10.00;
  doc["humidity"] = 10.00;
  
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
