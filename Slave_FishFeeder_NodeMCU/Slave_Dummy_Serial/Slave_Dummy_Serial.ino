#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
//A5.5930.38283234510:50:40120B
// 2 7 = .
//19 22 = :
char auth[] = "yvb5kccFol1Gg3nMfAyju6ncTZqT8__E";
char ssid[] = "hehehe";
char pass[] = "12345670";

WidgetLCD lcd1(V4), lcd2(V5);// lcd3(V6);

float tdsValue = 0; //TDS
float suhuAir = 0; //Suhu
float ph = 0; //pH
float jarak = 0;
String bufferRx;
bool captureSerialRx = false;
bool completeSerialRx = false;

int Jarak = 0;
int Pakan = 0;
int Motor = 0;
int Hari = 0;
int Air = 0;
int Kipas = 0;

String strPhTerima;
String strSuhuTerima;
String strTdsTerima;
String strJarakTerima;
String strLcd3KipasTerima;
String strLcd3AirTerima;
String strLcd3MotorTerima;
String strLcd3PakanTerima;
String strLcd3HariTerima;
String strWaktuTerima;

String stringLcd2Kipas;
String stringLcd2Air;
String stringLcd2Motor;
String stringLcd1Pakan;
String stringLcd1Hari;

int time_to_clear_lcd = 0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  Blynk.begin(auth, ssid, pass);
  lcd1.clear();
  lcd2.clear();
//  lcd3.clear();
}

void loop() {
  // put your main code here, to run repeatedly:
  
   Blynk.run();
    baca_pesan();
//   Pakan session
   if(Pakan == 1){
      stringLcd1Pakan = "Pakan Pagi";
    }
    else if(Pakan == 2){
      stringLcd1Pakan = "Pakan Siang";
    }
    else if(Pakan == 3){
      stringLcd1Pakan = "Pakan Malam";
    }
// Air session
  if(Air == 1){
      stringLcd2Air = "Kuras Air";
    }
   else if(Air == 2){
      stringLcd2Air = "Isi Air";
    }
    else if(Air == 3){
      stringLcd2Air = "Air Penuh";
    }
//    Motor session
  if(Motor == 0){
      stringLcd2Motor = "M pH OFF";
    }
   else if(Motor == 1){
      stringLcd2Motor = "M pH ON";
    }
//  Kipas session
  if(Kipas == 0){
      stringLcd2Kipas = "AC OFF";
    }
   else if(Kipas == 1){
      stringLcd2Kipas = "AC ON";
    }
//    Hari decoder
  if(Hari == 1)
  {
    stringLcd1Hari = "Senin";
  }
  else if(Hari == 2){
      stringLcd1Hari = "Selasa";
  }
  else if(Hari == 3){
      stringLcd1Hari = "Rabu";
  }
  else if(Hari == 4){
      stringLcd1Hari = "Kamis";
  }
  else if(Hari == 5){
      stringLcd1Hari = "Jumat";
  }
  else if(Hari == 6){
      stringLcd1Hari = "Sabtu";
  }
  else if(Hari == 7){
      stringLcd1Hari = "Minggu";
  }
  if(Serial.available()){
    Serial.print(strPhTerima + strSuhuTerima + strTdsTerima +  strLcd3KipasTerima + strLcd3AirTerima + strLcd3PakanTerima + strLcd3MotorTerima + strWaktuTerima + strLcd3HariTerima + strJarakTerima); 
    Serial.print("\n millis print" + String(millis()) + "\n");
  }

    if(millis() - time_to_clear_lcd > 5000 ){
        lcd1.clear();
        lcd2.clear();
        time_to_clear_lcd = millis();
    }
  Blynk.virtualWrite(V0, strSuhuTerima);
    Blynk.virtualWrite(V1, strPhTerima);
    Blynk.virtualWrite(V2, strTdsTerima);
    Blynk.virtualWrite(V3, strJarakTerima);
    
    lcd1.print(0,0, stringLcd1Hari + ", " + strWaktuTerima);
    lcd1.print(3,1, stringLcd1Pakan);
    
    lcd2.print(0,0, stringLcd2Motor + "  " + stringLcd2Kipas);
    lcd2.print(3,1, stringLcd2Air);
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
    Serial.print("buffer = " + bufferRx + "\n");
    if(bufferRx.charAt(2) == '.' && bufferRx.charAt(7) == '.' && bufferRx.charAt(19) == ':' && bufferRx.charAt(22) == ':'){
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
    strLcd3KipasTerima = bufferRx.charAt(13);
    Kipas = strLcd3KipasTerima.toInt();

    strLcd3AirTerima = bufferRx.charAt(14);
    Air = strLcd3AirTerima.toInt();
    
    strLcd3PakanTerima = bufferRx.charAt(15);
    Pakan = strLcd3PakanTerima.toInt();

    strLcd3MotorTerima = bufferRx.charAt(16);
    Motor = strLcd3MotorTerima.toInt();

    strWaktuTerima = bufferRx.charAt(17);
    strWaktuTerima += bufferRx.charAt(18);
    strWaktuTerima += bufferRx.charAt(19);
    strWaktuTerima += bufferRx.charAt(20);
    strWaktuTerima += bufferRx.charAt(21);
    strWaktuTerima += bufferRx.charAt(22);
    strWaktuTerima += bufferRx.charAt(23);
    strWaktuTerima += bufferRx.charAt(24);

    strLcd3HariTerima = bufferRx.charAt(25);
    Hari = strLcd3HariTerima.toInt();
    
    strJarakTerima = bufferRx.charAt(26);

    strJarakTerima += bufferRx.charAt(27);
    
//    bufferRx = "";
//    completeSerialRx = false;
    }
    bufferRx = "";
    completeSerialRx = false;
  }
}
