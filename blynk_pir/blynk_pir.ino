#define BLYNK_PRINT Serial

/* Fill-in your Template ID (only if using Blynk.Cloud) */
//#define BLYNK_TEMPLATE_ID   "YourTemplateID"
#define Pin_Led 2
#define Pin_Pir 3

bool Pir_State = 0;

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
char auth[] = "PaI_7nRTxZLDe-qn7IWj80fHTHHOQ7bB";

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "hehehe";
char pass[] = "12345679";

void setup()
{
  // Debug console
  Serial.begin(9600);
  pinMode(Pin_Led, OUTPUT);
  pinMode(Pin_Pir, INPUT);
  Blynk.begin(auth, ssid, pass);

  digitalWrite(Pin_Led, LOW);
}

void loop()
{
  Blynk.run();
}

 BLYNK_WRITE(V4){  // This function gets called each time something changes on the widget
  Pir_State = param.asInt();
  if(Pir_State){
    Serial.println("Object Detected");
    Blynk.notify("Object Detected");
  }
  else
    Blynk.notify("No Object Detected");
  digitalWrite(Pin_Led, Pir_State);
  Blynk.virtualWrite(V0, Pir_State); 
}
