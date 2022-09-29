#include "DHT.h"

#define pin_dht 3
#define pin_buzzer 4
#define DHTTYPE DHT11

double T = 0.0;
double H = 0.0;

DHT dht(pin_dht, DHTTYPE);

void setup() {
  // put your setup code here, to run once:
  // Crystal Oscillator division factor: 1
  //  WDTCSR = 1 << WDE | 1 << WDCE;
//  WDTCSR = 0;
  delay(3000);
  //  MCUSR= 0 ;
  //  WDTCSR |= _BV(WDCE) | _BV(WDE);
  //  WDTCSR = 0;
  Serial.begin(9600);
  pinMode(pin_dht, INPUT_PULLUP);
  pinMode(pin_buzzer, OUTPUT);

  dht.begin();

  CLKPR = (1 << CLKPCE);
  CLKPR = (0 << CLKPCE) | (0 << CLKPS3) | (0 << CLKPS2) | (0 << CLKPS1) | (0 << CLKPS0);

  //  // Timer/Counter 1 initialization
  //  // Clock source: System Clock
  //  // Clock value: 16000.000 kHz
  //  // Mode: Normal top=0xFFFF
  //  // OC1A output: Disconnected
  //  // OC1B output: Disconnected
  //  // Noise Canceler: Off
  //  // Input Capture on Falling Edge
  //  // Timer Period: 4.096 ms
  //  // Timer1 Overflow Interrupt: Off
  //  // Input Capture Interrupt: Off
  //  // Compare A Match Interrupt: Off
  //  // Compare B Match Interrupt: Off
  //  TCCR1A = (0 << COM1A1) | (0 << COM1A0) | (0 << COM1B1) | (0 << COM1B0) | (0 << WGM11) | (0 << WGM10);
  //  TCCR1B = (0 << ICNC1) | (0 << ICES1) | (0 << WGM13) | (0 << WGM12) | (0 << CS12) | (0 << CS11) | (1 << CS10);
  //  TCNT1H = 0x00;
  //  TCNT1L = 0x00;
  //  ICR1H = 0x00;
  //  ICR1L = 0x00;
  //  OCR1AH = 0x00;
  //  OCR1AL = 0x00;
  //  OCR1BH = 0x00;
  //  OCR1BL = 0x00;

  // Timer/Counter 1 Interrupt(s) initialization
  TIMSK1 = (0 << ICIE1) | (0 << OCIE1B) | (0 << OCIE1A) | (0 << TOIE1);

  // External Interrupt(s) initialization
  // INT0: Off
  // INT1: On
  // INT1 Mode: Any change
  // Interrupt on any change on pins PCINT0-7: Off
  // Interrupt on any change on pins PCINT8-14: Off
  // Interrupt on any change on pins PCINT16-23: Off
  EICRA = (1 << ISC11) | (1 << ISC10) | (0 << ISC01) | (0 << ISC00);
  EIMSK = (1 << INT1) | (0 << INT0);
  EIFR = (1 << INTF1) | (0 << INTF0);
  PCICR = (0 << PCIE2) | (0 << PCIE1) | (0 << PCIE0);

  // ADC initialization
  // ADC disabled
  ADCSRA = (0 << ADEN) | (0 << ADSC) | (0 << ADATE) | (0 << ADIF) | (0 << ADIE) | (0 << ADPS2) | (0 << ADPS1) | (0 << ADPS0);

  // SPI initialization
  // SPI disabled
  SPCR = (0 << SPIE) | (0 << SPE) | (0 << DORD) | (0 << MSTR) | (0 << CPOL) | (0 << CPHA) | (0 << SPR1) | (0 << SPR0);

  // TWI initialization
  // TWI disabled
  TWCR = (0 << TWEA) | (0 << TWSTA) | (0 << TWSTO) | (0 << TWEN) | (0 << TWIE);
  WDTCSR = (0 << WDIF) | (0 << WDIE) | (0 << WDP3) | (1 << WDCE) | (1 << WDE) | (0 << WDP2) | (0 << WDP1) | (0 << WDP0);
  WDTCSR = 1 << WDP0 | 1 << WDP2;
  Serial.println("start");
  // Global enable interrupts
    sei();
}

void loop() {
  //(0 << WDIF) | (0 << WDIE) | (0 << WDP3) | (0 << WDCE) | (0 << WDE) | (0 << WDP2) | (0 << WDP1) | (0 << WDP0);
  //  cli();

  delay(2000);
  // put your main code here, to run repeatedly:
  float H = dht.readHumidity();
  // Read temperature as Celsius (the default)
  float T = dht.readTemperature();
  // Read temperature as Fahrenheit (isFahrenheit = true)
  //  float f = dht.readTemperature(true);

  if (T >= 30) {
    digitalWrite(pin_buzzer, HIGH);
    bool aws = digitalRead(5);

    if (aws == false) {
    // Watchdog Timer initialization
    // Watchdog Timer Prescaler: OSC/1024k
    // Watchdog timeout action: Reset
      Serial.println("wd jalax n");
      WDTCSR = (1 << WDIF) | (1 << WDIE) | (0 << WDP3) | (1 << WDCE) | (1 << WDE) | (1 << WDP2) | (0 << WDP1) | (1 << WDP0);
//      WDTCSR = 1 << WDP0 | 1 << WDP2;
    }
//    delay(1000);
//    sei();
  }
  else {
    digitalWrite(pin_buzzer, LOW);
  }
  Serial.println(T);
}

ISR (INT1_vect)
{
  
  //  cli();
  //  else {
  //      cli();
  //  }

}
