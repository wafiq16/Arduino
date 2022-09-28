#include <WiFi.h>
#include <PubSubClient.h>
//#include <HTTPClient.h>
#include <ArduinoJson.h>

// Update these with values suitable for your network.
char* ssid = "hehehe";
char* password = "12345679";
char* mqtt_server = "l40840f6.en.emqx.cloud";//"m16.cloudmqtt.com";
#define mqtt_port 12245
#define MQTT_USER "wafiq"
#define MQTT_PASSWORD "12345678"
#define YAKINJAYATOPICDEMO1 "/yakinjaya/logger1"
#define USE_SERIAL Serial

//StaticJsonDocument<200> doc;
//char json[63];

WiFiClient wifiClient;

PubSubClient client(wifiClient);

void setup_wifi() {
    delay(10);
    // We start by connecting to a WiFi network
    Serial.println();
    Serial.print("Connecting to ");
    Serial.println(ssid);
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) {
      delay(500);
      Serial.print(".");
    }
//    randomSeed(micros());
    Serial.println("");
    Serial.println("WiFi connected");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());
}

void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Create a random client ID
    String clientId = "ESP32Client-";
    clientId += String(random(0xffff), HEX);
    // Attempt to connect
    if (client.connect(clientId.c_str(),MQTT_USER,MQTT_PASSWORD)) {
      Serial.println("connected");
      //Once connected, publish an announcement...
//      client.publish(YAKINJAYATOPICDEMO1, "ini demo 1");
//      client.publish(YAKINJAYATOPICDEMO2, "Ini demo 2");
      // ... and resubscribe
      client.subscribe(YAKINJAYATOPICDEMO1);
//      client.subscribe(YAKINJAYATOPICDEMO2);
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(100);
    }
  }
}

void callback(char* topic, byte *payload, unsigned int length) {
    Serial.println("-------new message from broker-----");
    Serial.print("channel:");
    Serial.println(topic);
    Serial.print("data:");  
    Serial.write(payload, length);
    Serial.println();
}

void setup() {
  Serial.begin(115200);
  Serial.setTimeout(500);// Set time out for 
  setup_wifi();
//  client.setServer(mqtt_server, mqtt_port);
//  client.setCallback(callback);
  reconnect();
}

void publishSerialData(char *serialData, char* topic){
  if (!client.connected()) {
    reconnect();
//    Serial.println(" dc maneh\n");
  }
  client.publish(topic, serialData);
}
void loop() {
  StaticJsonBuffer<300> JSONbuffer;
  JsonObject& JSONencoder = JSONbuffer.createObject();
 
  JSONencoder["device"] = "32";
  JSONencoder["sensorType"] = "56";
//  JsonArray& values = JSONencoder.createNestedArray("values");
 
//  values.add(20);
//  values.add(21);
//  values.add(23);
 
  char JSONmessageBuffer[100];
  JSONencoder.printTo(JSONmessageBuffer, sizeof(JSONmessageBuffer));
  Serial.println("Sending message to MQTT topic..");
  Serial.println(JSONmessageBuffer);
  publishSerialData(JSONmessageBuffer, YAKINJAYATOPICDEMO1);
//  if (client.publish("esp/test", JSONmessageBuffer) == true) {
//    Serial.println("Success sending message");
//  } else {
//    Serial.println("Error sending message");
//  }
//   if (Serial.available() > 0) {
     char *mun = "10";
//    String mun;
//     memset(mun,0, 501);
//     Serial.readBytesUntil( '\n',mun,500);
     mun = "10";
//     char *saya = "2";
//     client.publish(YAKINJAYATOPICDEMO2, serialData);
     
//     publishSerialData(saya, YAKINJAYATOPICDEMO2);
//     delay(1000);
//   }
  client.loop();
 }
