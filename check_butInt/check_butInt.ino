#include <Arduino.h>
#include <TM1637Display.h>

// Module connection pins (Digital Pins)
#define CLK 9
#define DIO 10

// The amount of time (in milliseconds) between tests
#define TEST_DELAY   2000

TM1637Display display(CLK, DIO);

#define Button_Interupt 2

#define Button_Juri_Standby 3
#define Button_Juri_Acc 4
#define Button_Juri_No 5

#define Button_Tim_A 6
#define Button_Tim_B 7
#define Button_Tim_C 8

bool siap = false;
bool tampil_nilai = false;
bool tim_a_jawab = false;
bool tim_b_jawab = false;
bool tim_c_jawab = false;
bool kesempatan_jawab_a = true;
bool kesempatan_jawab_b = true;
bool kesempatan_jawab_c = true;
//bool kesempatan_jawab = true;
//bool a, b, c;

int nilai_tim_a = 0;
int nilai_tim_b = 0;
int nilai_tim_c = 0;
int count_siap = 0;

void setup() {
  // put your setup code here, to run once:
  //  pinMode(Button_Juri_Acc, INPUT);
  delay(3000);
  Serial.begin(9600);
  pinMode(Button_Juri_Acc, INPUT_PULLUP);
  pinMode(Button_Juri_No, INPUT_PULLUP);
  pinMode(Button_Tim_A, INPUT_PULLUP);
  pinMode(Button_Tim_B, INPUT_PULLUP);
  pinMode(Button_Tim_C, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(Button_Interupt), IT_HANDLER, RISING);

}

