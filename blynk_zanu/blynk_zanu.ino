#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
char auth[] = "jgDgStJZLJ8QdgXuuytB33u24H7Cr21R";

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "hehehe";
char pass[] = "12345679";

bool Motor_State = 0;

//dummy data before running serial with stm32
double arus = 1;
double tegangan = 12;
double daya = arus * tegangan;

void setup()
{
  // Debug console
  Serial.begin(9600);
  Blynk.begin(auth, ssid, pass);
}

void loop()
{
  Blynk.run();
  String LCD_atas = "A=" + String(arus) + "A"+ "V=" + String(tegangan) + "V";
  String LCD_bawah = "daya = " + String(daya) + " W"; 
  Blynk.virtualWrite(V0, LCD_atas);
  Blynk.virtualWrite(V1, LCD_bawah); 
}

BLYNK_WRITE(V2){  // This function gets called each time something changes on the widget
  Motor_State = param.asInt();
  if(Motor_State){
    Serial.println("ON");
  }
  else{
    Serial.println("OFF");
  }
}
