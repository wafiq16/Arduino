//for 5 v
#define DTH_MAX_NTU_VOLTAGE 2.5
//for 3.3 v
//#define DTH_MAX_NTU_VOLTAGE 1.7

void setup() {
  Serial.begin(9600); //Baud rate: 9600
}
void loop() {
  int sensorValue = analogRead(14);// read the input on analog pin 0:
  float voltage = sensorValue * (5 / 4096.0); // Convert the analog reading (which goes from 0 - 1023) to a voltage (0 - 5V):
  Serial.print("tegangan=");
  Serial.println(voltage); // print out the value you read:
  Serial.print("analog=");
  Serial.println(analogRead(14));
  Serial.print("Ntu=");
  Serial.println(convertToNTU(voltage));
  delay(500);
}

float convertToNTU(float volt)
{
  float ntu = 0;
  
  if(volt < DTH_MAX_NTU_VOLTAGE)
  {
    ntu = 3000;
  }
  else
  {
//    for 5 v
    ntu = (-1120.4 * volt * volt) + (5742.3 * volt) - 4352.9;
//    for 3.3 v
//      ntu = (-1120.4 * volt * volt * 10.89 / 25 ) + (5742.3 * volt * 3.3 / 5 ) - (4352.9) ;
    if(ntu < 0)
      ntu = 0;
  }
  return ntu;
}
