//#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>
#include <UniversalTelegramBot.h>
//#include <Ultrasonic.h>
#include "CTBot.h"

char ssidku[] = "hehehe";     // diisi nama wifi
char password[] = "12345679"; // diisi password wifi

#define BOTtoken "1822114692:AAG8Em27qnqFQWu2EhvkibpzHnLNcAr2xvg"

WiFiClientSecure client;

int Pin_Led = D3;
//Ultrasonic ultrasonic1(D5, D6);  // An ultrasonic sensor HC-04
int Distance = 0;
char jarak[30];

CTBot myBot;

String ssid = ssidku;     // REPLACE mySSID WITH YOUR WIFI SSID
String pass = password; // REPLACE myPassword YOUR WIFI PASSWORD, IF ANY
String token = BOTtoken;   // REPLACE myToken WITH YOUR TELEGRAM BOT TOKEN
uint8_t led = Pin_Led;            // the onboard ESP8266 LED.    
                            // If you have a NodeMCU you can use the BUILTIN_LED pin
                            // (replace 2 with BUILTIN_LED)             

void setup() {
  // initialize the Serial
  Serial.begin(9600);
  Serial.println("Starting TelegramBot...");

  // connect the ESP8266 to the desired access point
  myBot.wifiConnect(ssid, pass);

  // set the telegram bot token
  myBot.setTelegramToken(token);

  // check if all things are ok
  if (myBot.testConnection())
    Serial.println("\ntestConnection OK");
  else
    Serial.println("\ntestConnection NOK");

  // set the pin connected to the LED to act as output pin
  pinMode(led, OUTPUT);
  digitalWrite(led, HIGH); // turn off the led (inverted logic!)

}

void loop() {
  // a variable to store telegram message data
  TBMessage msg;
      // sekarang = millis();
  // if there is an incoming message...
    int sekarang = millis();
  if (myBot.getNewMessage(msg)) {
    Serial.println(millis() - sekarang);
    sekarang = millis();
    Serial.println("got response");

    if (msg.text.equalsIgnoreCase("/LEDON")) {              // if the received message is "LIGHT ON"...
      digitalWrite(led, HIGH);                               // turn on the LED (inverted logic!)
      myBot.sendMessage(msg.sender.id, "Light is now ON");  // notify the sender
    }
    else if (msg.text.equalsIgnoreCase("/LEDOFF")) {        // if the received message is "LIGHT OFF"...
      digitalWrite(led, LOW);                              // turn off the led (inverted logic!)
      myBot.sendMessage(msg.sender.id, "Light is now OFF"); // notify the sender
    }
    else if(msg.text.equalsIgnoreCase("/CEKJARAK")){
      String temp = "Jarak saat ini : ";
//      Distance = ultrasonic1.read();
      temp += Distance;
      myBot.sendMessage(msg.sender.id, temp);
    }
    else {                                                    // otherwise...
      String welcome = "Welcome  " + msg.sender.username + ".\n";
      welcome += "/CEKJARAK : Cek Jarak Benda\n";
      welcome += "/LEDON : Nyalakan lampu\n";
      welcome += "/LEDOFF : Matikan lampu\n";
      myBot.sendMessage(msg.sender.id, welcome);
    }
      Serial.println(millis() - sekarang);
  }
}
