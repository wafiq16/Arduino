#include <FastLED.h>

#define LED_PWM_SIDE    5
#define LED_ON_SIDE     6
#define LED_PWM_BOT     3
#define LED_ON_BOT      4
#define LED_SOURCE      7

#define NUM_LEDS    10
#define BRIGHTNESS  255
#define LED_TYPE    WS2812
#define COLOR_ORDER GRB

#include "String.h"
#include <Wire.h>
#include "Adafruit_TCS34725.h"

#define UPDATES_PER_SECOND 100000

CRGBPalette16 currentPalette;
TBlendType    currentBlending;

extern CRGBPalette16 myRedWhiteBluePalette;
extern const TProgmemPalette16 myRedWhiteBluePalette_p PROGMEM;

int colorIndex = 0;
int lowBoundary = 50;
int highBoundary = 100;

String bufferRx;
bool captureSerialRx = false;
bool completeSerialRx = false;

String strLTerima;
String strMTerima;
String strNTerima;
String strOTerima;
String strPTerima;

int LTerima;
int MTerima;
int NTerima;
int OTerima;
int PTerima;

uint16_t r, g, b, c, colorTemp, lux;

char message[30];
/* Example code for the Adafruit TCS34725 breakout library */

/* Connect SCL    to analog 5
   Connect SDA    to analog 4
   Connect VDD    to 3.3V DC
   Connect GROUND to common ground */

/* Initialise with default values (int time = 2.4ms, gain = 1x) */
Adafruit_TCS34725 tcs = Adafruit_TCS34725();

/* Initialise with specific int time and gain values */
//Adafruit_TCS34725 tcs = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_614MS, TCS34725_GAIN_1X);
CRGB leds[NUM_LEDS];
CRGB leds2[NUM_LEDS];


void setup() {

  delay( 3000 ); // power-up safety delay
  Serial.begin(9600);
  FastLED.addLeds<LED_TYPE, LED_PWM_BOT, COLOR_ORDER>(leds, NUM_LEDS).setCorrection( TypicalLEDStrip );
  FastLED2.addLeds<LED_TYPE, LED_PWM_SIDE, COLOR_ORDER>(leds2, NUM_LEDS).setCorrection( TypicalLEDStrip );
  FastLED.setBrightness(  BRIGHTNESS );
  FastLED2.setBrightness(  BRIGHTNESS );

  currentPalette = RainbowColors_p;
  currentBlending = LINEARBLEND;

  pinMode(LED_ON_SIDE, OUTPUT);
  pinMode(LED_ON_BOT, OUTPUT);
  pinMode(LED_SOURCE, OUTPUT);

  if (tcs.begin()) {
    Serial.println("Found sensor");
  } else {
    Serial.println("No TCS34725 found ... check your connections");
    //    while (1);
  }

  //  pinMode(redButtonPin, INPUT_PULLUP);
  //  pinMode(greenButtonPin, INPUT_PULLUP);
  //  pinMode(blueButtonPin, INPUT_PULLUP);
  //  pinMode(whiteButtonPin, INPUT_PULLUP);

}


