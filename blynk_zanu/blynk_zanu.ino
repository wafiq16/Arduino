#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
char auth[] = "iayxmaE5W2QlGO9RaOwkF0jIaa3Wrp6e";

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "jalinan kasih";
char pass[] = "123456789";

bool Motor_State = 0;
bool Cleaner_State = 0;

//dummy data before running serial with stm32
double arus = 1;
double tegangan = 12;
double daya = arus * tegangan;

bool captureSerialRx = false;
bool completeSerialRx = false;

String bufferRx;

String strArusTerima;
String strTeganganTerima;

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
      strArusTerima = "";
      strTeganganTerima = "";
    }

    if (captureSerialRx) {
      bufferRx += rxChar;
    }
  }

  if (completeSerialRx) {
    for (int i = 0; i < strlen(bufferRx.c_str()); i++) {
      if (bufferRx.charAt(i) == 'I') {
        int digit = bufferRx.charAt(i + 1) - 48;
        for (int j = 2; j <= digit + 1; j++) {
          strArusTerima += bufferRx.charAt(i + j);
        }
      }
      if (bufferRx.charAt(i) == 'V') {
        int digit = bufferRx.charAt(i + 1) - 48;
        for (int j = 2; j <= digit + 1; j++) {
          strTeganganTerima += bufferRx.charAt(i + j);
        }
      }
    }
    
    Blynk.run();
    
    // set the fields with the values
    daya = strArusTerima.toFloat() * strTeganganTerima.toFloat();
    String LCD_atas = "A=" + strArusTerima + "A " + "V=" + strTeganganTerima + "V";
    String LCD_bawah = "daya = " + String(daya) + " W";
    Blynk.virtualWrite(V0, LCD_atas);
    Blynk.virtualWrite(V1, LCD_bawah);
    Blynk.virtualWrite(V2, strTeganganTerima);
    Blynk.virtualWrite(V3, strArusTerima);
    Blynk.virtualWrite(V4, daya);
    bufferRx = "";
    completeSerialRx = false;
  }
}

// CLEANER
BLYNK_WRITE(V5) { // This function gets called each time something changes on the widget
  Cleaner_State = param.asInt();
  if (Cleaner_State) {
    Serial.print("B1S");
    Serial.print("B1S");
    Serial.print("B1S");
  }
  else {
    Serial.print("B0S");
    Serial.print("B0S");
    Serial.print("B0S");
  }
}

// DC PUMP
BLYNK_WRITE(V6) { // This function gets called each time something changes on the widget
  Motor_State = param.asInt();
  if (Motor_State) {
    Serial.print("C1S");
    Serial.print("C1S");
    Serial.print("C1S");
  }
  else {
    Serial.print("C0S");
    Serial.print("C0S");
    Serial.print("C0S");
  }
}
