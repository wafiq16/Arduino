#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>
#include <PubSubClient.h>
#include <string.h>
#include <ArduinoJson.h>

char ssidku[] = "hehehe";     // diisi nama wifi
char password[] = "12345679"; // diisi password wifi

#define mqtt_port 1883
#define MQTT_USER "wafiq"
#define MQTT_PASSWORD "12345678"
#define PUBTOPICDEMO1 "/colour/monitor"
#define USE_SERIAL Serial

const char* mqtt_server = "broker.hivemq.com"; //"m16.cloudmqtt.com";

char pub_str[100];

WiFiClient espClient;
PubSubClient client(espClient);

int Telegram_Delay = 1000;
int Time_Temp = 0;

int Pin_Led = D3;
int i = 0;
// int sendTime = 0;
String bufferRx;
bool captureSerialRx = false;
bool completeSerialRx = false;
String strRTerima;
String strGTerima;
String strBTerima;
uint16_t arusTerima = 0;
uint16_t dayaTerima = 0;

String ssid = ssidku;     // REPLACE mySSID WITH YOUR WIFI SSID
String pass = password; // REPLACE myPassword YOUR WIFI PASSWORD, IF ANY
uint8_t led = Pin_Led;

void callback(char* topic, byte *payload, unsigned int length) {
  Serial.print(*topic);
  Serial.print(*payload);
  Serial.println();
}

void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    String clientId = "motor1";
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
    //    Serial.println(" dc maneh\n");
  }
  client.publish(topic, serialData);
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  WiFi.begin(ssid, password);
  client.setServer(mqtt_server, mqtt_port);
  client.setCallback(callback);
  reconnect(); // turn off the led (inverted logic!)
}

void loop() {
  // put your main code here, to run repeatedly:
  //  StaticJsonDocument<200> jsonBuffer;

  DynamicJsonDocument root(1024);
  
  root["tegangan_fasa_1"] = 1;
  root["tegangan_fasa_2"] = 2;
  root["tegangan_fasa_3"] = 3;
  root["arus_fasa_1"] = 1;
  root["arus_fasa_2"] = 2;
  root["arus_fasa_3"] = 3;
  root["arus_total"] = 6;
  root["tegangan_total"] = 6;
  root["daya"] = 36;
//  serializeJson(root, Serial);
  char myBuffer[1023];
  serializeJson(root, myBuffer);
  
  if (!client.connected())
  {
    reconnect();
    // Serial.print("disconnected");
  }

  if (millis() - Time_Temp > Telegram_Delay) {
    publishSerialData(myBuffer, PUBTOPICDEMO1);
    Serial.print(myBuffer);
    Time_Temp = millis();
  }
  client.subscribe(SUBTOPICDEMO1);
  client.loop();
}
