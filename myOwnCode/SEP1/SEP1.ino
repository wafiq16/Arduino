int var = 0;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(5,OUTPUT);
  pinMode(6,OUTPUT);
  pinMode(7,OUTPUT);
  pinMode(8,INPUT_PULLUP);
//  digitalWrite(13,HIGH);
//  DDRB = 0b00000000;
//  DDRB = 0b00001000;
//  DDRB = 1 << DDB5;
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(5,HIGH);
  delay(var);
  digitalWrite(6,HIGH);
  delay(var);
  digitalWrite(7,HIGH);
  delay(var);
  digitalWrite(5,LOW);
  digitalWrite(6,LOW);
  digitalWrite(7,LOW);
  delay(var);
  if(digitalRead(8) == LOW ){
    delay(10);
    if(digitalRead(8) == LOW){
      var++;
      Serial.println(var);
      }
      
    }
//  PORTB = PORTB | 0b00100000;
//  delay(1000);
//  PORTB = PORTB & 0b11011111;
//  delay(1000);

}
