#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

char auth[] = "YourAuthToken";
char ssid[] = "YourNetworkName";
char pass[] = "YourPassword";
float tdsValue = 0; //TDS
float suhuAir = 0; //Suhu
float phValue = 0; //pH
float jarak = 0;
String bufferRx;
bool captureSerialRx = false;
bool completeSerialRx = false;
String strPhTerima;
String strSuhuTerima;
String strTdsTerima;
String strJarakTerima;
WidgetLCD lcd1(V4), lcd2(V5), lcd3(V6);

void setup() {
  // put your setup code here, to run once:
  Blynk.begin(auth, ssid, pass);
  lcd1.clear();
  lcd2.clear();
  lcd3.clear();
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  Blynk.run();
  baca_pesan();
  Blynk.virtualWrite(V1, phValue);
  Blynk.virtualWrite(V0, suhuAir);
  Blynk.virtualWrite(V2, tdsValue);
  Blynk.virtualWrite(V3, jarak);
  lcd1.print(0,0, String() + hari + "," + tanggal + "-" + bulan + "-" + tahun);
  lcd1.print(0,1, String() + jam + ":" + menit + ":" + detik);
  Serial.print(strPhTerima);
  Serial.print(strSuhuTerima);
  Serial.print(strTdsTerima);
  Serial.print(strJarakTerima);
}

void baca_pesan(){
  if(Serial.available()){
    char rxChar = Serial.read();

    if(rxChar == 'A' && !captureSerialRx) captureSerialRx = true;
    else if(rxChar == 'B' && captureSerialRx) {
      captureSerialRx = false;
      completeSerialRx = true;
    }

    if(captureSerialRx) {
      bufferRx += rxChar;
    }
  }

  if(completeSerialRx){
    strPhTerima = bufferRx.charAt(1);
    strPhTerima += bufferRx.charAt(2);
    strPhTerima += bufferRx.charAt(3);
    strPhTerima += bufferRx.charAt(4);
//    phValue = strPhTerima.toInt();
    // arusTerima = strArusTerima.toInt();

    strSuhuTerima = bufferRx.charAt(5);
    strSuhuTerima += bufferRx.charAt(6);
    strSuhuTerima += bufferRx.charAt(7);
    strSuhuTerima += bufferRx.charAt(8);
    strSuhuTerima += bufferRx.charAt(9);
//    suhuAir = strSuhuTerima.toInt();
    
    strTdsTerima = bufferRx.charAt(10);
    strTdsTerima += bufferRx.charAt(11);
    strTdsTerima += bufferRx.charAt(12);
//    tdsValue = strTdsTerima.toInt();
    
    strJarakTerima = bufferRx.charAt(13);
    strJarakTerima += bufferRx.charAt(14);
    strJarakTerima += bufferRx.charAt(15);
//    jarak = strJarakTerima.toInt();
    
    bufferRx = "";
    completeSerialRx = false;
  }
}
