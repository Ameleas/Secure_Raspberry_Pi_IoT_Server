#include <ArduinoJson.h>
#include <WiFiClientSecure.h>
#include <PubSubClient.h>
#include "certs.h"

const char* ssid = "TYPE_YOUR_SSID_HERE";
const char* password = "TYPE_YOUR_PASSWORD_HERE";
const char* mqtt_server = "TYPE_YOUR_MQTT_SERVER_IPV4_HERE";
const int mqtt_port = 8883;  // Säker port

#define PIR_PIN 13
#define MSG_BUFFER_SIZE (50)

WiFiClientSecure espClient;
PubSubClient client(espClient);
unsigned long lastMsg = 0;
char msg[MSG_BUFFER_SIZE];

bool lastMotionState = false;

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
  
  // Ta bort kommentar för att använda riktig sensor:
  bool motionDetected = digitalRead(PIR_PIN);

  if (motionDetected != lastMotionState) {
    lastMotionState = motionDetected;
    
    doc["motion"] = motionDetected;
    
    serializeJson(doc, output);
    Serial.println(output);
    client.publish("/home/sensors", output);
    Serial.println("Sent via mTLS");
  }
  delay(200); // Debounce delay
}
