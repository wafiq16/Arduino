#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>
#include <PubSubClient.h>
#include <string.h>
#include <ArduinoJson.h>

char ssidku[] = "hehehe";     // diisi nama wifi
char password[] = "12345679"; // diisi password wifi

#define mqtt_port 1883
#define MQTT_USER "Techiotpartner"
#define MQTT_PASSWORD "12345678"
#define PUBTOPICDEMO1 "/farmMonitor"
#define SUBTOPICDEMO1 "/farmControl"
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

char *message = "";

double a = 22.5;
double b = 87.3;
double c = 0;
double d = 24.2;
double e = 83.1;
double f = 0;
double g = 1;

void callback(char* topic, byte *payload, unsigned int length) {
  StaticJsonDocument<200> doc;

  DeserializationError error = deserializeJson(doc, (char*)payload);
  //  a = doc["suhu1"];
  //  b = doc["Kelembapan1"];
  c = doc["relay1"];
  //  d = doc["suhu2"];
  //  e = doc["Kelembapan2"];
  f = doc["relay2"];
  g = doc["relay3"];
  //  int digit_a = strlen(String((int)a).c_str());
  //  int digit_b = strlen(String((int)b).c_str());
  //  int digit_c = strlen(String((int)c).c_str());
  //  int digit_d = strlen(String((int)d).c_str());
  //  int digit_e = strlen(String((int)e).c_str());
  //  int digit_f = strlen(String((int)f).c_str());
  //  int digit_g = strlen(String((int)g).c_str());
  Serial.println(c);
  Serial.println(f);
  Serial.println(g);
  //  Serial.print("A");
  //  Serial.print("L");
  //  Serial.print(digit_a);
  //  Serial.print(a);
  //  Serial.print("M");
  //  Serial.print(digit_b);
  //  Serial.print(b);
  //  Serial.print("N");
  //  Serial.print(digit_c);
  //  Serial.print(c);
  //  Serial.print("O");
  //  Serial.print(digit_d);
  //  Serial.print(d);
  //  Serial.print("P");
  //  Serial.print(digit_e);
  //  Serial.print(e);
  //  Serial.print("B");
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
  Serial.begin(9600);
  WiFi.begin(ssid, password);
  client.setServer(mqtt_server, mqtt_port);
  client.setCallback(callback);
  reconnect();
}

void loop() {
  // put your main code here, to run repeatedly:
//  getRGB();

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

//  root["R"] = strRTerima;
//  root["G"] = strGTerima;
//  root["B"] = strBTerima;
  root["suhu1"] = a;
  root["kelembapan1"] = b;
  root["pompa1"] = c;
  root["suhu2"] = d;
  root["kelembapan2"] = e;
  root["pompa2"] = f;
  root["pompa3"] = g;
  char myBuffer[1023];
  serializeJson(root, myBuffer);

  if (!client.connected())
  {
    reconnect();
  }
//  Serial.println(myBuffer);
  if (millis() - Time_Temp > Telegram_Delay) {
    publishSerialData(myBuffer, PUBTOPICDEMO1);
    Time_Temp = millis();
  }
  client.subscribe(SUBTOPICDEMO1);
  client.loop();
}

//  data format
//AR3152G254B256S
