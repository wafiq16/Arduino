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
#define SUBTOPICDEMO1 "/colour/setter"
#define USE_SERIAL Serial

const char* mqtt_server = "broker.hivemq.com";

char pub_str[100];

WiFiClient espClient;
PubSubClient client(espClient);

int Telegram_Delay = 100;
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

char *message = "";

void callback(char* topic, byte *payload, unsigned int length) {
  StaticJsonDocument<200> doc;

  DeserializationError error = deserializeJson(doc, (char*)payload);
  int a = doc["L"];
  int b = doc["M"];
  int c = doc["N"];
  int d = doc["O"];
  int e = doc["P"];
  int digit_a = strlen(String((int)a).c_str());
  int digit_b = strlen(String((int)b).c_str());
  int digit_c = strlen(String((int)c).c_str());
  int digit_d = strlen(String((int)d).c_str());
  int digit_e = strlen(String((int)e).c_str());
  Serial.print("A");
  Serial.print("L");
  Serial.print(digit_a);
  Serial.print(a);
  Serial.print("M");
  Serial.print(digit_b);
  Serial.print(b);
  Serial.print("N");
  Serial.print(digit_c);
  Serial.print(c);
  Serial.print("O");
  Serial.print(digit_d);
  Serial.print(d);
  Serial.print("P");
  Serial.print(digit_e);
  Serial.print(e);
  Serial.print("B");

  Serial.print("A");
  Serial.print("L");
  Serial.print(digit_a);
  Serial.print(a);
  Serial.print("M");
  Serial.print(digit_b);
  Serial.print(b);
  Serial.print("N");
  Serial.print(digit_c);
  Serial.print(c);
  Serial.print("O");
  Serial.print(digit_d);
  Serial.print(d);
  Serial.print("P");
  Serial.print(digit_e);
  Serial.print(e);
  Serial.print("B");
  //  AL11M11N255O10P297B
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
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  client.setServer(mqtt_server, mqtt_port);
  client.setCallback(callback);
  client.subscribe(SUBTOPICDEMO1);
  reconnect();
}

void loop() {
  // put your main code here, to run repeatedly:
  getRGB();
  if (!client.connected())
  {
    reconnect();
  }
  client.loop();
  client.subscribe(SUBTOPICDEMO1);

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

  if (millis() - Time_Temp > Telegram_Delay) {
    publishSerialData(myBuffer, PUBTOPICDEMO1);
    Time_Temp = millis();
  }

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
      //      Serial.println(strRTerima);
      //      Serial.println(strGTerima);
      //      Serial.println(strBTerima);
    }
  }
}

//  data format
//AR3152G254B256S