void loop()
{
  getRGB();
  getData();
  //  if (analogRead(POT_PIN) < lowBoundary) {
  //    lowBoundary = analogRead(POT_PIN);
  //  }
  //  if (analogRead(POT_PIN) > highBoundary) {
  //    highBoundary = analogRead(POT_PIN);
  //  }
  //  int a = digitalRead(redButtonPin);
  //  int b = digitalRead(greenButtonPin);
  //  int c = digitalRead(blueButtonPin);
  //  int d = digitalRead(whiteButtonPin);

  //  delay(10);
  //  Serial.print("a = ");
  //  Serial.println(a);
  //  Serial.print("b = ");
  //  Serial.println(b);
  //  Serial.print("c = ");
  //  Serial.println(c);
  //  Serial.print("d = ");
  //  Serial.println(d);
  //  if (!a) {
  //    delay(10);
  //    redLight = !redLight;
  //    if (redLight) {
  //      //        digitalWrite(LED_BUILTIN, HIGH);
  //      Serial.println("led merah nyala");
  //      for ( int i = 0; i < NUM_LEDS; i++) {
  //
  //        leds[i] = CHSV(0, 100, 100);
  //      }
  //    }
  //    else {
  //      //        digitalWrite(LED_BUILTIN, LOW);
  //      Serial.println("led merah mati");
  //      for ( int i = 0; i < NUM_LEDS; i++) {
  //        leds[i] = CHSV(0, 0, 255);
  //      }
  //    }
  //  }
  //  else if (!b) {
  //    delay(10);
  //    greenLight = !greenLight;
  //    if (greenLight) {
  //      //        digitalWrite(LED_BUILTIN, HIGH);
  //      Serial.println("led hijau nyala");
  //      for ( int i = 0; i < NUM_LEDS; i++) {
  //        leds[i] = CHSV(120, 100, 100);
  //      }
  //    }
  //    else {
  //      //        digitalWrite(LED_BUILTIN, LOW);
  //      Serial.println("led hijau mati");
  //      for ( int i = 0; i < NUM_LEDS; i++) {
  //        leds[i] = CHSV(0, 0, 255);
  //      }
  //    }
  //  }
  //  else if (!c) {
  //    delay(10);
  //    blueLight = !blueLight;
  //    if (blueLight) {
  //      //        digitalWrite(LED_BUILTIN, HIGH);
  //      Serial.println("led biru nyala");
  //      for ( int i = 0; i < NUM_LEDS; i++) {
  //
  //        leds[i] = CHSV(240, 100, 100);
  //      }
  //    }
  //    else {
  //      //        digitalWrite(LED_BUILTIN, LOW);
  //      Serial.println("led biru mati");
  //      for ( int i = 0; i < NUM_LEDS; i++) {
  //        leds[i] = CHSV(0, 0, 255);
  //      }
  //    }
  //  }
  //  else if (!d) {
  //    delay(10);
  //    whiteLight = !whiteLight;
  //    if (whiteLight) {
  //      //        digitalWrite(LED_BUILTIN, HIGH);
  //      Serial.println("led putih nyala");
  //      for ( int i = 0; i < NUM_LEDS; i++) {
  //        leds[i] = CHSV(0, 0, 255);
  //      }
  //    }
  //    else {
  //      //        digitalWrite(LED_BUILTIN, LOW);
  //      Serial.println("led putih mati");
  //      for ( int i = 0; i < NUM_LEDS; i++) {
  //        leds[i] = CHSV(0, 0, 255);
  //      }
  //    }
  //  }
  //  else if(!whiteLight && !redLight && !greenLight && !blueLight){

  if (MTerima == 1) {
    digitalWrite(LED_ON_SIDE, HIGH);
    for ( int i = 0; i < NUM_LEDS; i++) {
      leds2[i] = CHSV(NTerima, 255 , 255);
    }
  }
  else if (MTerima == 0) {
    digitalWrite(LED_ON_SIDE, LOW);
  }
  else {
    digitalWrite(LED_ON_SIDE, HIGH);
    for ( int i = 0; i < NUM_LEDS; i++) {
      leds2[i] = CHSV(0, 0, 255);
    }
  }
  if (OTerima == 1) {
    digitalWrite(LED_ON_BOT, HIGH);
    for ( int i = 0; i < NUM_LEDS; i++) {
      leds[i] = CHSV(PTerima, 255 , 255);
    }
  }
  else if (OTerima == 0) {
    digitalWrite(LED_ON_BOT, LOW);
  }
  else {
    digitalWrite(LED_ON_BOT, HIGH);
    for ( int i = 0; i < NUM_LEDS; i++) {
      leds[i] = CHSV(0, 0, 255);
    }
  }
  if (LTerima == 1) {
    digitalWrite(LED_SOURCE, HIGH);
  }
  else if (LTerima == 0) {
    digitalWrite(LED_SOURCE, LOW);
  }
  //  Serial.print(LTerima);
  //  Serial.print(MTerima);
  //  Serial.print(NTerima);
  //  Serial.print(OTerima);
  //  Serial.print(PTerima);
  FastLED.show();
  FastLED.delay(100 / UPDATES_PER_SECOND);

  FastLED2.show();
  FastLED2.delay(100 / UPDATES_PER_SECOND);
}


