
// Timer 8 kHz
long myTick = 0, sec = 0, hour = 0, minu = 0, ms10;
bool start = false;
int button = 2;
int buttonP = 5;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  pinMode(button, INPUT_PULLUP);
  pinMode(buttonP, INPUT_PULLUP);
}

void loop() {
  // put your main code here, to run repeatedly:
  char p;

  if(!digitalRead(button)){
//    delay(10);
    if(start == false)
    {
     Serial.println("STOPWATCH STARTED");
     delay(500);
     TCCR1A = 0x00;
     TCCR1B = 0x03;
     start = true;
    }
    else{
     start = false;
     Serial.println("STOPWATCH ENDED");
     delay(500);
     TCCR1A = 0;
     TCCR1B = 0;
     TCNT1 = 0;
     ms10 = 0;
     sec = 0;
     minu = 0;
     hour = 0;
    }
  }
//  Serial.print(TCNT1);
  if(!digitalRead(buttonP)){
   if(start == false)
    {
     Serial.println("STOPWATCH STARTED");
     delay(500);
     TCCR1A = 0x00;
     TCCR1B = 0x03;
     start = true;
     p = 'A';
    }
    else{
     start = false;
     Serial.println("STOPWATCH PAUSED");
     delay(500);
     TCCR1A = 0;
     TCCR1B = 0;
     TCNT1 = 0;
      p = 'A';
    }
   }
//   Serial.print(" ");
//   Serial.print(TCNT1);
//   Serial.print("\n");
//  micros
  myTick = TCNT1;
  if(myTick >= 2480){
    TCNT1 = 0;
    ms10++;
    if(ms10 == 100){
      ms10 = 0;
      sec++;
      if(sec == 60){
        minu++;
        sec = 0;
        if(minu == 60){
          hour++;
          minu = 0;
          }
        }
      }
//      Serial.println(TCNT1);
      Serial.print(hour); Serial.print(":");
      Serial.print(minu); Serial.print(":");
      Serial.print(sec); Serial.print(",");
      Serial.print(ms10);
      Serial.print("\n");
    }
//      delay(10);
//      p = Serial.read();
//      delay(10);
  
  
}