void loop() {
  // put your main code here, to run repeatedly:
  //  display.setBrightness(0x0f);
  //  delay(TEST_DELAY);
  //  display.clear();
  //  display.showNumberHexEx(0xA, 0, true, 1); // Expect: A___
  //  display.showNumberDec(14, false, 2, 2); // Expect: __14
  //  delay(TEST_DELAY);
  //  if (siap) {
  //    if (a) {
  //      tim_a_jawab = true;
  //      Serial.println("TIM A MENEKA TOMBOL");
  //      //      kesempatan_jawab_a = false;
  //      //      kesempatan_jawab_b = false;
  //      //      kesempatan_jawab_c = false;
  //    }
  //    else if (b) {
  //      tim_b_jawab = true;
  //      Serial.println("TIM B MENEKA TOMBOL");
  //      //      kesempatan_jawab_a = false;
  //      //      kesempatan_jawab_b = false;
  //      //      kesempatan_jawab_c = false;
  //    }
  //    else if (c) {
  //      tim_c_jawab = true;
  //      Serial.println("TIM C MENEKA TOMBOL");
  //      //      kesempatan_jawab_a = false;
  //      //      kesempatan_jawab_b = false;
  //      //      kesempatan_jawab_c = false;
  //    }
  //
  //    if (tim_a_jawab && kesempatan_jawab_a) {
  //      //      tampilkan nama team dan score
  //      Serial.println("KESEMPATAN MENJAWAB TIM A");
  //      int benar = digitalRead(Button_Juri_Acc);
  //      delay(50);
  //      int salah = digitalRead(Button_Juri_No);
  //      delay(50);
  //      if (benar && !salah) {
  //        nilai_tim_a += 2;
  //        Serial.println("JAWABAN BENAR TIM A");
  //        tim_a_jawab = false;
  //        //        tampilkan nilainya 1 detik
  //        //        kesempatan_jawab_a = false;
  //        display.clear();
  //        display.showNumberHexEx(0xA, 0, true, 1); // Expect: A___
  //        display.showNumberDec(nilai_tim_a, false, 2, 2); // Expect: __14
  //        delay(TEST_DELAY);
  //        display.clear();
  //      }
  //      else if (salah && !benar) {
  //        nilai_tim_a -= 1;
  //        //        tampilkan nilainya 1 detik
  //        Serial.println("JAWABAN SALAH TIM A");
  //        kesempatan_jawab_a = false;
  //        tim_a_jawab = false;
  //        display.clear();
  //        display.showNumberHexEx(0xA, 0, true, 1); // Expect: A___
  //        display.showNumberDec(nilai_tim_a, false, 2, 2); // Expect: __14
  //        delay(TEST_DELAY);
  //        display.clear();
  //
  //        if (kesempatan_jawab_b && kesempatan_jawab_c) {
  //          Serial.println("B dan C");
  //          display.clear();
  //          display.showNumberHexEx(0xBC, 2, true, 2); // Expect: A___
  //          //          display.showNumberHexEx(0xC, 3, true, 1); // Expect: A___
  //          delay(TEST_DELAY);
  //          display.clear();
  //        }
  //
  //        else if (kesempatan_jawab_b) {
  //          Serial.println("cuma B");
  //          display.clear();
  //          display.showNumberHexEx(0xB, 0, true, 1); // Expect: A___
  //          //          display.showNumberHexEx(0xC, 0, true, 3); // Expect: A___
  //          delay(TEST_DELAY);
  //          display.clear();
  //        }
  //
  //        else if (kesempatan_jawab_c) {
  //          Serial.println("cuma C");
  //          display.clear();
  //          display.showNumberHexEx(0xC, 0, true, 1); // Expect: A___
  //          //          display.showNumberHexEx(0xC, 0, true, 3); // Expect: A___
  //          delay(TEST_DELAY);
  //          display.clear();
  //        }
  //
  //
  //      }
  //
  //      //      kesempatan_jawab_b = false;
  //      //      kesempatan_jawab_c = false;
  //    }
  //
  //    else if (tim_b_jawab && kesempatan_jawab_b) {
  //      //      tampilkan nama team dan score
  //      Serial.println("KESEMPATAN MENJAWAB TIM B");
  //      int benar = digitalRead(Button_Juri_Acc);
  //      delay(30);
  //      int salah = digitalRead(Button_Juri_No);
  //      delay(30);
  //      if (benar && !salah) {
  //        nilai_tim_b += 2;
  //        Serial.println("JAWABAN BENAR TIM B");
  //        //        tampilkan nilainya 1 detik
  //        //        kesempatan_jawab_b = false;
  //        tim_b_jawab = false;
  //        display.clear();
  //        display.showNumberHexEx(0xB, 0, true, 1); // Expect: A___
  //        display.showNumberDec(nilai_tim_b, false, 2, 2); // Expect: __14
  //        delay(TEST_DELAY);
  //        display.clear();
  //      }
  //      else if (salah && !benar) {
  //        nilai_tim_b -= 1;
  //        Serial.println("JAWABAN SALAH TIM B");
  //        tim_b_jawab = false;
  //        kesempatan_jawab_b = false;
  //        //        tampilkan nilainya 1 detik
  //        display.clear();
  //        display.showNumberHexEx(0xB, 0, true, 1); // Expect: A___
  //        display.showNumberDec(nilai_tim_b, false, 2, 2); // Expect: __14
  //        delay(TEST_DELAY);
  //        display.clear();
  //
  //        if (kesempatan_jawab_a && kesempatan_jawab_c) {
  //          display.clear();
  //          display.showNumberHexEx(0xAC, 2, true, 2); // Expect: A___
  //          //          display.showNumberHexEx(0xC, 0, true, 3); // Expect: A___
  //          delay(TEST_DELAY);
  //          display.clear();
  //        }
  //
  //        else if (kesempatan_jawab_a) {
  //          display.clear();
  //          display.showNumberHexEx(0xA, 0, true, 1); // Expect: A___
  //          //          display.showNumberHexEx(0xC, 0, true, 3); // Expect: A___
  //          delay(TEST_DELAY);
  //          display.clear();
  //        }
  //
  //        else if (kesempatan_jawab_c) {
  //          display.clear();
  //          display.showNumberHexEx(0xC, 0, true, 1); // Expect: A___
  //          //          display.showNumberHexEx(0xC, 0, true, 3); // Expect: A___
  //          delay(TEST_DELAY);
  //          display.clear();
  //        }
  //
  //
  //      }
  //      //      kesempatan_jawab_a = false;
  //
  //      //      kesempatan_jawab_c = false;
  //    }
  //
  //    else if (tim_c_jawab && kesempatan_jawab_c) {
  //      //      tampilkan nama team dan score 2 detik
  //      Serial.println("KESEMPATAN MENJAWAB TIM C");
  //      int benar = digitalRead(Button_Juri_Acc);
  //      delay(30);
  //      int salah = digitalRead(Button_Juri_No);
  //      delay(30);
  //      if (benar && !salah) {
  //        nilai_tim_c += 2;
  //        //        tampilkan nilainya 1 detik
  //        Serial.println("JAWABAN BENAR TIM C");
  //        tim_c_jawab = false;
  //        display.clear();
  //        display.showNumberHexEx(0xC, 0, true, 1); // Expect: A___
  //        display.showNumberDec(nilai_tim_c, false, 2, 2); // Expect: __14
  //        delay(TEST_DELAY);
  //        display.clear();
  //      }
  //      else if (salah && !benar) {
  //        nilai_tim_c -= 1;
  //        Serial.println("JAWABAN SALAH TIM C");
  //        //        tampilkan nilainya 1 detik
  //        kesempatan_jawab_c = false;
  //        tim_c_jawab = false;
  //        display.clear();
  //        display.showNumberHexEx(0xC, 0, true, 1); // Expect: A___
  //        display.showNumberDec(nilai_tim_c, false, 2, 2); // Expect: __14
  //        delay(TEST_DELAY);
  //        display.clear();
  //
  //        if (kesempatan_jawab_a && kesempatan_jawab_b) {
  //          display.clear();
  //          display.showNumberHexEx(0xBA, 2, true, 2); // Expect: A___
  //          //          display.showNumberHexEx(0xC, 0, true, 3); // Expect: ___A
  //          delay(TEST_DELAY);
  //          display.clear();
  //        }
  //
  //        else if (kesempatan_jawab_b) {
  //          display.clear();
  //          display.showNumberHexEx(0xB, 0, true, 1); // Expect: A___
  //          //          display.showNumberHexEx(0xC, 0, true, 3); // Expect: ___A
  //          delay(TEST_DELAY);
  //          display.clear();
  //        }
  //
  //        else if (kesempatan_jawab_a) {
  //          display.clear();
  //          display.showNumberHexEx(0xA, 0, true, 1); // Expect: A___
  //          //          display.showNumberHexEx(0xC, 0, true, 3); // Expect: ___A
  //          delay(TEST_DELAY);
  //          display.clear();
  //        }
  //
  //
  //      }
  //    }
  //  }

  //  else {
  //    setting tampilan sevent segment
  //    Serial.println("MODE MENAMPILKAN SEVEN SEGMENT SELURUH TIM");
  //    display.clear();
  //    display.showNumberHexEx(0xA, 0, true, 1); // Expect: A___
  //    display.showNumberDec(nilai_tim_a, false, 2, 2); // Expect: __14
  //    delay(TEST_DELAY);
  //    display.clear();
  //    display.clear();
  //    display.showNumberHexEx(0xB, 0, true, 1); // Expect: A___
  //    display.showNumberDec(nilai_tim_b, false, 2, 2); // Expect: __14
  //    delay(TEST_DELAY);
  //    display.clear();
  //    display.clear();
  //    display.showNumberHexEx(0xC, 0, true, 1); // Expect: A___
  //    display.showNumberDec(nilai_tim_c, false, 2, 2); // Expect: __14
  //    delay(TEST_DELAY);
  //    display.clear();
  //    siap = true;
  //  }
  bool a = digitalRead(Button_Tim_A);
  delay(50);
  bool b = digitalRead(Button_Tim_B);
  delay(50);
  bool c = digitalRead(Button_Tim_C);
  delay(50);
  Serial.println("a = " + String(a));
  Serial.println("b = " + String(b));
  Serial.println("c = " +  String(c));
}