void getRGB() {
  tcs.getRawData(&r, &g, &b, &c);
  //   colorTemp = tcs.calculateColorTemperature(r, g, b);
  colorTemp = tcs.calculateColorTemperature_dn40(r, g, b, c);
  lux = tcs.calculateLux(r, g, b);

  //  Serial.print("Color Temp: "); Serial.print((uint8_t)colorTemp, DEC); Serial.print(" K - ");
  //  Serial.print("Lux: "); Serial.print((uint8_t)lux, DEC); Serial.print(" - ");
  //  Serial.print("R: "); Serial.print((uint8_t)r, DEC); Serial.print(" ");
  //  Serial.print("G: "); Serial.print((uint8_t)g, DEC); Serial.print(" ");
  //  Serial.print("B: "); Serial.print((uint8_t)b, DEC); Serial.print(" ");
  //  Serial.print("C: "); Serial.print((uint8_t)c, DEC); Serial.print(" ");
  //  Serial.println(" ");
  uint16_t sum = c;
  float red, green, blue;

  red = r;
  red /= sum;

  green = g;
  green /= sum;

  blue = b;
  blue /= sum;

  red *= 256; green *= 256; blue *= 256;

  int digitR = strlen(String((int)red).c_str());
  int digitG = strlen(String((int)green).c_str());
  int digitB = strlen(String((int)blue).c_str());
  sprintf(message, "AR%d%dG%d%dB%d%dS", digitR, (int)red, digitG, (int)green , digitB, (int)blue);
  Serial.println(message);
  //  Serial.println(strlen(String(r).c_str()));
}

void getData() {
  if (Serial.available()) {
    char rxChar = Serial.read();

    if (rxChar == 'A' && !captureSerialRx) captureSerialRx = true;
    else if (rxChar == 'B' && captureSerialRx) {
      captureSerialRx = false;
      completeSerialRx = true;
      strLTerima = "";
      strMTerima = "";
      strNTerima = "";
      strOTerima = "";
      strPTerima = "";
    }

    if (captureSerialRx) {
      bufferRx += rxChar;
    }

    if (completeSerialRx) {
      for (int i = 0; i < strlen(bufferRx.c_str()); i++) {
        if (bufferRx.charAt(i) == 'L') {
          int digit = bufferRx.charAt(i + 1) - 48;
          for (int j = 2; j <= digit + 1; j++) {
            strLTerima += bufferRx.charAt(i + j);
          }
        }
        if (bufferRx.charAt(i) == 'M') {
          int digit = bufferRx.charAt(i + 1) - 48;
          for (int j = 2; j <= digit + 1; j++) {
            strMTerima += bufferRx.charAt(i + j);
          }
        }
        if (bufferRx.charAt(i) == 'N') {
          int digit = bufferRx.charAt(i + 1) - 48;
          for (int j = 2; j <= digit + 1; j++) {
            strNTerima += bufferRx.charAt(i + j);
          }
        }
        if (bufferRx.charAt(i) == 'O') {
          int digit = bufferRx.charAt(i + 1) - 48;
          for (int j = 2; j <= digit + 1; j++) {
            strOTerima += bufferRx.charAt(i + j);
          }
        }
        if (bufferRx.charAt(i) == 'P') {
          int digit = bufferRx.charAt(i + 1) - 48;
          for (int j = 2; j <= digit + 1; j++) {
            strPTerima += bufferRx.charAt(i + j);
          }
        }
      }
      bufferRx = "";
      completeSerialRx = false;
      //      Serial.println(strLTerima);
      //      Serial.println(strMTerima);
      //      Serial.println(strNTerima);
      //      Serial.println(strOTerima);
      //      Serial.println(strPTerima);
      LTerima = strLTerima.toInt();
      MTerima = strMTerima.toInt();
      NTerima = strNTerima.toInt();
      OTerima = strOTerima.toInt();
      PTerima = strPTerima.toInt();
    }
  }
}
