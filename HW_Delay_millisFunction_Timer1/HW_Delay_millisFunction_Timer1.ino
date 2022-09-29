unsigned long millisValue = 0;
unsigned long m, mc;
unsigned long startMillis, startMicros;
unsigned long elapseMillis, elapseMicros;
unsigned long microtime = 0;
char button = 'k', lastButton = 'b';


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(3, INPUT);
  TCCR1A = (0 << COM1A1) | (0 << COM1A0) | (0 << COM1B1) | (0 << COM1B0) | (0 << WGM11) | (0 << WGM10);
  TCCR1B = (0 << ICNC1) | (0 << ICES1) | (0 << WGM13) | (1 << WGM12) | (0 << CS12) | (0 << CS11) | (1 << CS10);
  TCNT1H = 0x00;
  TCNT1L = 0x00;
  OCR1AH = 0x3E;
  OCR1AL = 0x7F;

  TIMSK1 = (0 << ICIE1) | (0 << OCIE1B) | (1 << OCIE1A) | (1 << TOIE1);
  sei();
}

ISR(TIMER1_COMPA_vect) {
  TCNT1 = 0;
  millisValue++;
  //Serial.println(millisValue);
}

unsigned long myMillis() {
  cli();
  m = millisValue;
  sei();
  return m;
}

unsigned long myMicros() {
  unsigned long microsec = TCNT1;
  microtime = microtime + microsec;
  mc = microtime;
  return mc;
}

void loop() {
  button = Serial.read();
  delay(10);
  lastButton = 'a';
  while(button == 's' && lastButton != 's'){
    // put your main code here, to run repeatedly:
    unsigned long currentMicros = myMicros() / 4.096;
    elapseMicros = (currentMicros - startMicros);
    unsigned long currentMillis = myMillis();
    elapseMillis = (currentMillis - startMillis);

    unsigned long mmicros = (elapseMicros % 1000);
    unsigned long ms = (elapseMillis % 1000);
    unsigned long sec = (elapseMillis / 1000) % 60;
    unsigned long mmin = (elapseMillis / (60000)) % 60;
    unsigned long hhour = (elapseMillis / (3600000));
    hhour = hhour % 24;

    Serial.print(hhour);
    Serial.print(":");
    Serial.print(mmin);
    Serial.print(":");
    Serial.print(sec);
    Serial.print(":");
    Serial.print(ms);
    Serial.print(":");
    Serial.println(mmicros);
    lastButton = Serial.read();
  }
  
  //Serial.println((TCNT1/4096));
}