void IT_HANDLER() {
  //  delay(2000);
  //  count_siap++;
  //  Serial.println(count_siap);
  //  if (count_siap % 2 == 1) {
  //    siap = true;
  //    Serial.println("STANBY MODE ACTIVATED");
  //    kesempatan_jawab_a = true;
  //    kesempatan_jawab_b = true;
  //    kesempatan_jawab_c = true;
  //    tim_a_jawab = false;
  //    tim_b_jawab = false;
  //    tim_c_jawab = false;
  //  }
  //  else {
  //    siap = false;
  //    Serial.println("SHOW MODE");
  //  }
//  Serial.println("SIAP");
//  bool a = digitalRead(Button_Tim_A);
//  delay(50);
//  bool b = digitalRead(Button_Tim_B);
//  delay(50);
//  bool c = digitalRead(Button_Tim_C);
//  delay(50);
////  Serial.println(a);
////  Serial.println(b);
////  Serial.println(c);
//  if (a && b && c) {
//
//  }
//  else if (a) {
//    tim_a_jawab = true;
//    Serial.println("TIM A MENEKA TOMBOL");
//    //      kesempatan_jawab_a = false;
//    //      kesempatan_jawab_b = false;
//    //      kesempatan_jawab_c = false;
//  }
//  else if (b) {
//    tim_b_jawab = true;
//    Serial.println("TIM B MENEKA TOMBOL");
//    //      kesempatan_jawab_a = false;
//    //      kesempatan_jawab_b = false;
//    //      kesempatan_jawab_c = false;
//  }
//  else if (c) {
//    tim_c_jawab = true;
//    Serial.println("TIM C MENEKA TOMBOL");
//    //      kesempatan_jawab_a = false;
//    //      kesempatan_jawab_b = false;
//    //      kesempatan_jawab_c = false;
//  }
  //  delay(100);
}
