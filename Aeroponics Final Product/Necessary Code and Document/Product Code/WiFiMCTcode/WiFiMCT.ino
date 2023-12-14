// Import required libraries
#include <ESP8266WiFi.h>
#include "ESPAsyncWebServer.h"

// Set your access point network credentials
const char* ssid = "ESP8266";
const char* password = "123456789";
String id;
int idk;

String strtotal;
int statmarksend;
int statmark0=0;
int statmark1=0;
int statmark2=0;
int statmark3=0;
int statmark4=0;
int statmark5=0;
int statmark6=0;
int statmark7=0;


String test() {
  return String(strtotal);
}


// Create AsyncWebServer object on port 80
AsyncWebServer server(80);


void setup(){
  // Serial port for debugging purposes
  Serial.begin(115200);
  Serial.println();
  
  // Setting the ESP as an access point
  Serial.print("Setting AP (Access Point)…");
  // Remove the password parameter, if you want the AP (Access Point) to be open
  WiFi.softAP(ssid, password);

  IPAddress IP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(IP);

  server.on("/signal", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/plain", test().c_str());
  });
  
  bool status;
  
  // Start server
  server.begin();
}
 
void loop(){
  command();
}

void command () {
    while (Serial.available() > 0 ) {
    strtotal  = Serial.readString();

    id=strtotal.substring(14,15);
    idk=id.toInt();
    if (idk==0) {
      if (statmark0 == 1) {
        statmark0=0;
        } else if (statmark0 == 0) {
        statmark0=1;
      }
      statmarksend=statmark0;
    }
    if (idk==1) {
      if (statmark1 == 1) {
        statmark1=0;
        } else if (statmark1 == 0) {
        statmark1=1;
      }
      statmarksend=statmark1;
    }
    if (idk==2) {
      if (statmark2 == 1) {
        statmark2=0;
        } else if (statmark2 == 0) {
        statmark2=1;
      }
      statmarksend=statmark2;
    }
    if (idk==3) {
      if (statmark3 == 1) {
        statmark3=0;
        } else if (statmark3 == 0) {
        statmark3=1;
      }
      statmarksend=statmark3;
    }
    if (idk==4) {
      if (statmark3 == 4) {
        statmark4=0;
        } else if (statmark4 == 0) {
        statmark4=1;
      }
      statmarksend=statmark4;
    }
    if (idk==5) {
      if (statmark5 == 1) {
        statmark5=0;
        } else if (statmark5 == 0) {
        statmark5=1;
      }
      statmarksend=statmark5;
    }
    if (idk==6) {
      if (statmark6 == 1) {
        statmark6=0;
        } else if (statmark6 == 0) {
        statmark6=1;
      }
      statmarksend=statmark6;
    }
    if (idk==7) {
      if (statmark7 == 1) {
        statmark7=0;
        } else if (statmark7 == 0) {
        statmark7=1;
      }
      statmarksend=statmark7;
    }

    strtotal=strtotal+statmarksend;
    Serial.println("sent");
    Serial.println(strtotal);
   }

}