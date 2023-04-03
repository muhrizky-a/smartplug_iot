#include "credentials.h"
#include "sensor_pins.h"
#include <ESP8266WiFi.h>
#include <PubSubClient.h>

WiFiClient espClient;
PubSubClient client(espClient);

unsigned long lastMsg = 0;
#define MSG_BUFFER_SIZE  (50)
char msg[MSG_BUFFER_SIZE];
int value = 0;


// menerima data
void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Received [");
  Serial.print(topic);
  Serial.print("] ");

  String message = "";
  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
    message += (char)payload[i];
  }
  Serial.println();
  
  controlSensor(message);
}


void setup() {
  settingPinMode();
  Serial.begin(115200);
  setupWifi();
  client.setServer(MQTT_SERVER, MQTT_PORT);
  client.setCallback(callback);
}

String lastMessage = "";
void loop() {
  if (!client.connected()) {
    reconnectBroker();
  }
  client.loop();

  // Hanya jika state berubah maka message di-publish
//  String currentMessage = readRelayValues();
//  if(currentMessage != lastMessage){
//    publishMessage(MQTT_TOPIC, currentMessage.c_str());  
//    lastMessage = currentMessage;
//  }
  
  delay(2000);
}
