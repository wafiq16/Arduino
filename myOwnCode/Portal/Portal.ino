int pin_sensor_jarak_trigger = 3;
int pin_sensor_jarak_echo = 2; 
int pin_sensor_ir = 6;
int servo_handSanitizer = 9;
int servo_palang = 5;
int nilai_sensor_ir = 0;
int nilai_sensor_jarak = 0;
double distance = 0;
double duration = 0;
void setup() {
  // put your setup code here, to run once:
  pinMode(pin_sensor_jarak_trigger, INPUT);
  pinMode(pin_sensor_jarak_echo, INPUT);
  pinMode(pin_sensor_ir, INPUT);
  pinMode(servo_palang, OUTPUT);
  pinMode(servo_handSanitizer, OUTPUT);
}

void loop() {
  nilai_sensor_ir = digitalRead(pin_sensor_ir);
//  nilai_sensor_jarak = analogRead(pin_sensor_jarak);
  sensorUltrasonic(pin_sensor_jarak_trigger ,pin_sensor_jarak_echo);
  
  if(nilai_sensor_ir == HIGH){
    analogWrite(servo_handSanitizer, HIGH);
  }
  else{
    analogWrite(servo_handSanitizer, LOW);
  }

  if(nilai_sensor_jarak == HIGH){
    analogWrite(servo_palang, HIGH);
  }
  else{
    analogWrite(servo_palang, LOW);
  }
  Serial.println("jarak = ");
  Serial.println(distance); 
  // put your main code here, to run repeatedly:

}

void sensorUltrasonic(double trigger, double echo){
    digitalWrite(trigger, LOW);
    delayMicroseconds(2);
    digitalWrite(trigger, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigger, LOW);
    duration = pulseIn(echo, HIGH);
    distance = (duration / 2)/29.1;
    delay(100); 
  }
