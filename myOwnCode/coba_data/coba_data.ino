    const int pinIR = 4;
    const int pinLed = 2;
    const int lm = A2;
    void setup() {
      Serial.begin(9600);
      pinMode(pinIR, INPUT);
      pinMode(lm, INPUT);
      pinMode(pinLed, OUTPUT);
      Serial.println("Deteksi Sensor IR");
      delay(3000);
    }
    void loop() {
      int sensorState = digitalRead(pinIR);
      double suhuku = analogRead(lm);
      suhuku = suhuku * 500 /1024;
      if (sensorState == LOW) {
        Serial.println("Tedeteksi");
        digitalWrite(pinLed, HIGH);
      } else {
        Serial.println("Tidak terdeteksi");
        digitalWrite(pinLed, LOW);
      }
      Serial.println(suhuku);
      delay(500);
    }
