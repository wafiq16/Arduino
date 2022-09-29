
#include <ESP8266WiFi.h>
#include "secrets.h"
#include "ThingSpeak.h" // always include thingspeak header file after other header files and custom macros

#include <String.h>
bool captureSerialRx = false;
bool completeSerialRx = false;

String bufferRx;

String strArusTerima1;
String strTeganganTerima1;
String strArusTerima2;
String strTeganganTerima2;
String strArusTerima3;
String strTeganganTerima3;
String strArusTerima4;
String strTeganganTerima4;
String strArusTerima5;
String strTeganganTerima5;

String strArus1;
String strTegangan1;
String strArus2;
String strTegangan2;
String strArus3;
String strTegangan3;
String strArus4;
String strTegangan4;
String strArus5;
String strTegangan5;

//String strArusTerima1 = "1";
//String strTeganganTerima1 = "5";
//String strArusTerima2 = "2";
//String strTeganganTerima2 = "3";
//String strArusTerima3 = "3";
//String strTeganganTerima3 = "4";
//String strArusTerima4 = "1";
//String strTeganganTerima4 = "7";
//String strArusTerima5 = "1.5";
//String strTeganganTerima5 = "12";

String myStatus;

char ssid[] = "Jake Sim";   // your network SSID (name)
char pass[] = "faliajake";   // your network password
int keyIndex = 0;            // your network key Index number (needed only for WEP)
WiFiClient  client;

unsigned long myChannelNumber = 1727291;
const char * myWriteAPIKey = "O6GOQCUJYDXX76JI";

void setup() {
  delay(3000);
  Serial.begin(9600);  // Initialize serial
//  while (!Serial) {
//    ; // wait for serial port to connect. Needed for Leonardo native USB port only
//  }

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, pass);
  ThingSpeak.begin(client);  // Initialize ThingSpeak
}

void loop() {
  
  // Connect or reconnect to WiFi
//  if (WiFi.status() != WL_CONNECTED) {
//    Serial.print("Attempting to connect to SSID: ");
//    Serial.println(SECRET_SSID);
//    while (WiFi.status() != WL_CONNECTED) {
//      WiFi.begin(ssid, pass);  // Connect to WPA/WPA2 network. Change this line if using open or WEP network
//      Serial.print(".");
//      delay(1000);
//    }
//    Serial.println("\nConnected.");
//  }
  readData();

  //  delay(1000); // Wait 20 seconds to update the channel again
}

