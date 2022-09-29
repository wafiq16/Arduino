
#include <Adafruit_GFX.h>      // include Adafruit graphics library
#include <Adafruit_ST7735.h>   // include Adafruit ST7735 TFT library
#include <SPI.h>
#include <Adafruit_I2CDevice.h>
#define TFT_RST   8      // TFT RST pin is connected to arduino pin 8
#define TFT_CS    10      // TFT CS  pin is connected to arduino pin 9
#define TFT_DC    9     // TFT DC  pin is connected to arduino pin 10
// initialize ST7735 TFT library
Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS, TFT_DC, TFT_RST);


//  data pin connection

const int numReadings = 10;
int readings[numReadings];
int readIndex = 0;
int total = 0;
double average = 0;
int inputPin = A3;
float MQ3 = 0;
float V_1 = 0;

const int numReadings_1 = 10;
int readings_1[numReadings_1];
int readIndex_1 = 0;
int total_1 = 0;
double average_1 = 0;
int inputPin_1 = A1;
float TGS = 0 ;
float V_2 = 0;


int A = 0;
int B = 0;
int C = 0;
int D = 0;
int E = 0;
int F = 0;
bool H1 = false;
bool H2 = false;

void setup(void)
{
  Serial.begin(9600);


  // pinMode(2,OUTPUT);// Buz
  pinMode(3, OUTPUT); // Hijau MQ3
  pinMode(4, OUTPUT); // Kuning MQ3
  pinMode(5, OUTPUT); // Merah MQ3
  pinMode(6, OUTPUT); // Hijau  TGS
  pinMode(7, OUTPUT); // Kuning TGS
  pinMode(12, OUTPUT); // Merah TGS
  ;

  for (int thisReading = 0; thisReading < numReadings; thisReading++)
  {
    readings[thisReading] = 0;
  }

  for (int thisReading_1 = 0; thisReading_1 < numReadings_1; thisReading_1++)
  {
    readings_1[thisReading_1] = 0;
  }

  //analogReference(INTERNAL);     // set positive reference voltage to 1.1V

  tft.initR(INITR_BLACKTAB);     // initialize a ST7735S chip, black tab
  //tft.fillScreen(ST7735_BLACK);  // fill screen with black color

  //  tft.setCursor(30, 80);
  //  tft.setTextColor(ST7735_GREEN);
  // tft.setTextSize(1);
  // tft.print("Halal");

  //  tft.setCursor(70, 80);
  //  tft.setTextColor(ST7735_RED);
  //  tft.setTextSize(1);
  //  tft.print("Haram");

  /////////////////////////////////

  //  tft.setCursor(30, 135);
  // tft.setTextColor(ST7735_GREEN);
  //  tft.setTextSize(1);
  //  tft.print("Halal");

  // tft.setCursor(70, 135);
  // tft.setTextColor(ST7735_RED);
  //  tft.setTextSize(1);
  //  tft.print("Haram");

  //tftPrintTest();
  //  Serial.begin(9600);

  splashScreen();

}

