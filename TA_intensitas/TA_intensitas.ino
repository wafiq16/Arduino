#define pin_LDR A3
#define pin_LED 12

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
//  pinMode(pin_LDR, INPUT);
  pinMode(pin_LED, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  int sensor = analogRead(pin_LDR);
  digitalWrite(pin_LED, HIGH);
  Serial.println(sensor);
  delay(1000);
}

//adc value
//red 983 10 tets 50 ml
//green 985 1 tetes 80 ml
//blue 985 1 tetes 80 ml
