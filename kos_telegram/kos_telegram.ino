#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>
#include <PubSubClient.h>
#include <string.h>
#include <ArduinoJson.h>

char ssidku[] = "hehehe";     // diisi nama wifi
char password[] = "12345679"; // diisi password wifi

#define mqtt_port 1883 // Port TCP
#define MQTT_USER "KOS99" //
#define MQTT_PASSWORD "12345678"
#define PUBTOPICDEMO1 "/kosMonitor"
#define SUBTOPICDEMO1 "/kosControlPulsa"
#define SUBTOPICDEMO2 "/kosControlON"
#define SUBTOPICDEMO3 "/kosControlOFF"

const char* mqtt_server = "broker.hivemq.com";

char pub_str[100];

WiFiClient espClient;
PubSubClient client(espClient);

int Time_Temp;
bool captureSerialRx = false;
bool completeSerialRx = false;

String status_string = "";
String bufferRx;

String strArusTerima = "";
String strTeganganTerima = "";
String strDayaTerima = "";
String strEnergiTerima = "";
String strSisaKWHTerima = "";

bool kirim = false;

//String strArus = "";
//String strTegangan = "";
//String strDaya = "";
//String strEnergi = "";
//String strSisaKWH = "";

String myBuffer = "";

void setup()
{
  // Debug console
  Serial.begin(9600);
  WiFi.begin(ssidku, password);
  client.setServer(mqtt_server, mqtt_port);
  reconnect();
}

void loop()
{
  getSerialData();

  myBuffer = "\nArus = " + strArusTerima + "A" + "\n" + "Tegangan = " + strTeganganTerima + "V" + "\n" + "Daya = " + strDayaTerima + "W" + "\n" + "Energi = " + strEnergiTerima + "J" + "\n" + "Sisa KWH = " + strSisaKWH + "KWH" + "\n";
  char *dataKirim  = &*myBuffer.begin();

  if (!client.connected())
  {
    reconnect();
  }

  if (kirim) {
    publishSerialData(dataKirim, PUBTOPICDEMO1);
    kirim = false;
  }

  client.loop();
}

void reconnect() {
  while (!client.connected()) {
    String clientId = "device1";
    if (client.connect(clientId.c_str(), MQTT_USER, MQTT_PASSWORD)) {
      client.subscribe(SUBTOPICDEMO1);
      client.subscribe(SUBTOPICDEMO2);
      client.subscribe(SUBTOPICDEMO3);
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

    if (rxChar == 'Y' && !captureSerialRx) captureSerialRx = true;
    else if (rxChar == 'Z' && captureSerialRx) {
      captureSerialRx = false;
      completeSerialRx = true;
      strArusTerima = "";
      strTeganganTerima = "";
      strDayaTerima = "";
      strEnergiTerima = "";
      strSisaKWHTerima = "";
    }

    if (captureSerialRx) {
      bufferRx += rxChar;
    }

    if (completeSerialRx) {
      //      for (int i = 0; i < strlen(bufferRx.c_str()); i++) {
      //        if (bufferRx.charAt(i) == 'A') {
      //          int digit = bufferRx.charAt(i + 1) - 48;
      //          for (int j = 2; j <= digit + 1; j++) {
      //            strArusTerima += bufferRx.charAt(i + j);
      //          }
      //        }
      //        if (bufferRx.charAt(i) == 'V') {
      //          int digit = bufferRx.charAt(i + 1) - 48;
      //          for (int j = 2; j <= digit + 1; j++) {
      //            strTeganganTerima += bufferRx.charAt(i + j);
      //          }
      //        }
      //        if (bufferRx.charAt(i) == 'W') {
      //          int digit = bufferRx.charAt(i + 1) - 48;
      //          for (int j = 2; j <= digit + 1; j++) {
      //            strDayaTerima += bufferRx.charAt(i + j);
      //          }
      //        }
      //        if (bufferRx.charAt(i) == 'J') {
      //          int digit = bufferRx.charAt(i + 1) - 48;
      //          for (int j = 2; j <= digit + 1; j++) {
      //            strEnergiTerima += bufferRx.charAt(i + j);
      //          }
      //        }
      //        if (bufferRx.charAt(i) == 'K') {
      //          int digit = bufferRx.charAt(i + 1) - 48;
      //          for (int j = 2; j <= digit + 1; j++) {
      //            strSisaKWHTerima += bufferRx.charAt(i + j);
      //          }
      //        }
      //      }
      bufferRx = "";
      completeSerialRx = false;
    }
  }
}

void kirim_pesan(int kamar, int token, int onOff) {
  Serial.printf("B%d%d%dS", kamar, token, onOff);
  delay(4000);
  //  Serial.printf("B%dS", 0);
}

// susunan data pengiriman
// AT220H240D10B
// AT527.40H568.90D10B
// YA51.125V56.585W57.126J5100.1K5125.4Z

// ========================== STM ==========================
//if (data[1] == '1') 
//{
  sprintf(char*myBuffer, "Y\nKamar 1 = \n Arus = %0.3f \n Tegangan = %0.3f \n Z", digitA1, arus[1], digitV1, tegangan[1]);
  HAL_UART((uint_8 *) myBuffer, strlen(), 1000);
//}
//if (data[1] == '2') 
//{
  sprintf(char*myBuffer, "Y\nKamar 2 = \n Arus = %0.3f \n Tegangan = %0.3f \n Z", arus[1], digitV1);
  HAL_UART((uint_8 *) myBuffer, strlen(), 1000);
//}
