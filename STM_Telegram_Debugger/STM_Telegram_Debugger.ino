#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>
#include <PubSubClient.h>
#include <string.h>
#include <ArduinoJson.h>

char ssidku[] = "hehehe";     // diisi nama wifi
char password[] = "12345679"; // diisi password wifi

#define mqtt_port 1883 // Port TCP
#define MQTT_USER "Techiotpartner" //
#define MQTT_PASSWORD "12345678"
#define PUBTOPICDEMO1 "/d/M"
#define SUBTOPICDEMO1 "/d/C/POC"
#define SUBTOPICDEMO2 "/d/C/Sir"
#define SUBTOPICDEMO3 "/d/C/Flo"
#define SUBTOPICDEMO3 "/d/C/Moi"

const char* mqtt_server = "broker.hivemq.com";

char pub_str[100];

WiFiClient espClient;
PubSubClient client(espClient);

int Time_Temp;
bool captureSerialRx = false;
bool completeSerialRx = false;

String status_string = "";
String bufferRx;

String strSirTerima = "";
String strPOCTerima = "";
String strFloTerima = "";
String strMoiTerima = "";

bool kirim = false;

String myBuffer = "";

void setup()
{
  // Debug console
  Serial.begin(115200);
  WiFi.begin(ssidku, password);
  client.setServer(mqtt_server, mqtt_port);
  reconnect();
}

void loop()
{
  getSerialData();

  myBuffer = "\nSir = " + strSirTerima  + "\n" + "POC = " + strPOCTerima + "\n" + "Flow = " + strFloTerima + "\n" + "Moi = " + strMoiTerima + "\n";
  char *dataKirim  = &*myBuffer.begin();

  if (!client.connected())
  {
    reconnect();
  }

  if (kirim) {
    publishSerialData(dataKirim, PUBTOPICDEMO1);
  }
  //  if (millis() - Time_Temp > 1000) {

  //    Time_Temp = millis();
  //  }
  //  client.subscribe(SUBTOPICDEMO1);
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

    if (rxChar == 'A' && !captureSerialRx) captureSerialRx = true;
    else if (rxChar == 'B' && captureSerialRx) {
      captureSerialRx = false;
      completeSerialRx = true;

      strSirTerima = "";
      strPOCTerima = "";
      strFloTerima = "";
      strMoiTerima = "";
    }

    if (captureSerialRx) {
      bufferRx += rxChar;
    }

    if (completeSerialRx) {
      for (int i = 0; i < strlen(bufferRx.c_str()); i++) {
        if (bufferRx.charAt(i) == 'S') {
          int digit = bufferRx.charAt(i + 1) - 48;
          for (int j = 2; j <= digit + 1; j++) {
            strSirTerima += bufferRx.charAt(i + j);
          }
        }
        if (bufferRx.charAt(i) == 'P') {
          int digit = bufferRx.charAt(i + 1) - 48;
          for (int j = 2; j <= digit + 1; j++) {
            strPOCTerima += bufferRx.charAt(i + j);
          }
        }
        if (bufferRx.charAt(i) == 'F') {
          int digit = bufferRx.charAt(i + 1) - 48;
          for (int j = 2; j <= digit + 1; j++) {
            strFloTerima += bufferRx.charAt(i + j);
          }
        }
        if (bufferRx.charAt(i) == 'M') {
          int digit = bufferRx.charAt(i + 1) - 48;
          for (int j = 2; j <= digit + 1; j++) {
            strMoiTerima += bufferRx.charAt(i + j);
          }
        }
      }
      bufferRx = "";
      completeSerialRx = false;

      Serial.println(strSuhuTerima);
      Serial.println(strKelembapanTerima);
      Serial.println(strKeringTerima);
    }
  }
}

void kirim_pesan() {
  Serial.printf("B%dS", arusKirim);
  delay(4000);
  Serial.printf("B%dS", 0);
}

// susunan data pengiriman
//AT220H240D10B
//AT527.40H568.90D10B
