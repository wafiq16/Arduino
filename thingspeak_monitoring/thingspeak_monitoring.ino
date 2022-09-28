#include <WiFi.h>
#include "ThingSpeak.h" // always include thingspeak header file after other header files and custom macros
#include <LiquidCrystal_I2C.h>
#include <Wire.h>
#include <ADS1115_WE.h>
#include <FlowMeter.h>  // https://github.com/sekdiy/FlowMeter

//Flowmeter
FlowMeter *Meter;
const unsigned long period = 1000;
int pin_flow = 18;

#define I2C_ADDRESS 0x48
// Turbidity
#define TURBIDITY_SAMPLE 16
#define DTH_MAX_NTU_VOLTAGE 2.5     /* > 3000 NTU with 2.5V */
#define DTH_ZERO_NTU_VOLTAGE 4.25

// PH meter
#define SensorPin 26            //pH meter Analog output to Arduino Analog Input 0
#define Offset 0.00            //deviation compensate
#define samplingInterval 20
#define printInterval 800
#define ArrayLenth  6    //times of collection
float pHArray[ArrayLenth];   //Store the average value of the sensor feedback
int pHArrayIndex=0;

ADS1115_WE adc = ADS1115_WE(I2C_ADDRESS);

float ntu_val = 0;
double vel_val = 0;
double vol_val = 0;
float volt = 0;

char ssid[] = "hehehe";   // your network SSID (name)
char pass[] = "12345670";   // your network password
int keyIndex = 0;            // your network key Index number (needed only for WEP)

WiFiClient  client;
LiquidCrystal_I2C lcd(0x27, 16, 2);

unsigned long myChannelNumber = 1435814;
const char * myWriteAPIKey = "YR2C6A9GR1K6C2L7";

String myStatus = "";

void setup() {
  Serial.begin(115200);  //Initialize serial
  while (!Serial) {
    ; // wait for serial port to connect. Needed for Leonardo native USB port only
  }

  WiFi.mode(WIFI_STA);
  ThingSpeak.begin(client);  // Initialize ThingSpeak
  Wire.begin();
  adc.setVoltageRange_mV(ADS1115_RANGE_6144); //comment line/change parameter to change range

  adc.setCompareChannels(ADS1115_COMP_0_GND); //comment line/change parameter to change channel
  adc.setCompareChannels(ADS1115_COMP_1_GND);
  adc.setCompareChannels(ADS1115_COMP_2_GND);
  adc.setCompareChannels(ADS1115_COMP_3_GND);

  adc.setMeasureMode(ADS1115_CONTINUOUS); //comment line/change parameter to change mode

  //sensor initialize
  Meter = new FlowMeter(digitalPinToInterrupt(pin_flow), UncalibratedSensor, MeterISR, RISING);

  Serial.println("ADS1115 Example Sketch - Continuous Mode");
  Serial.println("All values in volts");
  Serial.println();
  //  I2C di d22 dan d21
  lcd.begin();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("WATER MONITORING");
  lcd.setCursor(4, 1);
  lcd.print("PROTOTYPE");
  delay(2000);
  //  lcd.clear();

}

