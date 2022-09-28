//char auth[] = "YourAuthToken";
//char ssid[] = "YourNetworkName";
//char pass[] = "YourPassword";
//WidgetLCD lcd1(V4), lcd2(V5), lcd3(V6);

#include <EEPROM.h> //TDS
#include <GravityTDS.h> //TDS
#include <OneWire.h> //Suhu
#include <DallasTemperature.h> //Suhu
#include "RTClib.h" //pakan

#define TdsSensorPin A1 //TDS
#define ONE_WIRE_BUS 3 //Suhu
#define phpin A0 //pH

#define kipasPin 8 //Suhu
#define pumpIn 9 //air masuk TDS
#define pumpOut 10 //air keluar TDS
#define triggerPin 11 //jarak TDS
#define echoPin 12 //jarak TDS
#include <Servo.h> //pH dan pakan

GravityTDS gravityTds; //TDS
OneWire oneWire(ONE_WIRE_BUS); //Suhu
DallasTemperature sensorSuhu(&oneWire); //Suhu
Servo motors; //pH
Servo motor; //pakan
RTC_DS1307 rtc; //pakan

float tdsValue = 0; //TDS
float suhuAir; //Suhu
float phValue = 0; //pH
char dataHari[7][12] = {"Minggu", "Senin", "Selasa", "Rabu", "Kamis", "Jumat", "Sabtu"};
String hari; //pakan
int tanggal, bulan, tahun, jam, menit, detik; //pakan
// LCD State
String State_lcd1_waktu = "";
String State_lcd1_tanggal = "";
int State_lcd1_hari = 0;
int State_lcd2_motor = 0;
int State_lcd2_pakan = 0;
int State_lcd3_air = 0;
int State_lcd3_kipas = 0;

void setup(){
    Serial.begin(9600);
//    Blynk.begin(auth, wifi, ssid, pass);
//    lcd1.clear();
//    lcd2.clear();
//    lcd3.clear();
    gravityTds.setPin(TdsSensorPin); //TDS
    gravityTds.setAref(5.0);  //reference voltage on ADC, default 5.0V on Arduino UNO
    gravityTds.setAdcRange(1024);  //1024 for 10bit ADC;4096 for 12bit ADC
    gravityTds.begin();  //initialization
    sensorSuhu.begin(); //Suhu
    pinMode(phpin, INPUT); //pH
    pinMode(pumpIn,OUTPUT); //TDS
    pinMode(pumpOut,OUTPUT); //TDS
    pinMode(triggerPin, OUTPUT); //TDS
    pinMode(echoPin, INPUT); //TDS
    pinMode(kipasPin,OUTPUT); //Suhu
    motors.attach(6); //ph
    motors.write(0); //ph
    motor.attach(7); //pakan
    motor.write(0); //pakan
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
}

void loop(){
  Blynk.run();
  DateTime now = rtc.now();
  hari    = dataHari[now.dayOfTheWeek()];
  tanggal = now.day(), DEC;
  bulan   = now.month(), DEC;
  tahun   = now.year(), DEC;
  jam     = now.hour(), DEC;
  menit   = now.minute(), DEC;
  detik   = now.second(), DEC;
//  Serial.println(String() + hari + "," + tanggal + "-" + bulan + "-" + tahun);
//  Serial.println(String() + jam + ":" + menit + ":" + detik);
  State_lcd1_hari = now.dayOfTheWeek(); 
  State_lcd1_tanggal  = "," + String(tanggal) + "-" + String(bulan) + "-" + String(tahun);
  State_lcd1_waktu   = String(jam) + ":" + String(menit) + ":" + String(detik));
//  lcd1.print(0,0, String() + hari + "," + tanggal + "-" + bulan + "-" + tahun);
//  lcd1.print(0,1, String() + jam + ":" + menit + ":" + detik);
  
  phValue = 0;
  for(int i = 0; i<10; i++){
  phValue = phValue + analogRead(phpin);
  }
  float ratarataPh = phValue/10;
  float tegangan = (ratarataPh/1024)*5;
  float ph = -5.5435*tegangan + 30.277;
  Serial.print("pH : ");
  Serial.println(ph);
