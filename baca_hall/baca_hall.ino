#define pinHall 13//78
void setup() {
  // put your setup code here, to run once:
  delay(3000);
  Serial.begin(9600);
  Serial.println("Dallas Temperature IC Control Library Demo");
//  pinMode(pinRelay, OUTPUT);
  pinMode(pinHall, INPUT_PULLUP);
}

void loop() {
  // put your main code here, to run repeatedly:
  int a = digitalRead(pinHall);
  Serial.println(a);
}
