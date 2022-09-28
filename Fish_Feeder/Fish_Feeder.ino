#include <Servo.h>
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>
#include <PubSubClient.h>
#include <DS3231.h>
#include <string.h>
// Set the LCD address to 0x27 for a 16 chars and 2 line display
LiquidCrystal_I2C lcd(0x27, 16, 2);

char ssid[] = "hehehe";     // diisi nama wifi
char password[] = "12345670"; // diisi password wifi // REPLACE myPassword YOUR WIFI PASSWORD, IF ANY

#define mqtt_port 1883
#define MQTT_USER "wafiqkamal16"
#define MQTT_PASSWORD "12345670"
#define SUBDATA "/Sub"
#define PUBDATA "/Pub"
#define USE_SERIAL Serial


int jadwal_jam = 13;
int jadwal_menit = 33;
int jadwal_detik = 30;



const char* mqtt_server = "broker.hivemq.com"; //"m16.cloudmqtt.com";

char *pub_str;
int perintah;
WiFiClient espClient;
PubSubClient client(espClient);
DS3231 myclock;
RTCDateTime dt;
Servo myservo;     // variable untuk menyimpan posisi data
int pos = 00;

void callback(char* topic, byte *payload, unsigned int length) {
    perintah = *payload; 
    Serial.println(perintah);
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
      client.subscribe(SUBDATA);
    } else {
       Serial.print("failed, rc=");
       Serial.print(client.state());
       Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(100);
    }
  }
}

void publishSerialData(char *serialData, char* topic){
  if (!client.connected()) {
    reconnect();
    Serial.println(" dc maneh\n");
  }
  client.publish(topic, serialData);
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Wire.begin();
  WiFi.begin(ssid, password);
  client.setServer(mqtt_server, mqtt_port);
  client.setCallback(callback);
  reconnect();

  myservo.attach(14); //sinyal data kabel motor servo dikonekan di pin 3 Arduino
  //d5 nodemcu = pin 14 arduino
  lcd.begin();
 
  // Nyalakan backlight
  lcd.backlight();
 
  // Pindahkan kursor ke kolom 0 dan baris 0
  // (baris 1)

  // Set sketch compiling time
  Serial.println("Initialize DS3231");
  myclock.begin();
//  myclock.setDateTime(__DATE__, __TIME__);
  lcd.begin();

  // Turn on the blacklight and print a message.
  lcd.backlight();
  lcd.setCursor(4, 0);
  lcd.print("FISH FEEDER");
  lcd.setCursor(6, 1);
  lcd.print("PROTOTYPE");
  delay(2000);
  lcd.clear();
}

void loop() {
  // put your main code here, to run repeatedly:
//  lcd.setCursor(0, 1);
//  lcd.print("Hello, world!");
  if(!client.connected())
  {
    reconnect();
     Serial.print("disconnected");
  }
   if (perintah == '3') {              // if the received message is "LIGHT ON"...
      char* Start_String = "Menampilkan penjadwalan pakan";
      char buff[10];
      sprintf(buff, "%s\n%d:%d:%d", Start_String,jadwal_jam,jadwal_menit,jadwal_detik);
      client.publish(PUBDATA, buff);  // notify the sender
    }
    else if(perintah == '2'){
      char* Start_String = "Menampilkan waktu sistem";
      char buff[10];
      sprintf(buff, "%s\n%d:%d:%d", Start_String,dt.hour,dt.minute,dt.second);
      client.publish(PUBDATA, buff);  // notify the sender
    }
    else if (perintah == '1') {        // if the received message is "LIGHT OFF"...
     for(pos = 00; pos < 180; pos += 2)  //fungsi perulangan yang akan dijadikan PWM dengan kenaikan 1
      {
        myservo.write(pos); //prosedur penulisan data PWM ke motor servo
        delay(15); //waktu tunda 15 ms                 
      } 
      delay(500);
      char* Start_String = "selesai beri makan";
      char buff[10];
      sprintf(buff, "%s\n%d:%d:%d", Start_String,dt.hour,dt.minute,dt.second);
      client.publish(PUBDATA, buff);;
    }
    else if(perintah == '0'){
      char* Start_String = "\nWelcome to fishfeeder prototipe \n1 : beri makan\n2 : Tampilkan waktu sistem\n3 : Tampilkan Jadwal\n";
      pub_str = Start_String;
     client.publish(PUBDATA, Start_String);
    }
    perintah = '5';
  client.subscribe(SUBDATA);
  client.loop();

  dt = myclock.getDateTime();

  lcd.setCursor(4, 1);
  lcd.print(jadwal_jam);   lcd.print(":");
  lcd.print(jadwal_menit); lcd.print(":");
  lcd.print(jadwal_detik); lcd.println("");
  lcd.setCursor(4, 0);
  Serial.print(dt.year);   Serial.print("-");
  Serial.print(dt.month);  Serial.print("-");
  Serial.print(dt.day);    Serial.print(" ");
  Serial.print(dt.hour);   Serial.print(":");
  Serial.print(dt.minute); Serial.print(":");
  Serial.print(dt.second); Serial.println("");
  lcd.print(dt.hour);   lcd.print(":");
  lcd.print(dt.minute); lcd.print(":");
  lcd.print(dt.second); lcd.println("");
  
  if(dt.hour == jadwal_jam && dt.minute == jadwal_menit && dt.second == jadwal_detik){
    Serial.println("alarm nyala");
    for(pos = 00; pos < 180; pos += 2)  //fungsi perulangan yang akan dijadikan PWM dengan kenaikan 1
      {
        myservo.write(pos); //prosedur penulisan data PWM ke motor servo
        delay(15); //waktu tunda 15 ms                 
      } 
      delay(500);                          // turn off the led (inverted logic!)
      char* Start_String = "selesai beri makan";
      char buff[10];
      sprintf(buff, "%s\n%d:%d:%d", Start_String,dt.hour,dt.minute,dt.second);
      client.publish(PUBDATA, buff);
  }
  
  delay(1000);
  lcd.clear();
}
