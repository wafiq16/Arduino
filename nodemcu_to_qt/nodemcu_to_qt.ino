#include <Wire.h>
#include "Adafruit_TCS34725.h"

#define redButtonPin 6
#define greenButtonPin 7
#define blueButtonPin 8
#define whiteButtonPin 9

bool redLight = false;
bool greenLight = false;
bool blueLight = false;
bool whiteLight = false;

uint16_t r, g, b, c, colorTemp, lux;

/* Example code for the Adafruit TCS34725 breakout library */

/* Connect SCL    to analog 5
   Connect SDA    to analog 4
   Connect VDD    to 3.3V DC
   Connect GROUND to common ground */

/* Initialise with default values (int time = 2.4ms, gain = 1x) */
// Adafruit_TCS34725 tcs = Adafruit_TCS34725();

/* Initialise with specific int time and gain values */
Adafruit_TCS34725 tcs = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_614MS, TCS34725_GAIN_1X);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  
  pinMode(redButtonPin, INPUT_PULLUP);
  pinMode(greenButtonPin, INPUT_PULLUP);
  pinMode(blueButtonPin, INPUT_PULLUP);
  pinMode(whiteButtonPin, INPUT_PULLUP);

  if (tcs.begin()) {
    Serial.println("Found sensor");
  } else {
    Serial.println("No TCS34725 found ... check your connections");
    while (1);
  }
}

void loop() {
  // put your main code here, to run repeatedly:
  getRGBData();
  int a = digitalRead(redButtonPin);
  int b = digitalRead(greenButtonPin);
  int c = digitalRead(blueButtonPin);
  int d = digitalRead(whiteButtonPin);
  delay(100);
  //  Serial.print("a = ");
  //  Serial.println(a);
  if (a) {
    delay(40);
    redLight = !redLight;
    if (redLight) {
      digitalWrite(LED_BUILTIN, HIGH);
      Serial.println("led merah nyala");
    }
    else {
      digitalWrite(LED_BUILTIN, LOW);
      Serial.println("led merah mati");
    }
  }
  if (b) {
    delay(40);
    greenLight = !greenLight;
    if (greenLight) {
      digitalWrite(LED_BUILTIN, HIGH);
      Serial.println("led hijau nyala");
    }
    else {
      digitalWrite(LED_BUILTIN, LOW);
      Serial.println("led hijau mati");
    }
  }
  if (c) {
    delay(40);
    blueLight = !blueLight;
    if (blueLight) {
      digitalWrite(LED_BUILTIN, HIGH);
      Serial.println("led biru nyala");
    }
    else {
      digitalWrite(LED_BUILTIN, LOW);
      Serial.println("led biru mati");
    }
  }
  if (d) {
    delay(40);
    whiteLight = !whiteLight;
    if (whiteLight) {
      digitalWrite(LED_BUILTIN, HIGH);
      Serial.println("led putih nyala");
    }
    else {
      digitalWrite(LED_BUILTIN, LOW);
      Serial.println("led putih mati");
    }
  }
}

void getRGBData(){
  tcs.getRawData(&r, &g, &b, &c);
  // colorTemp = tcs.calculateColorTemperature(r, g, b);
  colorTemp = tcs.calculateColorTemperature_dn40(r, g, b, c);
  lux = tcs.calculateLux(r, g, b);

  Serial.print("Color Temp: "); Serial.print((uint8_t)colorTemp, DEC); Serial.print(" K - ");
  Serial.print("Lux: "); Serial.print((uint8_t)lux, DEC); Serial.print(" - ");
  Serial.print("R: "); Serial.print((uint8_t)r, DEC); Serial.print(" ");
  Serial.print("G: "); Serial.print((uint8_t)g, DEC); Serial.print(" ");
  Serial.print("B: "); Serial.print((uint8_t)b, DEC); Serial.print(" ");
  Serial.print("C: "); Serial.print((uint8_t)c, DEC); Serial.print(" ");
  Serial.println(" ");
  }
