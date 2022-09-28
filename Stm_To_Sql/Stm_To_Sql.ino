#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <SPI.h>
#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>
#include <ESP8266HTTPClient.h>

// Buat object Wifi
ESP8266WiFiMulti WiFiMulti;

// Buat object http
HTTPClient http;

String url = "http://monitoringrbgi.com/config/simpan.php?suhu=";
String payload = "";

double SuhuTerima = 0;
double KelembapanTerima = 0;
double TeganganTerima = 0;

String strSuhuTerima;
String strTeganganTerima;
String strKelembapanTerima;

bool captureSerialRx = false;
bool completeSerialRx = false;

String bufferRx;

WiFiClient clientku;

void setup(void) {
  //the HTML of the web page
  Serial.begin(9600);

  //WiFi.mode(WIFI_STA);
  WiFi.begin("Fahmi", "hadehhhh");
}
void loop(void) {
  //server.handleClient();
  baca_pesan();
}

void postData() {
  // Tambahkan nilai suhu pada URL yang sudah kita buat
  
  http.begin(clientku ,url + strSuhuTerima + "&kelembapan=" + strKelembapanTerima + "&tegangan=" + strTeganganTerima);
  int httpCode = http.GET();

  if (httpCode > 0)
  {
    payload = http.getString(); 
    if (httpCode == HTTP_CODE_OK) {
      payload = http.getString();
    }
  }
  http.end();
  delay(1000);
}

void baca_pesan(){
  if(Serial.available()){
    char rxChar = Serial.read();

    if(rxChar == 'A' && !captureSerialRx) captureSerialRx = true;
    else if(rxChar == 'S' && captureSerialRx) {
      captureSerialRx = false;
      completeSerialRx = true;
    }

    if(captureSerialRx) {
      bufferRx += rxChar;
    }
    // char *boga = "\njalan\n";
    // publishSerialData(boga, WAFIQTOPICDEMO1);
  }

  if(completeSerialRx){
    strSuhuTerima = bufferRx.charAt(1);
    strSuhuTerima += bufferRx.charAt(2);
    strSuhuTerima += bufferRx.charAt(3);
    strSuhuTerima += bufferRx.charAt(4);
    strSuhuTerima += bufferRx.charAt(5);
    //if(strlen(strSuhuTerima.c_str()) == 5) SuhuTerima = strtof(strSuhuTerima);
    Serial.println(strSuhuTerima);
    
    strKelembapanTerima = bufferRx.charAt(6);
    strKelembapanTerima += bufferRx.charAt(7);
    strKelembapanTerima += bufferRx.charAt(8);
    strKelembapanTerima += bufferRx.charAt(9);
    strKelembapanTerima += bufferRx.charAt(10);
    //if(strlen(strKelembapanTerima.c_str()) == 5) KelembapanTerima = strtof(strKelembapanTerima);
    Serial.println(strKelembapanTerima);
    
    strTeganganTerima = bufferRx.charAt(11);
    strTeganganTerima += bufferRx.charAt(12);
    strTeganganTerima += bufferRx.charAt(13);
    strTeganganTerima += bufferRx.charAt(14);
    strTeganganTerima += bufferRx.charAt(15);
    //if(strlen(strTeganganTerima.c_str()) == 5) TeganganTerima = strtof(strTeganganTerima);
    Serial.println(strTeganganTerima);
    
    bufferRx = "";
    completeSerialRx = false;
    if (WiFi.status() == WL_CONNECTED) {
      postData();
    }
    else
    {
      //WiFi.begin("hehehe", "12345670");
      Serial.println("rakenek asu");
    }
  }
}
