void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  pinMode(LED_BUILTIN, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  
  if(Serial.available()){
    char x = Serial.read();
    digitalWrite(HIGH, LED_BUILTIN);
    Serial.println(x); 
    }
    else{
      digitalWrite(LOW, LED_BUILTIN);
    }
    
}
