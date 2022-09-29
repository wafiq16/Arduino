#define redButtonPin 6
#define greenButtonPin 7
#define blueButtonPin 8
#define whiteButtonPin 9

#include "String.h"
#include <Wire.h>
#include "Adafruit_TCS34725.h"

bool redLight = false;
bool greenLight = false;
bool blueLight = false;
bool whiteLight = false;

uint16_t r, g, b, c, colorTemp, lux;

char message[30];
/* Example code for the Adafruit TCS34725 breakout library */

/* Connect SCL    to analog 5
   Connect SDA    to analog 4
   Connect VDD    to 3.3V DC
   Connect GROUND to common ground */

/* Initialise with default values (int time = 2.4ms, gain = 1x) */
// Adafruit_TCS34725 tcs = Adafruit_TCS34725();

/* Initialise with specific int time and gain values */
Adafruit_TCS34725 tcs = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_614MS, TCS34725_GAIN_1X);

void setup(void) {
  Serial.begin(9600);

  if (tcs.begin()) {
    Serial.println("Found sensor");
  } else {
    Serial.println("No TCS34725 found ... check your connections");
    while (1);
  }

  pinMode(redButtonPin, INPUT_PULLUP);
  pinMode(greenButtonPin, INPUT_PULLUP);
  pinMode(blueButtonPin, INPUT_PULLUP);
  pinMode(whiteButtonPin, INPUT_PULLUP);

  // Now we're ready to get readings!
}

void loop(void) {
  getRGB();
  
  int a = digitalRead(redButtonPin);
  int b = digitalRead(greenButtonPin);
  int c = digitalRead(blueButtonPin);
  int d = digitalRead(whiteButtonPin);
  
//  delay(20);
  
  if (!a) {
    delay(10);
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
  if (!b) {
    delay(10);
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
  if (!c) {
    delay(10);
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
  if (!d) {
    delay(10);
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

void getRGB() {
  tcs.getRawData(&r, &g, &b, &c);
  // colorTemp = tcs.calculateColorTemperature(r, g, b);
  colorTemp = tcs.calculateColorTemperature_dn40(r, g, b, c);
  lux = tcs.calculateLux(r, g, b);

//  Serial.print("Color Temp: "); Serial.print((uint8_t)colorTemp, DEC); Serial.print(" K - ");
//  Serial.print("Lux: "); Serial.print((uint8_t)lux, DEC); Serial.print(" - ");
//  Serial.print("R: "); Serial.print((uint8_t)r, DEC); Serial.print(" ");
//  Serial.print("G: "); Serial.print((uint8_t)g, DEC); Serial.print(" ");
//  Serial.print("B: "); Serial.print((uint8_t)b, DEC); Serial.print(" ");
//  Serial.print("C: "); Serial.print((uint8_t)c, DEC); Serial.print(" ");
//  Serial.println(" ");

  int digitR = strlen(String((uint8_t)r).c_str());
  int digitG = strlen(String((uint8_t)g).c_str());
  int digitB = strlen(String((uint8_t)b).c_str());
  sprintf(message, "AR%d%dG%d%dB%d%dS", digitR, (uint8_t)r, digitG, (uint8_t)g , digitB, (uint8_t)b);
  Serial.println(message);  
//  Serial.println(strlen(String(r).c_str()));
}
