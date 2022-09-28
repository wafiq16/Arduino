#include <OneWire.h>
#include <DallasTemperature.h>
#include <ADS1X15.h>
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <LCD_I2C.h>

LCD_I2C lcd(0x27, 16, 2);
// Data wire is plugged into port 2 on the Arduino
#define ONE_WIRE_BUS 14 //D5
#define pinRelay 2 //S3
#define pinHall 13//D7
#define TEMPERATURE_PRECISION 9

char auth[] = "nM4qWukoq0kKHBWMR5LmzHpo8BCaxHc8";

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "hehehe";
char pass[] = "12345679";

// Setup a oneWire instance to communicate with any OneWire devices (not just Maxim/Dallas temperature ICs)
OneWire oneWire(ONE_WIRE_BUS);
// Pass our oneWire reference to Dallas Temperature.
DallasTemperature sensors(&oneWire);

ADS1115 ADS(0x48);

DeviceAddress tempDeviceAddress;

// set number of hall trips for RPM reading (higher improves accuracy)
float hall_thresh = 1000.0;
int zeroCurrentValue = 13350.94;
bool done = true;
bool on_state = false;
long hall_count = 0;
float start_count;// = micros();
bool Motor_State = 0;
int numberOfDevices = 0;
float tempC = 0;

void setup() {
  // put your setup code here, to run once:
  delay(3000);
  Serial.begin(9600);
  Serial.println("Dallas Temperature IC Control Library Demo");
  pinMode(pinRelay, OUTPUT);
  pinMode(pinHall, INPUT);

  // Start up the library

  sensors.begin();
  numberOfDevices = sensors.getDeviceCount();

  ADS.begin();
  lcd.begin(); // If you are using more I2C devices using the Wire library use lcd.begin(false)
  // this stop the library(LCD_I2C) from calling Wire.begin()
  lcd.backlight();
  Blynk.begin(auth, ssid, pass);

  // locate devices on the bus
  Serial.print("Locating devices...");

  Serial.print("Found ");
  Serial.print(numberOfDevices, DEC);
  Serial.println(" devices.");

  // report parasite power requirements
  Serial.print("Parasite power is: ");
  if (sensors.isParasitePowerMode()) Serial.println("ON");
  else Serial.println("OFF");

  // Loop through each device, print out address
  for (int i = 0; i < numberOfDevices; i++)
  {
    // Search the wire for address
    if (sensors.getAddress(tempDeviceAddress, i))
    {
      Serial.print("Found device ");
      Serial.print(i, DEC);
      Serial.print(" with address: ");
      printAddress(tempDeviceAddress);
      Serial.println();

      Serial.print("Setting resolution to ");
      Serial.println(TEMPERATURE_PRECISION, DEC);

      // set the resolution to TEMPERATURE_PRECISION bit (Each Dallas/Maxim device is capable of several different resolutions)
      sensors.setResolution(tempDeviceAddress, TEMPERATURE_PRECISION);

      Serial.print("Resolution actually set to: ");
      Serial.print(sensors.getResolution(tempDeviceAddress), DEC);
      Serial.println();
    } else {
      Serial.print("Found ghost device at ");
      Serial.print(i, DEC);
      Serial.print(" but could not detect address. Check power and cabling");
    }
  }

}

void loop() {
  Blynk.run();

  sensors.requestTemperatures(); // Send the command to get temperatures
  // We use the function ByIndex, and as an example get the temperature from the first sensor only.

  for (int i = 0; i < numberOfDevices; i++)
  {
    // Search the wire for address
    if (sensors.getAddress(tempDeviceAddress, i))
    {
      // Output the device ID
      //      Serial.print("Temperature for device: ");
      //      Serial.println(i, DEC);

      // It responds almost immediately. Let's print out the data
      printTemperature(tempDeviceAddress); // Use a simple function to print out the data
    }
  }
  //  if (tempC > 31) {
  //    digitalWrite(pinRelay, LOW);
  //  }
  //  else {
  //    digitalWrite(pinRelay, HIGH);
  //  }

  long rawValue = 0;
  for (int i = 0; i < 50; i++) {
    rawValue += ADS.readADC(2);
  }
  float rawVoltage = rawValue / 50.0;
  float current = (rawVoltage - zeroCurrentValue) * 4.0 / 26.214 / 0.185;

  Serial.print("Arus : "); // Current
  current = current / 1000;
  Serial.println(current);

  hall_count = 0.0;
  on_state = false;
  read_rpm();

  // print information about Time and RPM
  float time_passed = ((5000000) / 1000000.0);
  Serial.print("Time Passed: ");
  Serial.print(time_passed);
  Serial.println("s");

  float rpm_val = float(hall_count / time_passed) * 60.0;
  Serial.print(rpm_val);
  Serial.println(" RPM");

  Blynk.virtualWrite(V0, current);
  Blynk.virtualWrite(V1, tempC);
  Blynk.virtualWrite(V2, rpm_val);

  lcd.backlight();
  lcd.clear();

  lcd.setCursor(0, 0);
  lcd.print("RPM="); // You can make spaces using well... spaces
  lcd.print(int(rpm_val));
  lcd.setCursor(9, 0);
  lcd.print("I="); // You can make spaces using well... spaces
  lcd.print(current);
  lcd.setCursor(3, 1);
  lcd.print("Temp="); // You can make spaces using well... spaces
  lcd.print(tempC);
  lcd.print("C");

  delay(1000);
  //  lcd.clear();
}

void read_rpm() {
  start_count = micros();
  for (; micros() - start_count < 5000000 && hall_count < hall_thresh;) {
    Serial.println(hall_count);
    if (digitalRead(pinHall) == 0) {
      if (on_state == false) {
        on_state = true;
        hall_count += 1.0;
      }
    }
    else {
      on_state = false;
    }
  }
}

BLYNK_WRITE(V3) { // This function gets called each time something changes on the widget
  Motor_State = param.asInt();
  Serial.print("Motor State = ");
  Serial.print(!Motor_State);
  digitalWrite(pinRelay, Motor_State);
}

void printTemperature(DeviceAddress deviceAddress)
{
  tempC = sensors.getTempC(deviceAddress);
  if (tempC == DEVICE_DISCONNECTED_C)
  {
    Serial.println("Error: Could not read temperature data");
    return;
  }
  Serial.print("Temp C: ");
  Serial.println
  (tempC);
}

void printAddress(DeviceAddress deviceAddress)
{
  for (uint8_t i = 0; i < 8; i++)
  {
    if (deviceAddress[i] < 16) Serial.print("0");
    Serial.print(deviceAddress[i], HEX);
  }
}
