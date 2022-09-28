#include <Wire.h>
#include <DS3231.h>
#include <LiquidCrystal_I2C.h>

// Set the LCD address to 0x27 for a 16 chars and 2 line display
LiquidCrystal_I2C lcd(0x27, 16, 2);

DS3231 myclock;
RTCDateTime dt;

void setup()
{
  Serial.begin(9600);

  // Initialize DS3231
  Serial.println("Initialize DS3231");;
  myclock.begin();

  // Set sketch compiling time
  myclock.setDateTime(__DATE__, __TIME__);
  lcd.begin();

  // Turn on the blacklight and print a message.
  lcd.backlight();
  lcd.print("Hello, world!");
}

void loop()
{
  dt = myclock.getDateTime();

  // For leading zero look to DS3231_dateformat example

  Serial.print("Raw data: ");
  Serial.print(dt.year);   Serial.print("-");
  Serial.print(dt.month);  Serial.print("-");
  Serial.print(dt.day);    Serial.print(" ");
  Serial.print(dt.hour);   Serial.print(":");
  Serial.print(dt.minute); Serial.print(":");
  Serial.print(dt.second); Serial.println("");

  delay(1000);
}
