#define pin_pwm 5
int i = 0;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(pin_pwm, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  i++;// = Serial.read();
  //if(Serial.available()){
    analogWrite(pin_pwm, 150);
    Serial.println(i);
  //}
}
