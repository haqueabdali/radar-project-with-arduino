#include <Arduino.h>
#include <WiFi.h>
#include <PubSubClient.h>
#include <ArduinoJson.h>
#include <AccelStepper.h>
#include <HCSR04.h>

// WiFi Configuration
const char* ssid = "vodafone";
const char* password = "1223334444";

// MQTT Configuration
const char* mqtt_server = "broker.hivemq.com";
const char* topic = "abdali/radar/data";

// Stepper Motor Configuration
#define MOTOR_TYPE 8
#define STEPS_PER_REV 2048
AccelStepper stepper(MOTOR_TYPE, 12, 14, 13, 15); // IN1, IN2, IN3, IN4

// Ultrasonic Sensor
HCSR04 hc(5, 18); // TRIG, ECHO

// Network Clients
WiFiClient espClient;
PubSubClient client(espClient);

void setup_wifi() {
  delay(10);
  Serial.print("Connecting to ");
  Serial.println(ssid);
  
  WiFi.begin(ssid, password);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  
  Serial.println("\nWiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void reconnect() {
  while (!client.connected()) {
    Serial.print("Connecting to MQTT broker...");
    
    if (client.connect("ESP32RadarClient")) {
      Serial.println("connected");
      client.publish(topic, "{\"status\":\"online\"}");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" retrying in 5s");
      delay(5000);
    }
  }
}

void setup() {
  Serial.begin(115200);
  
  // Stepper motor setup
  stepper.setMaxSpeed(500);
  stepper.setAcceleration(300);
  
  // Initialize WiFi
  setup_wifi();
  
  // MQTT setup
  client.setServer(mqtt_server, 1883);
}

void loop() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop();

  // Perform 180° scan
  stepper.moveTo(STEPS_PER_REV/2);
  while(stepper.distanceToGo() != 0) {
    stepper.run();
    
    // Take measurement every 10°
    if(stepper.distanceToGo() % (STEPS_PER_REV/36) == 0) {
      int angle = map(stepper.currentPosition(), 0, STEPS_PER_REV/2, 0, 180);
      float distance = hc.dist();
      
      if(isnan(distance) distance = 0;
      
      // Create JSON payload
      StaticJsonDocument<128> doc;
      doc["device"] = "radar-01";
      doc["angle"] = angle;
      doc["distance"] = distance;
      doc["rssi"] = WiFi.RSSI();
      
      char payload[128];
      serializeJson(doc, payload);
      
      // Publish data
      client.publish(topic, payload);
      Serial.println(payload);
    }
  }
  
  // Return to start position
  stepper.moveTo(0);
  while(stepper.distanceToGo() != 0) {
    stepper.run();
  }
  
  delay(3000); // Wait before next scan
}