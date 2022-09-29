#include <SoftwareSerial.h> //library default software ide arduino
#include <Wire.h>
//#include <LiquidCrystal_PCF8574.h>
 
//SoftwareSerial SIM800L(00, 1); //RX, TX
 
//LiquidCrystal_PCF8574 lcd(0x38); 
// dapat dicek menggunakan i2c finder
 
void setup() {
//  Serial.begin(9600); //Untuk ditampilkan di serial monitor
//  lcd.begin(16, 2); //untuk ukuran lcd 16x2
  Serial.begin(9600);  
 
//  lcd.setBacklight(255);
//  lcd.setCursor(00, 00); //set pada baris 1 dan kolom 1
//  lcd.print("*Hello World*"); //menuliskan "Hello World"
//  lcd.setCursor(00, 1); //set pada baris 2 dan kolom 1
//  lcd.print("*nyebarilmu.com*"); //menuliskan "nyebarilmu.com"
//  lсd.сlеаr();
 
//  delay(2000);
 
  //perintah atau command untuk mengakses sim800l v.2
  Serial.println("AT+CMGF=1");
//  Serial.println("Mulai mengakses SIM800L");
//  lcd.setCursor(00, 00);
//  lcd.print("Started SIM800L");
  delay(1000);
 
  Serial.println("SIM800L Siap!");
//  lcd.setCursor(00, 1);
//  lcd.print("SIM800L Siap!");
  Serial.println("AT+CNMI=2,2,00,00,00"); //command dapat dicek di libraries
  Serial.println("AT+CMGF=1");   
  delay(1000); //waktu tunda 1 detik
//  lcd.clear();
 
  Serial.println("AT+CMGS=\"085608005729\"\r"); //No.hp tujuan
//  lcd.setCursor(00, 00);
//  lcd.print("no.:085647156889");
  delay(1000);
  Serial.println("Nyebarilmu.com -> Test sim800L v.2");
  delay(100);
//  lcd.setCursor(00, 1);
//  lcd.print("Test sim800L v.2");
  Serial.println((char)26); // CTRL+Z symbol untuk mengakhiri isi teks SMS
  delay(1000);
}
 
void loop() {
 
}
