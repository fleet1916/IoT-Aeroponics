#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>

#include <ESP8266WiFiMulti.h>
ESP8266WiFiMulti WiFiMulti;


int stationnum= 1; 

const char* ssid = "ESP8266";
const char* password = "123456789";

//Your IP address or domain name with URL path
const char* serverNamesig = "http://192.168.4.1/signal";



String signal;
String strmark;
String strnum;
int idk;
int controller;
int bookmark;
int lastmark =0;
String command;


unsigned long previousMillis = 0;
const long interval = 500; 

void setup() {
  Serial.begin(115200);
  Serial.println();

  Serial.print("Connecting to ");
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("Connected to WiFi");
}

void loop() {
  unsigned long currentMillis = millis();
  
  if(currentMillis - previousMillis >= interval) {
    // Check WiFi connection status
    if ((WiFiMulti.run() == WL_CONNECTED)) {
      signal = httpGETRequest(serverNamesig);
      strnum=signal.substring(14,15);
      idk=strnum.toInt();
    
      if (idk==stationnum) {
      strmark=signal.substring(15);
      bookmark=strmark.toInt();
      command=signal.substring(0,15);
      if (bookmark !=  lastmark) {
        Serial.println(command);
        lastmark=bookmark;
      }
    }
      
      
      
      previousMillis = currentMillis;
    }
    else {
      Serial.println("WiFi Disconnected");
    }
  }
}

String httpGETRequest(const char* serverName) {
  WiFiClient client;
  HTTPClient http;
    
  // Your IP address with path or Domain name with URL path 
  http.begin(client, serverName);
  
  // Send HTTP POST request
  int httpResponseCode = http.GET();
  
  String payload = "--"; 
  
  if (httpResponseCode>0) {
    payload = http.getString();
  }
  else {
    Serial.print("Error code: ");
    Serial.println(httpResponseCode);
  }
  // Free resources
  http.end();

  return payload;
}