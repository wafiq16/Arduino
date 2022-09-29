#include <Arduino.h>
//#include <WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WiFi.h>
//#include <WiFiClientSecure.h>
#include <PubSubClient.h>
#include <string.h>
#include <ArduinoJson.h>

char ssidku[] = "hehehe";     // diisi nama wifi
char password[] = "12345679"; // diisi password wifi

#define mqtt_port 1883
#define MQTT_USER "Techiotpartner"
#define MQTT_PASSWORD "12345678"
#define PUBTOPICDEMO1 "/alcoholMonitor"
#define SUBTOPICDEMO1 "/alcoholControl"
#define USE_SERIAL Serial

const char* mqtt_server = "broker.hivemq.com";

char pub_str[100];

WiFiClient espClient;
PubSubClient client(espClient);

int Time_Temp;
bool haram_state = 0;
bool captureSerialRx = false;
bool completeSerialRx = false;

String status_string = "";
String bufferRx;
String halal = haram_state ? "haram bang" : "halal bang";
//String strMQTerima;
//String strTGSTerima;
//String strA1Terima;
//String strB1Terima;
//String strC1Terima;
//String strHalalTerima;
String strHalal = "";

String strMQTerima = "10";
String strTGSTerima = "11";
String strA1Terima = "";
String strB1Terima = "";
String strC1Terima = "";
String strA2Terima = "";
String strB2Terima = "";
String strC2Terima = "";
String strHalal1Terima = "";
String strHalal2Terima = "";

String strMQ    =  "10";
String strTGS   =  "11";
String strA1     = "1";
String strB1     = "0";
String strC1     = "0";
String strHalal1 = "1";
String strA2     = "0";
String strB2     = "0";
String strC2     = "1";
String strHalal2 = "0";

void setup()
{
  // Debug console
  Serial.begin(9600);
  WiFi.begin(ssidku, password);
  client.setServer(mqtt_server, mqtt_port);
  //  client.setCallback(callback);
  reconnect();
}