//  Blynk.virtualWrite(V1, ph);
    
  sensorSuhu.requestTemperatures();
  suhuAir = sensorSuhu.getTempCByIndex(0);
  Serial.print("Suhu : ");
  Serial.print(suhuAir);
  Serial.println(" °C");
//  Blynk.virtualWrite(V0, suhuAir);
  
  gravityTds.setTemperature(suhuAir);  // set the temperature and execute temperature compensation
  gravityTds.update();  //sample and calculate 
  tdsValue = gravityTds.getTdsValue();  // then get the value
  Serial.print("TDS : ");
  Serial.print(tdsValue);
  Serial.println(" ppm");
//  Blynk.virtualWrite(V2, tdsValue);

  long duration, jarak;
  digitalWrite(triggerPin, LOW);
  delayMicroseconds(2);
  digitalWrite(triggerPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(echoPin, LOW);
  duration=pulseIn(echoPin, HIGH);
  jarak=(duration/2)/29.1;
  Serial.print("jarak : ");
  Serial.print(jarak);
  Serial.println("cm");
  Blynk.virtualWrite(V3, jarak);

  if(Serial.available() > 0){
   Serial.print("A%.2f%.2f%d%d%d%d%d%d%s%sB", ph, suhuAir, tdsValue, jarak, State_lcd3_kipas, State_lcd3_air, State_lcd2_pakan, State_lcd2_motor, State_lcd1_Waktu, State_lcd1_Hari); 
  }
  
  if(tdsValue>400){
    digitalWrite(pumpOut,HIGH);
    digitalWrite(pumpIn,LOW);
    Serial.println("Kuras Air");
//    lcd3.print(0,1, "Kuras Air");
    State_lcd3_air = 1;
  }
  if(jarak>22){
    digitalWrite(pumpOut,LOW);
    digitalWrite(pumpIn,HIGH);
    Serial.println("Isi Air");
//    lcd3.print(0,1, "Isi Air");
    State_lcd3_air = 2;
  }
  if(jarak>7){
    digitalWrite(pumpOut,LOW);
    digitalWrite(pumpIn,LOW);
    Serial.println("Air Penuh");
//    lcd3.print(0,1, "Air Penuh");
    State_lcd3_air = 3;
  }
    
  if (suhuAir>30){
    digitalWrite(kipasPin,HIGH);
    Serial.println("Kipas ON");
    // lcd3.print(0,0, "Kipas ON");
    State_lcd3_kipas = 1;
  } 
  if (suhuAir<30){
    digitalWrite(kipasPin,LOW);
    Serial.println("Kipas OFF");
    // lcd3.print(0,0, "Kipas OFF");
    State_lcd3_kipas = 0;
  }
  if (ph<6){
    kasih_ph(1);
    Serial.println("Motor pH ON");
    // lcd2.print(0,0, "Motor pH ON");
    State_lcd2_motor = 1;
  }
  if (ph>6){
    Serial.println("Motor pH OFF");
    // lcd2.print(0,0, "Motor pH OFF");
    State_lcd2_motor = 0;
  }
  if(jam == 07 & menit == 30 & detik == 1){
    kasih_pakan(1);
    Serial.println("Pakan Pagi");
    // lcd2.print(0,1, "Pakan Pagi");
    State_lcd2_pakan = 1;
  }
    if(jam == 13 & menit == 30 & detik == 1){
     kasih_pakan(1);
     Serial.println("Pakan Siang");
    //  lcd2.print(0,1, "Pakan Siang");
    State_lcd2_pakan = 2;
  }
  if(jam == 18 & menit == 30 & detik == 1){
     kasih_pakan(1);
     Serial.print("Pakan Malam");
    //  lcd2.print(0,1, "Pakan Malam");
    State_lcd2_pakan = 3;
  }
    delay(500);
}

void kasih_ph(int jumlah){
  for(int i = 1; i<= jumlah; i++){
  motors.write(150);
  delay(100);
  motors.write(0);
  delay(100);}
}

void kasih_pakan(int jumlah){
  for(int i = 1; i<= jumlah; i++){
  motor.write(150);
  delay(100);
  motor.write(0);
  delay(100);}
}
