#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <dht.h>
#define sensor 14 
dht DHT;

char auth[] = "zrzqGbBnQjAopdxZs9aMCZYRAuXGg4nX";
char ssid[] = "hehehe";
char pass[] = "12345679";

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  Blynk.begin(auth, ssid, pass);
}

void loop() {
  // put your main code here, to run repeatedly:
  
    Blynk.run();
    DHT.read11(sensor);
  Serial.print("Kelembaban udara = ");
  Serial.print(DHT.humidity);
  Serial.print("% ");
  Serial.print("Suhu = ");
  Serial.print(DHT.temperature); 
  Serial.println(" C ");
    Blynk.virtualWrite(V0, DHT.temperature);
    Blynk.virtualWrite(V1, DHT.humidity);
  
  // ждём две секунды
  delay(500);
}
