/***************************************************************************
* Example sketch for the ADS1115_WE library
*
* This sketch shows how to use the ADS1115 in continuous mode. 
*  
* Further information can be found on:
* https://wolles-elektronikkiste.de/ads1115 (German)
* https://wolles-elektronikkiste.de/en/ads1115-a-d-converter-with-amplifier (English)
* 
***************************************************************************/

#include<ADS1115_WE.h> 
#include<Wire.h>
#define I2C_ADDRESS 0x48

ADS1115_WE adc = ADS1115_WE(I2C_ADDRESS);

void setup() {
  Wire.begin();
  Serial.begin(9600);
  if(!adc.init()){
    Serial.println("ADS1115 not connected!");
  }

  /* Set the voltage range of the ADC to adjust the gain
   * Please note that you must not apply more than VDD + 0.3V to the input pins!
   * 
   * ADS1115_RANGE_6144  ->  +/- 6144 mV
   * ADS1115_RANGE_4096  ->  +/- 4096 mV
   * ADS1115_RANGE_2048  ->  +/- 2048 mV (default)
   * ADS1115_RANGE_1024  ->  +/- 1024 mV
   * ADS1115_RANGE_0512  ->  +/- 512 mV
   * ADS1115_RANGE_0256  ->  +/- 256 mV
   */
  adc.setVoltageRange_mV(ADS1115_RANGE_6144); //comment line/change parameter to change range
  
  adc.setCompareChannels(ADS1115_COMP_0_GND); //comment line/change parameter to change channel
  adc.setCompareChannels(ADS1115_COMP_1_GND);
  adc.setCompareChannels(ADS1115_COMP_2_GND);
  adc.setCompareChannels(ADS1115_COMP_3_GND);

  adc.setMeasureMode(ADS1115_CONTINUOUS); //comment line/change parameter to change mode

  Serial.println("ADS1115 Example Sketch - Continuous Mode");
  Serial.println("All values in volts");
  Serial.println();
}

void loop() {
  float voltage = 0.0;

  Serial.print("0: ");
  voltage = readChannel(ADS1115_COMP_0_GND);
  Serial.print(voltage);

  Serial.print(",   1: ");
  voltage = readChannel(ADS1115_COMP_1_GND);
  Serial.print(voltage);
  
  Serial.print(",   2: ");
  voltage = readChannel(ADS1115_COMP_2_GND);
  Serial.print(voltage);

  Serial.print(",   3: ");
  voltage = readChannel(ADS1115_COMP_3_GND);
  Serial.println(voltage);

  delay(1000);
}

float readChannel(ADS1115_MUX channel) {
  float voltage = 0.0;
  adc.setCompareChannels(channel);
  voltage = adc.getResult_V(); // alternative: getResult_mV for Millivolt
  return voltage;
}
