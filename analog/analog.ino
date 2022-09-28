#define pin A0
int adc = 0;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(pin, INPUT_PULLUP);
}

void loop() {
  // put your main code here, to run repeatedly:
  adc = analogRead(pin);
  Serial.println(adc);
  delay(100);
}
