#include <String.h>
bool captureSerialRx = false;
bool completeSerialRx = false;

String bufferRx;
String strSuhuTerima;
String strLedTerima;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  if (Serial.available()) {
    char rxChar = Serial.read();

    if (rxChar == 'A' && !captureSerialRx) captureSerialRx = true;
    else if (rxChar == 'B' && captureSerialRx) {
      captureSerialRx = false;
      completeSerialRx = true;
    }

    if (captureSerialRx) {
      bufferRx += rxChar;
    }
  }

  if (completeSerialRx) {
    strSuhuTerima = bufferRx.charAt(1);
    strSuhuTerima += bufferRx.charAt(2);
    strSuhuTerima += bufferRx.charAt(3);
    strSuhuTerima += bufferRx.charAt(4);
    strSuhuTerima += bufferRx.charAt(5);

    strLedTerima = bufferRx.charAt(6);
    bufferRx = "";
    completeSerialRx = false;
    Serial.println(strSuhuTerima);
    Serial.println(strLedTerima);
  }
}
