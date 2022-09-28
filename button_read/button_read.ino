#define pinButton 3
bool flagStart = false;
bool lastButtonState = false;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(pinButton, INPUT_PULLUP);
}

void loop() {
  // put your main code here, to run repeatedly:
  int ad = digitalRead(pinButton);
  delay(10);
  if (!ad) {
    delay(10);
    if(lastButtonState != ad){
      delay(10);
      flagStart = !flagStart;
    }
    lastButtonState = !ad;
  }
  Serial.println(flagStart);
}
