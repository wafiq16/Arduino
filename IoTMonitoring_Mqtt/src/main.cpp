#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>
#include <PubSubClient.h>
#include <string.h>

char ssidku[] = "hehehe";     // diisi nama wifi
char password[] = "12345679"; // diisi password wifi

#define mqtt_port 1883
#define MQTT_USER "wafiqkamal16"
#define MQTT_PASSWORD "12345670"
#define WAFIQTOPICDEMO1 "/Pub_Data"
#define BROKERTOPIC1 "/Sub_Data"
#define USE_SERIAL Serial

const char* mqtt_server = "broker.hivemq.com"; //"m16.cloudmqtt.com";

char pub_str[100];

WiFiClient espClient;
PubSubClient client(espClient);
int Telegram_Delay = 2000;
int Time_Temp = 0;

int Pin_Led = D3;
int i = 0;
// send data serial
double temp = 0; //variable konversi 10 bit ke 8 bit
unsigned char tegangan = 0;
unsigned char arus = 0;
unsigned char daya = 0;
// unsigned char daya = 0;
unsigned char status = 0;
// char *buffer;
String status_string = ""; 
int sendTime = 0;
void kirim_pesan(char* data);
// read data serial
char buffer[20];
char daya_total[5];
unsigned char data = 0;
unsigned char kunci = 0;
unsigned char checksum = 0;
void baca_pesan();


String ssid = ssidku;     // REPLACE mySSID WITH YOUR WIFI SSID
String pass = password; // REPLACE myPassword YOUR WIFI PASSWORD, IF ANY
uint8_t led = Pin_Led; 


void callback(char* topic, byte *payload, unsigned int length) {
    // Serial.println("-------new message from broker-----");
    // Serial.print("channel:");
    // Serial.println(topic);
    // if(topic == BROKERTOPIC1){
    arus = *payload;
    char buffSubData[5];
    sprintf(buffSubData, "%c",arus);
    kirim_pesan(buffSubData);
      // Serial.print("get status data");
    // }
    // Serial.print("data:");  
    // Serial.write(payload, length);
    // Serial.println();
}

void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    // Serial.print("Attempting MQTT connection...");
    // Create a random client ID
    String clientId = "ESP32Client-";
    clientId += String(random(0xffff), HEX);
    // Attempt to connect
    if (client.connect(clientId.c_str(),MQTT_USER,MQTT_PASSWORD)) {
      // Serial.println("connected");
      //Once connected, publish an announcement...
      client.subscribe(BROKERTOPIC1);
    } else {
      // Serial.print("failed, rc=");
      // Serial.print(client.state());
      // Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(100);
    }
  }
}

void publishSerialData(char *serialData, char* topic){
  if (!client.connected()) {
    reconnect();
//    Serial.println(" dc maneh\n");
  }
  client.publish(topic, serialData);
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
	// Serial.println("Starting TelegramBot...");
  WiFi.begin(ssid, password);
  pinMode(led, OUTPUT);
	digitalWrite(led, HIGH);
  client.setServer(mqtt_server, mqtt_port);
  client.setCallback(callback);
  reconnect(); // turn off the led (inverted logic!)
  // arus = '4';
  // tegangan = '9';
  // status = '0';
}

void loop() {
  // put your main code here, to run repeatedly:
  baca_pesan();
  // sprintf(buffer,"%d%d%d%d%d",arus,daya_1,daya_2,daya_3,status);
  if(buffer[4] == '0'){
    status_string = "Safe";
  }
  else{
    status_string = "Thread";
  }
  if(!client.connected())
  {
    reconnect();
    // Serial.print("disconnected");
  }
  sprintf(pub_str,"\narus = %c \ndaya = %c%c%c \nstatus = %s \n", buffer[0], buffer[1],buffer[2],buffer[3], status_string);
  // Serial.print(pub_str);
  
  if(millis() - Time_Temp > Telegram_Delay){
    publishSerialData(pub_str, WAFIQTOPICDEMO1);
    Time_Temp = millis();
  }
  client.subscribe(BROKERTOPIC1);
  client.loop();
}

void kirim_pesan(char* data){
  if((millis() - sendTime > 50 || sendTime == 0))  // pembacaan apakah terjadi komunikasi serial antara matlab dengan arduino
  {  
    sendTime = millis();
    Serial.print('B');
    Serial.print(data);
    // if(i == 1){
      // Serial.print('A');
      // temp = 'A';
    // }
    // else if(i == 3){
      // Serial.print('B');
      // temp += 'B';
    // }
    // else if(i == 5){
      // Serial.print(arus);// mengirim data ke matlab
      // temp += arus;
    // }
    // else if(i==7)
    // {
      // Serial.print(daya);// mengirim data ke matlab
      // temp += daya;
    // }
    // else if(i == 9){
      // Serial.print(status);// mengirim data ke matlab
      // temp += status;
    // }

    // else if(i == 11){
      // Serial.print(temp);// mengirim data ke matlab
    // }

    // i++;
    // if(i>9)
      // i = 1;
  }
}

void baca_pesan(){
  // Serial.readBytesUntil('\n',buffer,7);
  if(Serial.available() > 0){
    if(Serial.read() == 'A'){
      for(int i=0;i<5;i++){
        buffer[i]    = Serial.read();
      }
    }
  }
  // arus = buffer[0];
  // daya = buffer[1] + buffer[2] + buffer [3];
  // status = buffer[4];
}