void loop() {

  // Connect or reconnect to WiFi
  if (WiFi.status() != WL_CONNECTED) {
    Serial.print("Attempting to connect to SSID: ");
    Serial.println(ssid);
    while (WiFi.status() != WL_CONNECTED) {
      WiFi.begin(ssid, pass);  // Connect to WPA/WPA2 network. Change this line if using open or WEP network
      Serial.print(".");
      delay(5000);
    }
    Serial.println("\nConnected.");
  }

  float voltage_Turb = 0.0;
  float voltage_Flow = 0.0;
  float voltage_Ph = 0.0;

  Serial.print("A0: ");
  voltage_Turb = readChannel(ADS1115_COMP_0_GND);
  ntu_val = convertToNTU(voltage_Turb);
  Serial.print("NTU = ");
  Serial.print(ntu_val);
  Serial.print(" ADC = ");
  Serial.println(voltage_Turb);

  Serial.print("A1: ");
  voltage_Ph = readChannel(ADS1115_COMP_1_GND);
  Serial.print(" ADC = ");
  Serial.println(voltage_Ph);
  static unsigned long samplingTime = millis();
  static unsigned long printTime = millis();
  float pHValue,voltage;
//  if(millis()-samplingTime > samplingInterval)
//  {
//      formula gak normal
      pHValue = voltage_Ph*10.84099 - 11.90938;
//      formula normal
//      pHValue = voltage*-5.96+22.25;
//      samplingTime=millis();
//  }
  Serial.print(" pH = ");
  Serial.println(pHValue);
  
  Serial.print("A2: ");
  Meter->tick(1000);
  double vel_val = Meter->getCurrentFlowrate();
  double vol_val = Meter->getTotalVolume();
  Serial.print("VEL = ");
  Serial.print(Meter->getCurrentFlowrate());
  Serial.print(" Liter/min ");
  Serial.print(" VOL = ");
  Serial.print(Meter->getTotalVolume());
  Serial.println(" Liter");
  
  // set the fields with the values
  ThingSpeak.setField(1, ntu_val);
  ThingSpeak.setField(2, (float)vel_val);
  ThingSpeak.setField(3, pHValue);
  
  lcd.setCursor(0, 0);
  lcd.print("V=");   
  lcd.print(vel_val); 
  lcd.print("L/m");
  lcd.setCursor(10, 0);
  lcd.print("pH=");   
  lcd.print(pHValue);
  lcd.setCursor(0, 1); 
  lcd.print("T=");   
  lcd.print(ntu_val); 
  lcd.print(" ntu");
  
  myStatus = String("send data");

  // set the status
  ThingSpeak.setStatus(myStatus);

  // write to the ThingSpeak channel
  int x = ThingSpeak.writeFields(myChannelNumber, myWriteAPIKey);
  if (x == 200) {
    Serial.println("Channel update successful.");
  }
  else {
    Serial.println("Problem updating channel. HTTP error code " + String(x));
  }
  
  delay(1000); // Wait 20 seconds to update the channel again
  lcd.clear();
}

float readChannel(ADS1115_MUX channel) {
  float voltage = 0.0;
  adc.setCompareChannels(channel);
  voltage = adc.getResult_V(); // alternative: getResult_mV for Millivolt
  return voltage;
}

float convertToNTU(float volt)
{
  float ntu = 0;
  if (volt < DTH_MAX_NTU_VOLTAGE)
  {
    ntu = 3000;
  }
  else
  {
    ntu = (-1120.4 * volt * volt) + (5742.3 * volt) - 4352.9;
    if (ntu < 0)
      ntu = 0;
  }
  return ntu;
}

void MeterISR() {
  // let our flow meter count the pulses
  Meter->count();
}
double avergearray(int* arr, int number){
  int i;
  int max,min;
  double avg;
  long amount=0;
  if(number<=0){
    Serial.println("Error number for the array to avraging!/n");
    return 0;
  }
  if(number<=5){   //less than 5, calculated directly statistics
    for(i=0;i<number;i++){
      amount+=arr[i];
    }
    avg = amount/number;
    return avg;
  }else{
    if(arr[0]<arr[1]){
      min = arr[0];max=arr[1];
    }
    else{
      min=arr[1];max=arr[0];
    }
    for(i=2;i<number;i++){
      if(arr[i]<min){
        amount+=min;        //arr<min
        min=arr[i];
      }else {
        if(arr[i]>max){
          amount+=max;    //arr>max
          max=arr[i];
        }else{
          amount+=arr[i]; //min<=arr<=max
        }
      }//if
    }//for
    avg = (double)amount/(number-2);
  }//if
  return avg;
}
