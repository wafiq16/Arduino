// GPIO 2 D4
#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

char auth[] = "toTdZfUc5TpPxpaaObNvA7QF39S9FxgC";

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "error";
char pass[] = "kurkurkur";

BlynkTimer timer;

int value = 0;

bool captureSerialRx = false;
bool completeSerialRx = false;

String bufferRx;

String strDayaTerima;
String strTeganganTerima;
String strRPMTerima;

void setup()
{
  // Debug console
  Serial.begin(115200);
  Blynk.begin(auth, ssid, pass);
}

void loop()
{
  readData();
}

void readData() {
  if (Serial.available()) {
    char rxChar = Serial.read();

    if (rxChar == 'A' && !captureSerialRx) captureSerialRx = true;
    else if (rxChar == 'B' && captureSerialRx) {
      captureSerialRx = false;
      completeSerialRx = true;
      strDayaTerima = "";
      strTeganganTerima = "";
      strRPMTerima = "";
    }

    if (captureSerialRx) {
      bufferRx += rxChar;
    }
  }

  if (completeSerialRx) {
    for (int i = 0; i < strlen(bufferRx.c_str()); i++) {
      if (bufferRx.charAt(i) == 'V') {
        int digit = bufferRx.charAt(i + 1) - 48;
        for (int j = 2; j <= digit + 1; j++) {
          strDayaTerima += bufferRx.charAt(i + j);
        }
      }
      if (bufferRx.charAt(i) == 'P') {
        int digit = bufferRx.charAt(i + 1) - 48;
        for (int j = 2; j <= digit + 1; j++) {
          strTeganganTerima += bufferRx.charAt(i + j);
        }
      }
      if (bufferRx.charAt(i) == 'R') {
        int digit = bufferRx.charAt(i + 1) - 48;
        for (int j = 2; j <= digit + 1; j++) {
          strRPMTerima += bufferRx.charAt(i + j);
        }
      }
    }
    Serial.println("isok");
    Serial.println(strDayaTerima);
    Serial.println(strTeganganTerima);
    Serial.println(strRPMTerima);
    // set the fields with the values
    Blynk.run();
    Blynk.virtualWrite(V0, strDayaTerima);
    Blynk.virtualWrite(V1, strTeganganTerima);
    Blynk.virtualWrite(V2, strRPMTerima);
    bufferRx = "";
    completeSerialRx = false;
  }
}
