#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>

// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
char auth[] = "QLvIisllTBuXqa79YsmTGCculKTTv0bz";

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "hehehe";
char pass[] = "12345679";

bool haram_state = 0;
bool captureSerialRx = false;
bool completeSerialRx = false;


String status_string = ""; 
String bufferRx;
String halal = haram_state ? "haram bang" : "halal bang";
//String strMQTerima;
//String strTGSTerima;
//String strATerima;
//String strBTerima;
//String strCTerima;
//String strHalalTerima;

String strMQTerima = "60";
String strTGSTerima = "42";
String strATerima = "0";
String strBTerima = "255";
String strCTerima = "0";
String strHalalTerima = "1";

String strHalal = "";

void setup()
{
  // Debug console
  Serial.begin(9600);
  Blynk.begin(auth, ssid, pass);
}

void loop()
{
  Blynk.run();
  Serial.println(strHalalTerima.toInt());
  strHalal = strHalalTerima.toInt() == 0 ? "Haram" : "Halal"; 
  
  Blynk.virtualWrite(V0, strMQTerima);
  Blynk.virtualWrite(V1, strTGSTerima);
  Blynk.virtualWrite(V2, strATerima);
  Blynk.virtualWrite(V3, strBTerima);
  Blynk.virtualWrite(V4, strCTerima);
  Blynk.virtualWrite(V5, strHalal); 
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
      strATerima     = "";
      strBTerima     = "";
      strCTerima     = "";
      strHalalTerima = "";
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
        if (bufferRx.charAt(i) == 'G') {
          int digit = bufferRx.charAt(i + 1) - 48;
          for (int j = 2; j <= digit + 1; j++) {
            strATerima += bufferRx.charAt(i + j);
          }
        }
        if (bufferRx.charAt(i) == 'H') {
          int digit = bufferRx.charAt(i + 1) - 48;
          for (int j = 2; j <= digit + 1; j++) {
            strBTerima += bufferRx.charAt(i + j);
          }
        }
        if (bufferRx.charAt(i) == 'H') {
          int digit = bufferRx.charAt(i + 1) - 48;
          for (int j = 2; j <= digit + 1; j++) {
            strCTerima += bufferRx.charAt(i + j);
          }
        }
        if (bufferRx.charAt(i) == 'H') {
          int digit = bufferRx.charAt(i + 1) - 48;
          for (int j = 2; j <= digit + 1; j++) {
            strHalalTerima += bufferRx.charAt(i + j);
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
// susunan data pengiriman
//RM20T40A0B255C0H1S
