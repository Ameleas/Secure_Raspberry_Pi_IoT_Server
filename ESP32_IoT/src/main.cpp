#include <Arduino.h>
#define PIR_PIN 13

void setup() {
  Serial.begin(115200);
  pinMode(PIR_PIN, INPUT);
  Serial.println("Testing PIR...");
}

void loop() {
  int state = digitalRead(PIR_PIN);
  Serial.println(state ? "Motion detected!" : "No motion");
  delay(1000);
}


/* #include <ArduinoJson.h>
#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <PubSubClient.h>
#include "certs.h"

const char* ssid = "Amelea";
const char* password = "elspels83";
const char* mqtt_server = "10.147.106.112";
const int mqtt_port = 8883;  // Säker port

#define PIR_PIN 13
#define MSG_BUFFER_SIZE (50)

WiFiClientSecure espClient;
PubSubClient client(espClient);
unsigned long lastMsg = 0;
char msg[MSG_BUFFER_SIZE];

void setup_wifi() {
  delay(100);
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  
  WiFi.begin(ssid, password);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  
  randomSeed(micros());
  
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
  }
  Serial.println();
}

void reconnect() {
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    String clientId = "ESP32Client-";
    clientId += String(random(0xffff), HEX);
    
    if (client.connect(clientId.c_str())) {
      Serial.println("connected");
      client.publish("/home/status", "ESP32 connected");
      client.subscribe("/home/commands");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      delay(5000);
    }
  }
}

void setup() {
  Serial.begin(115200);
  while (!Serial);
  Serial.println(F("PIR test with mTLS"));
  
  pinMode(PIR_PIN, INPUT);
  Serial.println("PIR sensor initialized!");
  
  setup_wifi();
  
  // Konfigurera TLS/SSL
  espClient.setCACert(ca_cert);
  espClient.setCertificate(client_cert);
  espClient.setPrivateKey(client_key);
  
  client.setServer(mqtt_server, mqtt_port);
  client.setCallback(callback);
  
  Serial.println("mTLS configured");
}

void loop() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop();
  
  StaticJsonDocument<128> doc;
  char output[55];
  
  long now = millis();
  if (now - lastMsg > 5000) {
    lastMsg = now;
    
    // Ta bort kommentar för att använda riktig sensor:
   bool motionDetected = digitalRead(PIR_PIN);
    
    // Simulering utan hårdvara:
    // bool motionDetected = random(0, 2);
    
    doc["motion"] = motionDetected;
    
    serializeJson(doc, output);
    Serial.println(output);
    client.publish("/home/sensors", output);
    Serial.println("Sent via mTLS");
  }
}
  */











/* 
#include <ArduinoJson.h>
#include <ArduinoJson.hpp>
#include <WiFi.h>
#include <PubSubClient.h>
#include <Wire.h>

const char* ssid = "Amelea";
const char* password = "elspels83";
const char* mqtt_server = "10.147.106.112";

#define PIR_PIN 13   // GPIO där HC-SR501 är kopplad (ändra vid behov)
#define MSG_BUFFER_SIZE (50)


WiFiClient espClient;
PubSubClient client(espClient);
unsigned long lastMsg = 0;
#define MSG_BUFFER_SIZE	(50)
char msg[MSG_BUFFER_SIZE];
int value = 0;

void setup_wifi() {

  delay(100);
  // We start by connecting to a WiFi network
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  randomSeed(micros());

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void callback(char* topic, byte* payload, unsigned int length) {

}

void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Create a random client ID
    String clientId = "ESP32Client-";
    clientId += String(random(0xffff), HEX);
    // Attempt to connect
    if (client.connect(clientId.c_str())) {
      Serial.println("connected");
      // Once connected, publish an announcement...
      client.publish("outTopic", "hello world");
      // ... and resubscribe
      client.subscribe("inTopic");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}

void setup() {
  Serial.begin(115200);
  while (!Serial);
  Serial.println(F("PIR test"));

  pinMode(PIR_PIN, INPUT);
  Serial.println("PIR sensor initialized!");

  setup_wifi();
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);
}

void loop() {

  if (!client.connected()) {
    reconnect();
  }
  client.loop();
  StaticJsonDocument<32> doc;
  char output[55];

  long now = millis();
  if (now - lastMsg > 5000) {
    lastMsg = now;

    //bool motionDetected = digitalRead(PIR_PIN); 
    //simulera utan hårdvara:
    bool motionDetected = random(0, 2);

    doc["motion"] = motionDetected;

    serializeJson(doc, output);
    Serial.println(output);
    client.publish("/home/sensors", output);
    Serial.println("Sent");
  }  
}
*/