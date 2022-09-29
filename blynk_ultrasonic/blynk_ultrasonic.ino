#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

#define BLYNK_PRINT Serial
#define Pin_Trigger 12
#define Pin_Echo 14

char auth[] = "Zq43HmHEdVo99ncaGFBZCOsgbSY6KMFY";
char ssid[] = "hehehe";
char pass[] = "12345679";

long durasi = 0;
long jarak = 0;
long timeStamp = 0;
long lastTimeStamp = 0;

WidgetLCD lcd(V1);

void setup()
{
  // Debug console
  Serial.begin(9600);
  pinMode(Pin_Trigger, OUTPUT);
  pinMode(Pin_Echo, INPUT);
  Blynk.begin(auth, ssid, pass);

  lcd.clear();
  lcd.print(0, 0, "jarak(cm)");
}

void loop()
{ 
//  Serial.println("jalan");
  digitalWrite(Pin_Trigger, LOW);
  delayMicroseconds(2);

  digitalWrite(Pin_Trigger, HIGH);
  delayMicroseconds(10);

  digitalWrite(Pin_Trigger, LOW);
  durasi = pulseIn(Pin_Echo, HIGH);
  jarak = (durasi/2) / 29.1;

    lcd.clear();
    lcd.print(0, 0, "jarak(cm)");
    lcd.print(7, 1, jarak);
  delay(500);
  Serial.print("Jarak = ");
  Serial.print(jarak);
  Serial.println(" cm ");
  
  if(jarak < 5 && jarak != 0){
    Blynk.notify("Jarak Terlalu Dekat");
   }
  Blynk.run();
}
