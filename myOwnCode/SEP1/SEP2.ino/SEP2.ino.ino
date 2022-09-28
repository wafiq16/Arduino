int PIN_SWITCH = 5;
byte i;
void setup() {
  // put your setup code here, to run once:
  pinMode(PIN_SWITCH,INPUT_PULLUP);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  
  if(digitalRead(PIN_SWITCH)==LOW){
    delay(10);
    if(digitalRead(PIN_SWITCH)==LOW){
      i++;
      pinMode(PIN_SWITCH,OUTPUT);
      digitalWrite(PIN_SWITCH,LOW);
      Serial.println(i);
      digitalWrite(PIN_SWITCH,HIGH);
      delay(500);
      digitalWrite(PIN_SWITCH,LOW);
      delay(500);
    }
   }
}
