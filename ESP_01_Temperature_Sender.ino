
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>

const char* ssid = "Nataliya";
const char* password = "08061961";

//Your Domain name with URL path or IP address with path
String serverName = "http://8eb9-92-112-198-38.ngrok.io/updateDeviceData/44rDuq17";

unsigned long lastTime = 0;
unsigned long timerDelay = 1000;

void setup() {
  Serial.begin(115200);
  pinMode(2, OUTPUT);

  WiFi.begin(ssid, password);
  Serial.println("Connecting");
  while(WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to WiFi network with IP Address: ");
  Serial.println(WiFi.localIP());
  digitalWrite(2, HIGH); //Indicate that all is ready
}

void loop() {
  // Send an HTTP POST request depending on timerDelay
  if ((millis() - lastTime) > timerDelay) {
    //Check WiFi connection status
    if(WiFi.status()== WL_CONNECTED){
      WiFiClient client;
      HTTPClient http;

      http.begin(client, serverName.c_str());
      
      // Send HTTP GET request
      int httpCode = http.PATCH("{\"data\": {\"hi\": 123}}");   //Send the request
      String payload = http.getString();                  //Get the response payload
  
      Serial.println(httpCode);   //Print HTTP return code
      Serial.println(payload);    //Print request response payload
  
      http.end();  //Close connection
    } else {
      Serial.println("WiFi Disconnected");
    }
    lastTime = millis();
  }
}