void loop()
{
  //  Serial.println(strHalalTerima.toInt());
  getSerialData();
  DynamicJsonDocument root(1024);


  root["MQ3"] = strMQ;
  root["TGS"] = strTGS;
  root["GolA1"] = strA1;
  root["GolB1"] = strB1;
  root["GolC1"] = strC1;
  root["status1"] = strHalal1;
  root["GolA2"] = strA2;
  root["GolB2"] = strB2;
  root["GolC2"] = strC2;
  root["status2"] = strHalal2;

  char myBuffer[1023];
  serializeJson(root, myBuffer);

  if (!client.connected())
  {
    Serial.println("recon");
    reconnect();
  }

  if (millis() - Time_Temp > 1000) {
    publishSerialData(myBuffer, PUBTOPICDEMO1);
    Time_Temp = millis();
    Serial.println("kirim");
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

void getSerialData() {
  if (Serial.available()) {
    char rxChar = Serial.read();

    if (rxChar == 'R' && !captureSerialRx) captureSerialRx = true;
    else if (rxChar == 'S' && captureSerialRx) {
      captureSerialRx = false;
      completeSerialRx = true;
      strMQTerima    = "";
      strTGSTerima   = "";
      strA1Terima     = "";
      strB1Terima     = "";
      strC1Terima     = "";
      strHalal1Terima = "";
      strA2Terima     = "";
      strB2Terima     = "";
      strC2Terima     = "";
      strHalal2Terima = "";
    }

    if (captureSerialRx) {
      bufferRx += rxChar;
    }

    if (completeSerialRx) {
      for (int i = 0; i < strlen(bufferRx.c_str()); i++) {
        if (bufferRx.charAt(i) == 'M') {
          int digit = bufferRx.charAt(i + 1) - 48;
          for (int j = 2; j <= digit + 1; j++) {
            strMQTerima += bufferRx.charAt(i + j);
          }
        }
        if (bufferRx.charAt(i) == 'T') {
          int digit = bufferRx.charAt(i + 1) - 48;
          for (int j = 2; j <= digit + 1; j++) {
            strTGSTerima += bufferRx.charAt(i + j);
          }
        }
        if (bufferRx.charAt(i) == 'A') {
          int digit = bufferRx.charAt(i + 1) - 48;
          for (int j = 2; j <= digit + 1; j++) {
            strA1Terima += bufferRx.charAt(i + j);
          }
        }
        if (bufferRx.charAt(i) == 'B') {
          int digit = bufferRx.charAt(i + 1) - 48;
          for (int j = 2; j <= digit + 1; j++) {
            strB1Terima += bufferRx.charAt(i + j);
          }
        }
        if (bufferRx.charAt(i) == 'C') {
          int digit = bufferRx.charAt(i + 1) - 48;
          for (int j = 2; j <= digit + 1; j++) {
            strC1Terima += bufferRx.charAt(i + j);
          }
        }
        if (bufferRx.charAt(i) == 'H') {
          int digit = bufferRx.charAt(i + 1) - 48;
          for (int j = 2; j <= digit + 1; j++) {
            strHalal1Terima += bufferRx.charAt(i + j);
          }
        }
        if (bufferRx.charAt(i) == 'D') {
          int digit = bufferRx.charAt(i + 1) - 48;
          for (int j = 2; j <= digit + 1; j++) {
            strA2Terima += bufferRx.charAt(i + j);
          }
        }
        if (bufferRx.charAt(i) == 'E') {
          int digit = bufferRx.charAt(i + 1) - 48;
          for (int j = 2; j <= digit + 1; j++) {
            strB2Terima += bufferRx.charAt(i + j);
          }
        }
        if (bufferRx.charAt(i) == 'F') {
          int digit = bufferRx.charAt(i + 1) - 48;
          for (int j = 2; j <= digit + 1; j++) {
            strC2Terima += bufferRx.charAt(i + j);
          }
        }
        if (bufferRx.charAt(i) == 'I') {
          int digit = bufferRx.charAt(i + 1) - 48;
          for (int j = 2; j <= digit + 1; j++) {
            strHalal2Terima += bufferRx.charAt(i + j);
          }
        }
      }

      bufferRx = "";
      completeSerialRx = false;
      strMQ    = strMQTerima;
      strTGS   = strTGSTerima;
      strA1     = strA1Terima;
      strB1     = strB1Terima;
      strC1     = strC1Terima;
      strHalal1 = strHalal1Terima;
      strA2     = strA2Terima;
      strB2     = strB2Terima;
      strC2     = strC2Terima;
      strHalal2 = strHalal2Terima;
    }
  }
}
// susunan data pengiriman
//RM229.49T215.16A10B10C11H10D10E11F10I10S
//RM220T240A10B3255C10H11S
//RM2-7T3-45A3255B10C10H10SRM2-3T3-35A3255B10C10H10SRM10T3-26A3255B10C10H10SRM14T3-16A3255B10C10H10SRM18T2-6A10B3255C10H10SRM212T12A10B3255C10H10SRM216T212A10B3255C10H10SRM220T221A10B10C3255H10SRM224T231A10B10C3255H10SRM228T240A10B10C3255H10SRM228T240A10B10C3255H10SRM228T240A10B10C3255H10SRM227T239A10B10C3255H10SRM227T239A10B10C3255H10SRM227T239A10B10C3255H10SRM227T239A10B10C3255H10SRM227T238A10B10C3255H10SRM227T238A10B10C3255H10SRM227T238A10B10C3255H10SRM226T238A10B10C3255H10SRM226T238A10B10C3255H10SRM226T238A10B10C3255H10SRM226T237A10B10C3255H10SRM226T237A10B10C3255H10SRM226T237A10B10C3255H10SRM226T237A10B10C3255H10SRM225T237A10B10C3255H10SRM225T237A10B10C3255H10SRM225T237A10B10C3255H10SRM225T237A10B10C3255H10SRM225T236A10B10C3255H10SRM225T236A10B10C3255H10SRM225T236A10B10C3255H10SRM225T236A10B10C3255H10SRM224T236A10B10C3255H10SRM224T236A10B10C3255H10SRM224T236A10B10C3255H10SRM224T235A10B10C3255H10SRM224T235A10B10C3255H10SRM224T235A10B10C3255H10SRM224T235A10B10C3255H10SRM224T235A10B10C3255H10SRM224T235A10B10C3255H10SRM224T235A10B10C3255H10SRM224T235A10B10C3255H10SRM224T234A10B10C3255H10SRM224T234A10B10C3255H10SRM223T234A10B10C3255H10SRM223T234A10B10C3255H10SRM223T234A10B10C3255H10SRM223T234A10B10C3255H10SRM223T234A10B10C3255H10SRM223T234A10B10C3255H10SRM223T234A10B10C3255H10SRM223T234A10B10C3255H10SRM223T233A10B10C3255H10SRM223T233A10B10C3255H10SRM223T233A10B10C3255H10SRM223T233A10B10C3255H10SRM223T233A10B10C3255H10SRM223T233A10B10C3255H10SRM223T233A10B10C3255H10SRM223T233A10B10C3255H10SRM223T233A10B10C3255H10SRM223T233A10B10C3255H10SRM223T233A10B10C3255H10SRM223T233A10B10C3255H10SRM223T233A10B10C3255H10SRM223T233A10B10C3255H10SRM223T233A10B10C3255H10SRM223T232A10B10C3255H10SRM223T232A10B10C3255H10SRM223T232A10B10C3255H10SRM223T232A10B10C3255H10SRM223T232A10B10C3255H10S
