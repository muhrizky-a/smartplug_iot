#include <ArduinoJson.h>

// Define sensor pins here
#define RELAY1 D3
#define RELAY2 D4

void settingPinMode(){
  pinMode(RELAY1, OUTPUT);
  pinMode(RELAY2, OUTPUT);
}

String readRelayValues(){
  String msg = "{";
  msg += "\"relay1\":";
  msg += 1;
  msg += ",";
  msg += "\"relay2\":";
  msg += 0;
  msg += "}";
  return msg;
}


void controlSensor(String message){

  // Deserialize Json
  DynamicJsonDocument doc(1024);
  deserializeJson(doc, message);
  int relay1 = doc["relay1"];
  int relay2 = doc["relay2"];

  // Control the relay
  if(relay1 == 1){
    digitalWrite(RELAY1, HIGH);  
  } else {
    digitalWrite(RELAY1, LOW);
  }

  if(relay2 == 1){
    digitalWrite(RELAY2, HIGH);  
  } else {
    digitalWrite(RELAY2, LOW);
  }
}
