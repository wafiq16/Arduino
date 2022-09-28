#define redButtonPin 6
#define greenButtonPin 7
#define blueButtonPin 8
#define whiteButtonPin 9

bool redLight = false;
bool greenLight = false;
bool blueLight = false;
bool whiteLight = false;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(redButtonPin, INPUT_PULLUP);
  pinMode(greenButtonPin, INPUT_PULLUP);
  pinMode(blueButtonPin, INPUT_PULLUP);
  pinMode(whiteButtonPin, INPUT_PULLUP);
}

void loop() {
  // put your main code here, to run repeatedly:
  int a = digitalRead(redButtonPin);
  int b = digitalRead(greenButtonPin);
  int c = digitalRead(blueButtonPin);
  int d = digitalRead(whiteButtonPin);
  delay(100);
    Serial.print("a = ");
    Serial.println(a);
  if (a) {
    delay(40);
    redLight = !redLight;
    if (redLight) {
      digitalWrite(LED_BUILTIN, HIGH);
      Serial.println("led merah nyala");
    }
    else {
      digitalWrite(LED_BUILTIN, LOW);
      Serial.println("led merah mati");
    }
  }
  if (b) {
    delay(40);
    greenLight = !greenLight;
    if (greenLight) {
      digitalWrite(LED_BUILTIN, HIGH);
      Serial.println("led hijau nyala");
    }
    else {
      digitalWrite(LED_BUILTIN, LOW);
      Serial.println("led hijau mati");
    }
  }
  if (c) {
    delay(40);
    blueLight = !blueLight;
    if (blueLight) {
      digitalWrite(LED_BUILTIN, HIGH);
      Serial.println("led biru nyala");
    }
    else {
      digitalWrite(LED_BUILTIN, LOW);
      Serial.println("led biru mati");
    }
  }
  if (d) {
    delay(40);
    whiteLight = !whiteLight;
    if (whiteLight) {
      digitalWrite(LED_BUILTIN, HIGH);
      Serial.println("led putih nyala");
    }
    else {
      digitalWrite(LED_BUILTIN, LOW);
      Serial.println("led putih mati");
    }
  }
}
