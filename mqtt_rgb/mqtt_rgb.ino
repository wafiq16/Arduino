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
#define SUBTOPICDEMO1 "/colour/control"
#define USE_SERIAL Serial

const char* mqtt_server = "broker.hivemq.com";

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

String ssid = ssidku;
String pass = password;
uint8_t led = Pin_Led;

void callback(char* topic, byte *payload, unsigned int length) {
  Serial.print(*topic);
  Serial.print(*payload);
  Serial.println();
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

void setup() {
  Serial.begin(9600);
  WiFi.begin(ssid, password);
  client.setServer(mqtt_server, mqtt_port);
  client.setCallback(callback);
  reconnect();
}

void loop() {
  // put your main code here, to run repeatedly:
  getRGB();

  DynamicJsonDocument root(1024);

//  root["tegangan_fasa_1"] = 1;
//  root["tegangan_fasa_2"] = 2;
//  root["tegangan_fasa_3"] = 3;
//  root["arus_fasa_1"] = 1;
//  root["arus_fasa_2"] = 2;
//  root["arus_fasa_3"] = 3;
//  root["arus_total"] = 6;
//  root["tegangan_total"] = 6;
//  root["daya"] = 36;

  root["R"] = strRTerima;
  root["G"] = strGTerima;
  root["B"] = strBTerima; 
  char myBuffer[1023];
  serializeJson(root, myBuffer);

  if (!client.connected())
  {
    reconnect();
  }

  if (millis() - Time_Temp > Telegram_Delay) {
    publishSerialData(myBuffer, PUBTOPICDEMO1);
    Time_Temp = millis();
  }
  client.subscribe(SUBTOPICDEMO1);
  client.loop();
}

void getRGB() {
  if (Serial.available()) {
    char rxChar = Serial.read();

    if (rxChar == 'A' && !captureSerialRx) captureSerialRx = true;
    else if (rxChar == 'S' && captureSerialRx) {
      captureSerialRx = false;
      completeSerialRx = true;
      strRTerima = "";
      strGTerima = "";
      strBTerima = "";
    }

    if (captureSerialRx) {
      bufferRx += rxChar;
    }

    if (completeSerialRx) {
      for (int i = 0; i < strlen(bufferRx.c_str()); i++) {
        if (bufferRx.charAt(i) == 'R') {
          int digit = bufferRx.charAt(i + 1) - 48;
          for (int j = 2; j <= digit + 1; j++) {
            strRTerima += bufferRx.charAt(i + j);
          }
        }
        if (bufferRx.charAt(i) == 'G') {
          int digit = bufferRx.charAt(i + 1) - 48;
          for (int j = 2; j <= digit + 1; j++) {
            strGTerima += bufferRx.charAt(i + j);
          }
        }
        if (bufferRx.charAt(i) == 'B') {
          int digit = bufferRx.charAt(i + 1) - 48;
          for (int j = 2; j <= digit + 1; j++) {
            strBTerima += bufferRx.charAt(i + j);
          }
        }
      }
      bufferRx = "";
      completeSerialRx = false;
      Serial.println(strRTerima);
      Serial.println(strGTerima);
      Serial.println(strBTerima);
    }
  }
}

//  data format
//AR3152G254B256S
