// Comment this out to disable prints and save space
#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

char auth[] = "h7keHly7VRvZshTuAaOKpt4C7VyH1Nvi";

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "hehehe";
char pass[] = "12345679";

BlynkTimer timer;

void setup()
{
  // Debug console
  Serial.begin(9600);
  Blynk.begin(auth, ssid, pass);

}

void loop()
{
  Blynk.run();
}
