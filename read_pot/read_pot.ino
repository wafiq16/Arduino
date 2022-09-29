#define pin_pot A0
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(pin_pot, INPUT_PULLUP);
}

void loop() {
  // put your main code here, to run repeatedly:
  int data = analogRead(pin_pot);
  Serial.println(data);
}
