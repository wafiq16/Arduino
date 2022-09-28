long counter = 0;
int currentStateCLK = 0;
int lastStateCLK = 0;
String currentDir="";
void setup() {
//  Serial.begin(115200);
  // put your setup code here, to run once:
  // pinMode(5, INPUT);

  pinMode(4, INPUT_PULLUP);
  pinMode(3, INPUT_PULLUP);
    // pinMode(4, INPUT_PULLUP);
  pinMode(2, INPUT_PULLUP);
  CLKPR=(1<<CLKPCE);
  CLKPR=(0<<CLKPCE) | (0<<CLKPS3) | (0<<CLKPS2) | (0<<CLKPS1) | (0<<CLKPS0);

// Input/Output Ports initialization
// Port B initialization
// Function: Bit7=In Bit6=In Bit5=In Bit4=In Bit3=In Bit2=In Bit1=In Bit0=In 
DDRB=(0<<DDB7) | (0<<DDB6) | (0<<DDB5) | (0<<DDB4) | (0<<DDB3) | (0<<DDB2) | (0<<DDB1) | (0<<DDB0);
// State: Bit7=T Bit6=T Bit5=T Bit4=T Bit3=T Bit2=T Bit1=T Bit0=T 
PORTB=(0<<PORTB7) | (0<<PORTB6) | (0<<PORTB5) | (0<<PORTB4) | (0<<PORTB3) | (0<<PORTB2) | (0<<PORTB1) | (0<<PORTB0);

// Port C initialization
// Function: Bit6=In Bit5=In Bit4=In Bit3=In Bit2=In Bit1=In Bit0=In 
DDRC=(0<<DDC6) | (0<<DDC5) | (0<<DDC4) | (0<<DDC3) | (0<<DDC2) | (0<<DDC1) | (0<<DDC0);
// State: Bit6=T Bit5=T Bit4=T Bit3=T Bit2=T Bit1=T Bit0=T 
PORTC=(0<<PORTC6) | (0<<PORTC5) | (0<<PORTC4) | (0<<PORTC3) | (0<<PORTC2) | (0<<PORTC1) | (0<<PORTC0);

// Port D initialization
// Function: Bit7=In Bit6=In Bit5=In Bit4=In Bit3=In Bit2=In Bit1=In Bit0=In 
DDRD=(0<<DDD7) | (0<<DDD6) | (0<<DDD5) | (0<<DDD4) | (0<<DDD3) | (0<<DDD2) | (0<<DDD1) | (0<<DDD0);
// State: Bit7=T Bit6=T Bit5=T Bit4=T Bit3=T Bit2=T Bit1=T Bit0=T 
PORTD=(0<<PORTD7) | (0<<PORTD6) | (0<<PORTD5) | (0<<PORTD4) | (0<<PORTD3) | (0<<PORTD2) | (0<<PORTD1) | (0<<PORTD0);

//   // Timer/Counter 1 initialization
// // Clock source: System Clock
// // Clock value: 2000.000 kHz
// // Mode: Ph. & fr. cor. PWM top=ICR1
// // OC1A output: Disconnected
// // OC1B output: Disconnected
// // Noise Canceler: Off
// // Input Capture on Falling Edge
// // Timer Period: 0 us
// // Timer1 Overflow Interrupt: On
// // Input Capture Interrupt: Off
// // Compare A Match Interrupt: Off
// // Compare B Match Interrupt: Off
TCCR1A=(0<<COM1A1) | (0<<COM1A0) | (0<<COM1B1) | (0<<COM1B0) | (0<<WGM11) | (0<<WGM10);
TCCR1B=(0<<ICNC1) | (0<<ICES1) | (1<<WGM13) | (0<<WGM12) | (0<<CS12) | (1<<CS11) | (0<<CS10);
TCNT1=0xFF;
TCNT1L=0x00;
ICR1H=0x00;
ICR1L=0x00;
OCR1AH=0x00;
OCR1AL=0x00;
OCR1BH=0x00;
OCR1BL=0x00;

// // Timer/Counter 1 Interrupt(s) initialization
TIMSK1=(0<<ICIE1) | (0<<OCIE1B) | (0<<OCIE1A) | (1<<TOIE1);

// USART initialization
// Communication Parameters: 8 Data, 1 Stop, No Parity
// USART Receiver: On
// USART Transmitter: On
// USART0 Mode: Asynchronous
// USART Baud Rate: 9600
 UCSR0A=(0<<RXC0) | (0<<TXC0) | (0<<UDRE0) | (0<<FE0) | (0<<DOR0) | (0<<UPE0) | (0<<U2X0) | (0<<MPCM0);
 UCSR0B=(1<<RXCIE0) | (1<<TXCIE0) | (0<<UDRIE0) | (1<<RXEN0) | (1<<TXEN0) | (0<<UCSZ02) | (0<<RXB80) | (0<<TXB80);
 UCSR0C=(0<<UMSEL01) | (0<<UMSEL00) | (0<<UPM01) | (0<<UPM00) | (0<<USBS0) | (1<<UCSZ01) | (1<<UCSZ00) | (0<<UCPOL0);
 UBRR0H=0x00;
 UBRR0L=0x67;
sei();
}

void loop() {
  // put your main code here, to run repeatedly:
  // Serial.print("\n\r Ch A = ");
  // Serial.print(TCNT0);
  // Serial.println(counter);
  // int a = digitalRead(5);
  // delay(50);
}

// interrupt [TIM1_OVF] void timer1_ovf_isr(void)
// {
// // Place your code here

// }

ISR(TIMER1_OVF_vect)        // interrupt service routine that wraps a user defined function supplied by attachInterrupt
{
  TCNT1 = 0xFF;
    // pinMode(8, INPUT_PULLUP);
  // pinMode(9, INPUT_PULLUP);            // preload timer
  // digitalWrite(13, digitalRead(13) ^ 1);
  // Serial.println(a)
  // Serial.println(digitalRead(9));
  // delay(10);
  currentStateCLK = digitalRead(2);
  		// Serial.print("Direction: ");
		// Serial.print(currentDir);
	// If last and current state of CLK are different, then pulse occurred
	// React to only 1 state change to avoid double count
	if (currentStateCLK){

		// If the DT state is different than the CLK state then
		// the encoder is rotating CCW so decrement
		if (digitalRead(4)) {
			counter--;
      // count_down();
			currentDir ="CCW";
      // Serial.println("CCW");
		} else {
			// Encoder is rotating CW so increment
			counter = counter + 1;
      // count_up();
			currentDir ="CW";
      // Serial.println("CW");
		}

    lastStateCLK = currentStateCLK;

		Serial.print("Direction: ");
		Serial.print(currentDir);
		Serial.print(" | Counter: ");
		Serial.println(counter);
	}
}
