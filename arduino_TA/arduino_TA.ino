#include <FastLED.h>

#define LED_PIN     5
#define POT_PIN     A0
#define SW_PIN      3
#define NUM_LEDS    10
#define BRIGHTNESS  255
#define LED_TYPE    WS2812
#define COLOR_ORDER GRB
CRGB leds[NUM_LEDS];

#define UPDATES_PER_SECOND 100

CRGBPalette16 currentPalette;
TBlendType    currentBlending;

extern CRGBPalette16 myRedWhiteBluePalette;
extern const TProgmemPalette16 myRedWhiteBluePalette_p PROGMEM;

int colorIndex = 0;
int lowBoundary = 50;
int highBoundary = 100;

void setup() {
    
    delay( 3000 ); // power-up safety delay
    Serial.begin(9600);
    FastLED.addLeds<LED_TYPE, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection( TypicalLEDStrip );
    FastLED.setBrightness(  BRIGHTNESS );
    
    currentPalette = RainbowColors_p;
    currentBlending = LINEARBLEND;

    pinMode(POT_PIN, INPUT_PULLUP);
    pinMode(SW_PIN, INPUT_PULLUP);
//    pinMode(LED_PIN, OUTPUT);
  
}


void loop()
{
    if(analogRead(POT_PIN)<lowBoundary){
      lowBoundary = analogRead(POT_PIN);
    }
    if(analogRead(POT_PIN)>highBoundary){
      highBoundary = analogRead(POT_PIN);
    }
    if(digitalRead(SW_PIN)){
      for( int i = 0; i < NUM_LEDS; i++) {
        leds[i] = CHSV(0, 0,255);
      }
    }
    else{
      Serial.print(" high = ");
      Serial.println(highBoundary);
      Serial.print(" Low = ");
      Serial.println(lowBoundary);
      colorIndex = analogRead(POT_PIN);
      float temp = float(colorIndex+1)/float(highBoundary-lowBoundary);
    
      float ledData = temp*256;
      if(ledData > 247.0) ledData = 247.0;
      if(ledData < 0.0) ledData = 0.0;
      Serial.println(ledData);
      FillLEDsFromPaletteColors((int)ledData);
    }
    FastLED.show();
    FastLED.delay(100 / UPDATES_PER_SECOND);
}

void FillLEDsFromPaletteColors( int colorIndex)
{   
    for( int i = 0; i < NUM_LEDS; i++) {
      leds[i] = CHSV(colorIndex, 255 ,255);
    }
}
