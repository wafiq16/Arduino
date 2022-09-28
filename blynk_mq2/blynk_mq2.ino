// GPIO 2 D4
#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

char auth[] = "nM4qWukoq0kKHBWMR5LmzHpo8BCaxHc8";

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "hehehe";
char pass[] = "12345679";

BlynkTimer timer;

int value = 0;

void setup()
{
  // Debug console
  Serial.begin(9600);
  Blynk.begin(auth, ssid, pass);
  pinMode(2, OUTPUT);
}

void loop()
{
  Blynk.run();
}

BLYNK_WRITE(V4){  // This function gets called each time something changes on the widget
  value = param.asInt();  // This gets the 'value' of the Widget as an integer
  if(value >= 800)
  {
    digitalWrite(2, HIGH);  // this send a PWM signal based on 'value' to the GPIO pin
    Blynk.notify("Kondisi gas berbahaya");
  }
  else
  {
    digitalWrite(2, LOW);
    Blynk.notify("Kondisi gas aman");
  }
}
