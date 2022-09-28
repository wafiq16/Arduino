#define T_C 262
#define T_D 294
#define T_E 330
#define T_F 349
#define T_G 392
#define T_A 440
#define T_B 493

const int Buzz = A0;

void setup() {
  // initialize the serial communication:
  Serial.begin(9600);
  // initialize the ledPin as an output:
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(Buzz, OUTPUT);
}

void loop() {
  int myTone;
  
  // check if data has been sent from the computer:
  if (Serial.available() > 0) {
    // read the most recent byte (which will be from 0 to 255):
    myTone = Serial.read();
    // set the brightness of the LED:
  if(myTone == '1')
  {
    tone(Buzz,T_C);
    digitalWrite(LED_BUILTIN,HIGH);
    delay(1000);
  }

  else if(myTone == '2')
  {
    tone(Buzz,T_D);
    digitalWrite(LED_BUILTIN,HIGH);
    delay(1000);
  }

  else if(myTone == '3')
  {
    tone(Buzz,T_E);
    digitalWrite(LED_BUILTIN,HIGH);
    delay(1000);
  }

  else if(myTone == '4')
  {
    tone(Buzz,T_F);
    digitalWrite(LED_BUILTIN,HIGH);
    delay(1000);
  }

  else if(myTone == '5')
  {
    tone(Buzz,T_G);
    digitalWrite(LED_BUILTIN,HIGH);
    delay(1000);
  }

  else if(myTone == '6')
  {
    tone(Buzz,T_A);
    digitalWrite(LED_BUILTIN,HIGH);
    delay(1000);
  }

  else if(myTone == '7')
  {
    tone(Buzz,T_B);
    digitalWrite(LED_BUILTIN,HIGH);
    delay(1000);
  }

  else{
    noTone(Buzz);
    digitalWrite(LED_BUILTIN,LOW);
  }
  }
}