// main loop
void loop()
{
  //////////////////////////// Tampilan//////////////////////
  /////////////////ADC////////////////
  char _buffer[8];

  // Pembacaan rata2 MQ3

  total = total - readings[readIndex];
  readings[readIndex] = analogRead(inputPin);
  total = total + readings[readIndex];
  readIndex = readIndex + 1;
  if (readIndex >= numReadings)
  {
    readIndex = 0;
  }

  // Pembacaan rata2 TGS2620
  total_1 = total_1 - readings_1[readIndex_1];
  readings_1[readIndex_1] = analogRead(inputPin_1);
  total_1 = total_1 + readings_1[readIndex_1];
  readIndex_1 = readIndex_1 + 1;
  if (readIndex_1 >= numReadings_1)
  {
    readIndex_1 = 0;
  }

  // hitung rata2 Pembacaan kedua sensor dan rumus hasil regresi.
  //  average = total / numReadings;
  //  MQ3 = ((average) *    0.1014 - 21.366)+11;
  //  average_1 = total_1 / numReadings_1;
  //  TGS = ((average_1) * 0.121 - 24.183)+1;

  average = total / numReadings;
  MQ3 = ((average) * 0.1282 - 20.865) + 21;
  average_1 = total_1 / numReadings_1;
  TGS = ((average_1) * 0.1218 - 40.461) + 27 ; //0.1218x - 40.461

  V_1 = (MQ3 * 4.76 / 1023);
  V_2 = (TGS * 4.76 / 1023);

  // Tampilan Serial Monitor
  //  Serial.print("  MQ3=");
  //  Serial.print(MQ3);
  //  Serial.print(" V=");
  //  Serial.print(V_1);
  //
  //  Serial.print("   TGS=");
  //  Serial.print(TGS);
  //  Serial.print(" V=");
  //  Serial.println(V_2);

  //  delay(100);


  //  char _buffer[8];
  //
  //  // Pembacaan rata2 MQ3
  //
  //  total = total - readings[readIndex];
  //  readings[readIndex] = analogRead(inputPin);
  //  total = total + readings[readIndex];
  //  readIndex = readIndex + 1;
  //  if (readIndex >= numReadings)
  //  {
  //    readIndex = 0;
  //  }
  //
  //
  //  // Pembacaan rata2 TGS2620
  //  total_1 = total_1 - readings_1[readIndex_1];
  //  readings_1[readIndex_1] = analogRead(inputPin_1);
  //  total_1 = total_1 + readings_1[readIndex_1];
  //  readIndex_1 = readIndex_1 + 1;
  //  if (readIndex_1 >= numReadings_1)
  //  {
  //    readIndex_1 = 0;
  //  }
  //
  //  // hitung rata2 Pembacaan kedua sensor dan rumus hasil regresi.
  //  average = total / numReadings;
  //  MQ3 = ((average) * 0.1282 - 20.865) + 10;
  //  average_1 = total_1 / numReadings_1;
  //  TGS = ((average_1) * 0.1218 - 40.461) -2 ;//0.1218x - 40.461
  //
  //
  ////  average = total / numReadings;
  //// MQ3 = ((average) * 0.1282 - 20.865) + 10;
  ////  average_1 = total_1 / numReadings_1;
  ////  TGS = ((average_1) * 0.1282 - 20.865)  ;
  //
  //
  //  // Tampilan Serial Monitor
  //    Serial.print("     MQ3=");
  //    Serial.print(MQ3);
  //    Serial.print("     TGS2620=");
  //    Serial.println(TGS);
  //  //  delay(100);


  //Tampilan LCD Nilai %

  tft.setCursor(50, 60);     //50,30
  tft.setTextColor(ST7735_WHITE, ST7735_BLUE);
  tft.setTextSize(1);
  tft.println(MQ3, 1);

  tft.setCursor(50, 115);
  tft.setTextColor(ST7735_WHITE, ST7735_BLUE);
  tft.setTextSize(1);
  tft.println(TGS, 1);
  delay(500);

  // Program perbandingan dalam penentuan Golongan

  ////////////////////////////////// Perbandingan golongan MQ3//////////////////////////

  if (MQ3 < 0.5)       // jika MQ3 <1
  {
    tft.fillRect(70, 80, 40, 10, ST77XX_BLUE);
    tft.setCursor(30, 80);
    tft.setTextColor(ST7735_GREEN);
    tft.setTextSize(1);
    tft.print("Halal");

    //  digitalWrite(2, LOW); //Buzzer

    H1 = 1;
    A = 0;
    B = 0;
    C = 0;

  }

  else if (MQ3 < 5 )       // jika MQ3 <5
  {

    digitalWrite(3, HIGH); // Hijau MQ3
    digitalWrite(4, LOW);// Kuning MQ3
    digitalWrite(5, LOW);// Merah MQ3

    tft.setCursor(40, 70);
    tft.setTextColor(ST7735_WHITE);
    tft.setTextSize(1);
    tft.print("Golongan A");


    tft.fillRect(20, 80, 40, 10, ST77XX_BLUE);
    tft.setCursor(70, 80);
    tft.setTextColor(ST7735_RED);
    tft.setTextSize(1);
    tft.print("Haram");
    A = 1;
    B = 0;
    C = 0;
    H1 = 0;
  }


  else if (MQ3  < 20)       // jika MQ3 5-20
  {

    digitalWrite(3, LOW); // Hijau MQ3
    digitalWrite(4, HIGH);// Kuning MQ3
    digitalWrite(5, LOW);// Merah MQ3

    tft.setCursor(40, 70);
    tft.setTextColor(ST7735_WHITE);
    tft.setTextSize(1);
    tft.print("Golongan B");

    tft.fillRect(20, 80, 40, 10, ST77XX_BLUE);
    tft.setCursor(70, 80);
    tft.setTextColor(ST7735_RED);
    tft.setTextSize(1);
    tft.print("Haram");

    A = 0;
    B = 1;
    C = 0;
    H1 = 0;

  }


  else if (MQ3  < 55)       // jika MQ3 20-55
  {

    digitalWrite(3, LOW); // Hijau MQ3
    digitalWrite(4, LOW);// Kuning MQ3
    digitalWrite(5, HIGH);// Merah MQ3

    tft.setCursor(40, 70);
    tft.setTextColor(ST7735_WHITE);
    tft.setTextSize(1);
    tft.print("Golongan C");

    tft.fillRect(20, 80, 40, 10, ST77XX_BLUE);
    tft.setCursor(70, 80);
    tft.setTextColor(ST7735_RED);
    tft.setTextSize(1);
    tft.print("Haram");
    digitalWrite(2, HIGH); //Buzzer

    A = 0;
    B = 0;
    C = 1;
    H1 = 0;
  }

  else if (MQ3  > 55)       // jika MQ3 5-20
  {

    digitalWrite(3, LOW); // Hijau MQ3
    digitalWrite(4, LOW);// Kuning MQ3
    digitalWrite(5, HIGH);// Merah MQ3

    tft.fillRect(20, 80, 40, 10, ST77XX_BLUE);
    tft.setCursor(70, 80);
    tft.setTextColor(ST7735_RED);
    tft.setTextSize(1);
    tft.print("Haram");

    digitalWrite(2, HIGH); //Buzzer

    A = 0;
    B = 0;
    C = 1;
    H1 = 0;
  }


  ////////////////////////////////// Perbandingan golongan TGS//////////////////////////

  if (TGS < 0.5)       // jika TGS <1
  {
    tft.fillRect(70, 135, 40, 10, ST77XX_BLUE);
    tft.setCursor(30, 135);
    tft.setTextColor(ST7735_GREEN);
    tft.setTextSize(1);
    tft.print("Halal");

    H2 = 1;
    D = 0;
    E = 0;
    F = 0;
  }

  else if (TGS < 5 )       // jika TGS<5
  {

    digitalWrite(6, HIGH); // Hijau TGS
    digitalWrite(7, LOW);// Kuning TGS
    digitalWrite(12, LOW);// Merah TGS

    tft.setCursor(40, 125);      //40,135
    tft.setTextColor(ST7735_WHITE);
    tft.setTextSize(1);
    tft.print("Golongan A");

    tft.fillRect(20, 135, 40, 10, ST77XX_BLUE);
    tft.setCursor(70, 135);
    tft.setTextColor(ST7735_RED);
    tft.setTextSize(1);
    tft.print("Haram");

    D = 1;
    E = 0;
    F = 0;
    H2 = 0;
  }


  else if (TGS  < 20)       // jika TGS 5-20
  {

    digitalWrite(6, LOW); // Hijau TGS
    digitalWrite(7, HIGH);// Kuning TGS
    digitalWrite(12, LOW);// Merah TGS


    tft.setCursor(40, 125);      //40,135
    tft.setTextColor(ST7735_WHITE);
    tft.setTextSize(1);
    tft.print("Golongan B");

    tft.fillRect(20, 135, 40, 10, ST77XX_BLUE);
    tft.setCursor(70, 135);
    tft.setTextColor(ST7735_RED);
    tft.setTextSize(1);
    tft.print("Haram");

    D = 0;
    E = 1;
    F = 0;
    H2 = 0;

  }


  else if (TGS  < 55)       // jika TGS 20-55
  {

    digitalWrite(6, LOW); // Hijau TGS
    digitalWrite(7, LOW);// Kuning TGS
    digitalWrite(12, HIGH);// Merah TGS

    tft.setCursor(40, 125);      //40,135
    tft.setTextColor(ST7735_WHITE);
    tft.setTextSize(1);
    tft.print("Golongan C");

    tft.fillRect(20, 135, 40, 10, ST77XX_BLUE);
    tft.setCursor(70, 135);
    tft.setTextColor(ST7735_RED);
    tft.setTextSize(1);
    tft.print("Haram");

    D = 0;
    E = 0;
    F = 1;
    H2 = 0;
  }

  else if (TGS  > 55)       // jika TGS 5-20
  {
    digitalWrite(6, LOW); // Hijau TGS
    digitalWrite(7, LOW);// Kuning TGS
    digitalWrite(12, HIGH);// Merah TGS

    tft.fillRect(20, 135, 40, 10, ST77XX_BLUE);
    tft.setCursor(70, 135);
    tft.setTextColor(ST7735_RED);
    tft.setTextSize(1);
    tft.print("Haram");

    D = 0;
    E = 0;
    F = 1;
    H2 = 0;
  }

  //  Pasti akan muncul error ini
  // =========================================================
  //  H = 0; // nilai haram dan halal 0 berarti haram, 1 berarti halal
  //  ========================================================

  delay(100);    // wait a second

  int digitMQ3 = strlen(String((int)MQ3).c_str());
  int digitTGS = strlen(String((int)TGS).c_str());

  int digitA = strlen(String((int)A).c_str());
  int digitB = strlen(String((int)B).c_str());
  int digitC = strlen(String((int)C).c_str());

  int digitD = strlen(String((int)D).c_str());
  int digitE = strlen(String((int)E).c_str());
  int digitF = strlen(String((int)F).c_str());

  int digitH1 = strlen(String((int)H1).c_str());
  int digitH2 = strlen(String((int)H2).c_str());
  //  RM220T240A10B3255C10H11S
  Serial.print("RM" + String(digitMQ3) +  String(MQ3) + "T" + String(digitTGS) + String(TGS) + "A" + String(digitA) + A + "B" + String(digitB) + B + "C" + String(digitC) + C + "H" + String(digitH1) + H1 + "D" + String(digitD) + D + "E" + String(digitE) + E + "F" + String(digitF) + F + "I" + String(digitH2) + H2 + "S" );
}
void splashScreen() {
  tft.fillScreen(ST7735_WHITE);

  tft.fillRoundRect(15, 45, 100, 50, 4, ST7735_BLUE);     //15, 10, 100, 50, 4
  tft.fillRoundRect(15, 100, 100, 50, 4, ST7735_BLUE);     //15, 100, 100, 50, 4


  tft.setCursor(20, 11);      //20,66
  tft.setTextColor(ST7735_RED);
  tft.setTextSize(2);
  tft.print("DETECTOR");

  tft.setCursor(25, 27);      //25,82
  tft.setTextColor(ST7735_RED);
  tft.setTextSize(2);
  tft.print("ALCOHOL");

  tft.setCursor(57, 50);      //57,15
  tft.setTextColor(ST7735_YELLOW);
  tft.setTextSize(1);
  tft.print("MQ3");

  tft.setCursor(80, 60);      //80,30
  tft.setTextColor(ST7735_WHITE);
  tft.setTextSize(1);
  tft.print("%");

  tft.setCursor(40, 70);      //40,45
  tft.setTextColor(ST7735_WHITE);
  tft.setTextSize(1);
  tft.print("Golongan");


  tft.setCursor(44, 105);      //44,105
  tft.setTextColor(ST7735_YELLOW);
  tft.setTextSize(1);
  tft.print("TGS2620");

  tft.setCursor(80, 115);      //80,120
  tft.setTextColor(ST7735_WHITE);
  tft.setTextSize(1);
  tft.print("%");

  tft.setCursor(40, 125);      //40,135
  tft.setTextColor(ST7735_WHITE);
  tft.setTextSize(1);
  tft.print("Golongan");

  //tft.fillRect(70, 80, 40, 10, ST77XX_YELLOW); //(posisix, posisiy, panjangx, panjangy,warna);
  //tft.fillRect(70, 135, 40, 10, ST77XX_YELLOW); //(posisix, posisiy, panjangx, panjangy,warna);
  //tft.fillRect(20, 80, 40, 10, ST77XX_BLUE); //(posisix, posisiy, panjangx, panjangy,warna);
  //tft.fillRect(20, 135, 40, 10, ST77XX_BLUE); //(posisix, posisiy, panjangx, panjangy,warna);
}
