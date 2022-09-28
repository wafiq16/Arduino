#include <DS3231.h>
#include <Wire.h>

DS3231 my_clock;

bool century = false;
bool h12Flag;
bool pmFlag;

void setup() {
	// Start the serial port
	Serial.begin(57600);
  
	// Start the I2C interface
	Wire.begin();

}

void loop() {
  delay(1000);
    DateTime now = my_clock.now();
    
    Serial.print(now.year(), DEC);
    Serial.print('/');
    Serial.print(now.month(), DEC);
    Serial.print('/');
    Serial.print(now.day(), DEC);
    Serial.print(' ');
    Serial.print(now.hour(), DEC);
    Serial.print(':');
    Serial.print(now.minute(), DEC);
    Serial.print(':');
    Serial.print(now.second(), DEC);
    Serial.println();
    
    Serial.print(" since midnight 1/1/1970 = ");
    Serial.print(now.unixtime());
    Serial.print("s = ");
    Serial.print(now.unixtime() / 86400L);
    Serial.println("d");  
}
