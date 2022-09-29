#define PWM_A 9
#define PWM_B 10
int myCount = 0;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  pinMode(PWM_A, OUTPUT);
  pinMode(PWM_B, OUTPUT);
TCCR1A=(1<<COM1A1) | (1<<COM1A0) | (1<<COM1B1) | (1<<COM1B0) | (1<<WGM11) | (0<<WGM10);
TCCR1B=(0<<ICNC1) | (0<<ICES1) | (1<<WGM13) | (1<<WGM12) | (0<<CS12) | (1<<CS11) | (0<<CS10);
TCNT1H=0x00;
TCNT1L=0x00;
ICR1H=0x07;
ICR1L=0xCF;
OCR1AH=0x00;
OCR1AL=0x00;
OCR1BH=0x07;
OCR1BL=0xCF;
}

void loop() {
  // put your main code here, to run repeatedly:
//  for(int i=0; i<= 1999; i+=3){
//    OCR1A = i;
//    OCR1B = 1999 - i;
//    Serial.println(OCR1A); 
//    Serial.println(OCR1B); 
//  }
//  for(int i=1999; i >= 0; i-=3){
//    OCR1A = i;
//    OCR1B = 1999 - i;
//    Serial.println(OCR1A);
//    Serial.println(OCR1B);   
//  }
    OCR1A = myCount;
    OCR1B = myCount;
    Serial.println(myCount);
  Serial.println(OCR1A);
  Serial.println(OCR1B);
  char myChar = Serial.read();
  if(Serial.available()){
    if(myChar == 'u'){
//          for(int i=0; i<= 1999; i+=3){
//      OCR1A = i;
//      OCR1B = 1999 - i;
//      Serial.println(OCR1A); 
//      Serial.println(OCR1B); 
//    }
      myCount = myCount + 100;
      }
    if(myChar == 'd'){
//          for(int i=1999; i >= 0; i-=3){
//    OCR1A = i;
//    OCR1B = 1999 - i;
//    Serial.println(OCR1A);
//    Serial.println(OCR1B);   
//  }
      myCount = myCount - 100;
      }
   }
//    OCR1A = 0;
//    OCR1B = 0;
}