void readData() {
  if (Serial.available()) {
    char rxChar = Serial.read();

    if (rxChar == 'A' && !captureSerialRx) captureSerialRx = true;
    else if (rxChar == 'B' && captureSerialRx) {
      captureSerialRx = false;
      completeSerialRx = true;
      strArusTerima1 = "";
      strTeganganTerima1 = "";
      strArusTerima2 = "";
      strTeganganTerima2 = "";
      strArusTerima3 = "";
      strTeganganTerima3 = "";
      strArusTerima4 = "";
      strTeganganTerima4 = "";
      strArusTerima5 = "";
      strTeganganTerima5 = "";
//      Serial.println("mengenolkan");
    }

    if (captureSerialRx) {
      bufferRx += rxChar;
    }
  }

  if (completeSerialRx) {
    for (int i = 0; i < strlen(bufferRx.c_str()); i++) {
      if (bufferRx.charAt(i) == 'C') {
        int digit = bufferRx.charAt(i + 1) - 48;
        for (int j = 2; j <= digit + 1; j++) {
          strArusTerima1 += bufferRx.charAt(i + j);
        }
      }
      if (bufferRx.charAt(i) == 'D') {
        int digit = bufferRx.charAt(i + 1) - 48;
        for (int j = 2; j <= digit + 1; j++) {
          strTeganganTerima1 += bufferRx.charAt(i + j);
        }
      }
      if (bufferRx.charAt(i) == 'E') {
        int digit = bufferRx.charAt(i + 1) - 48;
        for (int j = 2; j <= digit + 1; j++) {
          strArusTerima2 += bufferRx.charAt(i + j);
        }
      }
      if (bufferRx.charAt(i) == 'F') {
        int digit = bufferRx.charAt(i + 1) - 48;
        for (int j = 2; j <= digit + 1; j++) {
          strTeganganTerima2 += bufferRx.charAt(i + j);
        }
      }
      if (bufferRx.charAt(i) == 'G') {
        int digit = bufferRx.charAt(i + 1) - 48;
        for (int j = 2; j <= digit + 1; j++) {
          strArusTerima3 += bufferRx.charAt(i + j);
        }
      }
      if (bufferRx.charAt(i) == 'H') {
        int digit = bufferRx.charAt(i + 1) - 48;
        for (int j = 2; j <= digit + 1; j++) {
          strTeganganTerima3 += bufferRx.charAt(i + j);
        }
      }
      if (bufferRx.charAt(i) == 'I') {
        int digit = bufferRx.charAt(i + 1) - 48;
        for (int j = 2; j <= digit + 1; j++) {
          strArusTerima4 += bufferRx.charAt(i + j);
        }
      }
      if (bufferRx.charAt(i) == 'J') {
        int digit = bufferRx.charAt(i + 1) - 48;
        for (int j = 2; j <= digit + 1; j++) {
          strTeganganTerima4 += bufferRx.charAt(i + j);
        }
      }
      if (bufferRx.charAt(i) == 'K') {
        int digit = bufferRx.charAt(i + 1) - 48;
        for (int j = 2; j <= digit + 1; j++) {
          strArusTerima5 += bufferRx.charAt(i + j);
        }
      }
      if (bufferRx.charAt(i) == 'L') {
        int digit = bufferRx.charAt(i + 1) - 48;
        for (int j = 2; j <= digit + 1; j++) {
          strTeganganTerima5 += bufferRx.charAt(i + j);
        }
      }
    }
    strArus1 = strArusTerima1;
    strTegangan1 = strTeganganTerima1;
    strArus2 = strArusTerima2;
    strTegangan2 = strTeganganTerima2;
    strArus3 = strArusTerima3;
    strTegangan3 = strTeganganTerima3;
    strArus4 = strArusTerima4;
    strTegangan4 = strTeganganTerima4;
    strArus5 = strArusTerima5;
    strTegangan5 = strTeganganTerima5;
    
    float power1 = strArus1.toFloat() * strTegangan1.toFloat();
    float power2 = strArus2.toFloat() * strTegangan2.toFloat();
    float power3 = strArus3.toFloat() * strTegangan3.toFloat();
    float power4 = strArus4.toFloat() * strTegangan4.toFloat();
    float power5 = strArus5.toFloat() * strTegangan5.toFloat();

    // set the fields with the values
    ThingSpeak.setField(1, power1);
    ThingSpeak.setField(2, power2);
    ThingSpeak.setField(3, power3);
    ThingSpeak.setField(4, power4);
    ThingSpeak.setField(5, power5);

    myStatus = "Power 1 = (" + strArus1 + " V " + strTegangan1 + " A) " + "\n" "Power 2 = (" + strArus2 + " V " + strTegangan2 + " A) " + "\n" + "Power 3 = (" + strArus3 + " V " + strTegangan3 + " A) " + "\n" + "Power 4 = (" + strArus4 + " V " + strTegangan4 + " A) " + "\n" + "Power 5 = (" + strArus5 + " V " + strTegangan5 + " A) " + "\n" ;
    ThingSpeak.setStatus(myStatus);

    // write to the ThingSpeak channel
    int x = ThingSpeak.writeFields(myChannelNumber, myWriteAPIKey);
    if (x == 200) {
//      Serial.println("Channel update successful.");
    }
    else {
//      Serial.println("Problem updating channel. HTTP error code " + String(x));
    }
    bufferRx = "";
    completeSerialRx = false;
  }
}
//AC42.10D41.10E42.10F41.40G44.10H42.10I41.60J44.50K45.10L42.60B
