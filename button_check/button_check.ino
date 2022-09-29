#define pin_but 3

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(pin_but, INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  int data = digitalRead(pin_but);
  delay(50);
  Serial.println(data);
  if(data){
    Serial.println("sudah benar");
    }
    else{
      Serial.println("salah");
      }
}
