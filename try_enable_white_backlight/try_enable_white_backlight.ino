#define pin_sw 3
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(pin_sw, INPUT_PULLUP);
}

void loop() {
  // put your main code here, to run repeatedly:
  int a = digitalRead(pin_sw);
  // active high
  Serial.println(a);
}
