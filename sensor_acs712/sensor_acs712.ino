const int pinADC = A0;
int sensitivitas = 66; //tegantung sensor arus yang digunakan, yang ini 30A
int nilaiadc= 00;
double teganganoffset = 2117; //nilai pembacaan offset saat tidak ada arus yang lewat
double tegangan = 00;
double nilaiarus = 00;
double nilaiarusakhir = 00;
double averageCurrent = 00;
int i = 0;
 
void setup(){
Serial.begin(9600); //baud komunikasi serial monitor 9600bps
//Serial.print("*MODULE ARUS*"); //menuliskan "Hello World"
//Serial.print("*nyebarilmu.com*"); //menuliskan "nyebarilmu.com"
 
delay(2000);
}
 
void data_olah(){
  nilaiadc = analogRead(pinADC);
  tegangan = ((nilaiadc) / 1024.0) * 5000;
  nilaiarus = ((tegangan-teganganoffset) / sensitivitas);
//  if(nilaiarus < 0)
//    nilaiarus = 0;
  averageCurrent += nilaiarus;
  if(i>10){
    i = 0;
    averageCurrent = averageCurrent/10;
    nilaiarusakhir = averageCurrent;
  }
  i++;
}
 
void loop(){
   data_olah();
  Serial.print("Nilai ADC yang terbaca = " );
  Serial.print(nilaiadc);
 
  Serial.print("\t tegangan (mV) = ");
  Serial.print(tegangan,3);
 
  Serial.print("\t Arus = ");
  Serial.println(nilaiarusakhir,3);
 
//  delay(1000);
}
 
