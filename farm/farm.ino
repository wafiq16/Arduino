#define DISABLE_TLS
#include <ESP8266WiFi.h>
#include <ThingerESP8266.h>
#include <WiFiClientSecure.h>
#include <PubSubClient.h>
#include <string.h>
#include <ArduinoJson.h>
#include "DHT.h"

#define FAN_PIN1 D2   // FAN RELAY
#define FAN_PIN2 D7
#define FAN_PIN3 D8
#define LAMPU_PIN D3
#define AIR_PIN D1

#define USERNAME "bagasggg" // sudah sama
#define DEVICE_ID "Kontrol_suhu"
#define DEVICE_CREDENTIAL "+RTT&853B!ASDfTF"
#define SSID "Redmi 4X_8266"
#define SSID_PASSWORD "123456789"
#define mqtt_port 1883
#define MQTT_USER "Techiotpartner"
#define MQTT_PASSWORD "12345678"
#define PUBTOPICDEMO1 "/farmMonitor"
#define SUBTOPICDEMO1 "/farmControl"

const char* mqtt_server = "broker.hivemq.com";

// Initialize DHT sensor.
DHT dht11(D6, DHT11);
DHT dht22(D5, DHT22);
ThingerESP8266 thing(USERNAME, DEVICE_ID, DEVICE_CREDENTIAL);

WiFiClient espClient;
PubSubClient client(espClient);

//relay state
int c = 0; // 1 & 2
int f = 0; // 3 & 4
int g = 0; // 5

int Time_Temp;
double t1, t2, h1, h2;

void setup() {
  Serial.begin(115200);
  pinMode(AIR_PIN, OUTPUT);
  pinMode(FAN_PIN1, OUTPUT);
  digitalWrite(FAN_PIN1, LOW);
  pinMode(FAN_PIN2, OUTPUT);
  digitalWrite(FAN_PIN2, LOW);
  pinMode(FAN_PIN3, OUTPUT);
  digitalWrite(FAN_PIN3, LOW);
  pinMode(LAMPU_PIN, OUTPUT);
  digitalWrite(LAMPU_PIN, LOW);
  Serial.println(F("DHTxx test!"));
  dht22.begin();
  thing.add_wifi(SSID, SSID_PASSWORD);
  thing["AIR"] << digitalPin(AIR_PIN);
  thing["dht11"] >> [](pson & out) {
    // Add the values and the corresponding code
    out["humidity"] = dht22.readHumidity();
    out["celsius"] = dht22.readTemperature();
  };
  dht11.begin();
  thing["dht11-2"] >> [](pson & out) {
    // Add the values and the corresponding code
    out["humidity"] = dht11.readHumidity();
    out["celsius"] = dht11.readTemperature();
  };
  WiFi.begin(SSID, SSID_PASSWORD);
  client.setServer(mqtt_server, mqtt_port);
  client.setCallback(callback);
  reconnect();
  client.subscribe(SUBTOPICDEMO1);
}

void callback(char* topic, byte *payload, unsigned int length) {
  StaticJsonDocument<200> doc;

  DeserializationError error = deserializeJson(doc, (char*)payload);

  c = doc["relay1"];
  f = doc["relay2"];
  g = doc["relay3"];

  Serial.println("Button 1 sekarang")
  Serial.println(c == 1 ? "menyala" : "mati");
  Serial.println("Button 2 sekarang")
  Serial.println(f == 1 ? "menyala" : "mati");
  Serial.println("Button 3 sekarang")
  Serial.println(g == 1 ? "menyala" : "mati");
  Serial.println(f);
  Serial.println(g);
}

void loop() {

  // Wait a few seconds between measurements.
  //  delay(2000);



  if (millis() - Time_Temp > 2000) {
    //    publishSerialData(myBuffer, PUBTOPICDEMO1);
    h1 = dht11.readHumidity();
    t1 = dht11.readTemperature();
    h2 = dht22.readHumidity();
    t2 = dht22.readTemperature();
    Time_Temp = millis();
  }


  // Check if any reads failed and exit early (to try again).
  if (isnan(h1) || isnan(t1))
  {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

  Serial.print(F("Temperature: "));
  Serial.print(t1);
  Serial.print(F("°C "));
  Serial.println();
  Serial.print(F("Humidity: "));
  Serial.print(h1);
  Serial.print(F("%"));
  Serial.println();

  Serial.println("***");
  Serial.println();

  // Check if any reads failed and exit early (to try again).
  if (isnan(h2) || isnan(t2))
  {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

  Serial.print(F("Temperature: "));
  Serial.print(t2);
  Serial.print(F("°C "));
  Serial.println();
  Serial.print(F("Humidity: "));
  Serial.print(h2);
  Serial.print(F("%"));
  Serial.println();

  Serial.println("***");
  Serial.println();

  DynamicJsonDocument root(1024);
  root["suhu1"] = t1;
  root["kelembapan1"] = h1;
  root["pompa1"] = c;
  root["suhu2"] = t2;
  root["kelembapan2"] = h2;
  root["pompa2"] = f;
  root["pompa3"] = g;

  char myBuffer[1023];
  serializeJson(root, myBuffer);

  if (!client.connected())
  {
    reconnect();
  }
  //  Serial.println(myBuffer);
  if (millis() - Time_Temp > 2000) {
    publishSerialData(myBuffer, PUBTOPICDEMO1);
    Time_Temp = millis();
  }


  // Compare Threshold value from Blynk and DHT Temperature value.
  if (c == 1)
  {
    digitalWrite(FAN_PIN1, HIGH);
    //    thing.call_endpoint("KIPAS_MENYALA");
  }
  else {
    digitalWrite(FAN_PIN1, LOW);
    //    thing.handle();
  }

  // Compare Threshold value from Blynk and DHT Temperature value.
  if (c == 1)
  {
    digitalWrite(LAMPU_PIN, HIGH);
    //    thing.call_endpoint("LAMPU_MENYALA");
  }
  else {
    digitalWrite(LAMPU_PIN, LOW);
    //    thing.handle();
  }
  if (f == 1)
  {
    digitalWrite(FAN_PIN2, HIGH);
  }
  else {
    digitalWrite(FAN_PIN2, LOW);
    //    thing.handle();
  }

  // Compare Threshold value from Blynk and DHT Temperature value.
  if (f == 1)
  {
    digitalWrite(FAN_PIN3, HIGH);
  }
  else {
    digitalWrite(FAN_PIN3, LOW);
    //    thing.handle();
  }

  if (g == 1)
  {
    digitalWrite(AIR_PIN, HIGH);
  }
  else {
    digitalWrite(AIR_PIN, LOW);
    //    thing.handle();
  }
  client.loop();
}

void reconnect() {
  while (!client.connected()) {
    String clientId = "device1";
    if (client.connect(clientId.c_str(), MQTT_USER, MQTT_PASSWORD)) {
      client.subscribe(SUBTOPICDEMO1);
    } else {
      delay(100);
    }
  }
}

void publishSerialData(char *serialData, char* topic) {
  if (!client.connected()) {
    reconnect();
  }
  client.publish(topic, serialData);
}
