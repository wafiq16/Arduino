void setup() {
  // put your setup code here, to run once:
    // put your setup code here, to run once:
  // Crystal Oscillator division factor: 1
  //  WDTCSR = 1 << WDE | 1 << WDCE;
//  WDTCSR = 0;
  WDTCSR = 0x00;
//  WDTCSR= (0<<WDP3) | (1<<WDCE) | (0<<WDE) | (1<<WDP2) | (1<<WDP1) | (0<<WDP0);
  delay(3000);
  //  MCUSR= 0 ;
  //  WDTCSR |= _BV(WDCE) | _BV(WDE);
  //  WDTCSR = 0;
  WDTCSR=0;
  Serial.begin(9600);

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

  Serial.println("start");
  // Global enable interrupts
    sei();
//    WDTCSR = (1 << WDCE) | (0 << WDE);
  
//  WDTCSR=(0<<WDIF) | (0<<WDIE) | (0<<WDP3) | (0<<WDCE) | (1<<WDE) | (0<<WDP2) | (0<<WDP1) | (0<<WDP0);

//   WDTCSR= (0<<WDP3) | (1<<WDCE) | (1<<WDE) | (1<<WDP2) | (1<<WDP1) | (1<<WDP0);
  #pragma optsize-
  WDTCSR=(1<<WDCE) | (1<<WDE);
  WDTCSR=(0<<WDIF) | (1<<WDIE) | (0<<WDP3) | (0<<WDCE) | (1<<WDE) | (1<<WDP2) | (1<<WDP1) | (1<<WDP0);
  #ifdef _OPTIMIZE_SIZE_
  #pragma optsize+
  #endif
}

void loop() {
  // put your main code here, to run repeatedly:
//    WDTCSR = (0 << WDIF) | (0 << WDIE) | (0 << WDP3) | (1 << WDCE) | (1 << WDE) | (0 << WDP2) | (0 << WDP1) | (0 << WDP0);
//    WDTCSR = 1 << WDCE;
//    WDTCSR = (1 << WDCE) | (0 << WDE);
    WDTCSR = 0x00;
    //Set new watchdog timeout value to 1 second (WDP2 and WDP1 to 1) and enable interrupts instead of reset (WDIE to 1)
}

ISR(WDT_vect){
//  WDTCSR = ( << WDCE) | (1 << WDE);
}
