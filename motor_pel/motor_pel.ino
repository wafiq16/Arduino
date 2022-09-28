// sensor suhu dallas
#include <OneWire.h>
#include <DallasTemperature.h>

// Data wire is plugged into port 2 on the Arduino
#define ONE_WIRE_BUS 2
#define pinRelay 3

// Setup a oneWire instance to communicate with any OneWire devices (not just Maxim/Dallas temperature ICs)
OneWire oneWire(ONE_WIRE_BUS);

// Pass our oneWire reference to Dallas Temperature.
DallasTemperature sensors(&oneWire);

// kecepatan motor
// digital pin 2 is the hall pin
int hall_pin = 2;
// set number of hall trips for RPM reading (higher improves accuracy)
float hall_thresh = 100.0;

// sensor arus
const int pinADC = A0;
int sensitivitas = 66; //tegantung sensor arus yang digunakan, yang ini 30A
int nilaiadc = 00;
double teganganoffset = 2117; //nilai pembacaan offset saat tidak ada arus yang lewat
double tegangan = 00;
double nilaiarus = 00;
double nilaiarusakhir = 00;
double averageCurrent = 00;
int i = 0;
int Pir_State = 0;

// blink
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
char auth[] = "PaI_7nRTxZLDe-qn7IWj80fHTHHOQ7bB";

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "hehehe";
char pass[] = "12345679";


void setup() {
  // put your setup code here, to run once:
  delay(3000);
  Serial.begin(9600); //baud komunikasi serial monitor 9600bps

  pinMode(pinRelay, OUTPUT);
  pinMode(hall_pin, INPUT);
  // Start up the library
  sensors.begin();
  Blynk.begin(auth, ssid, pass);
}

// calculate adc for sensor current acs712 30 A
void data_olah() {
  nilaiadc = analogRead(pinADC);
  tegangan = ((nilaiadc) / 1024.0) * 5000;
  nilaiarus = ((tegangan - teganganoffset) / sensitivitas);
  averageCurrent += nilaiarus;
  if (i > 10) {
    i = 0;
    averageCurrent = averageCurrent / 10;
    nilaiarusakhir = averageCurrent;
  }
  i++;
}

void loop() {
  // put your main code here, to run repeatedly:
  data_olah();
  Serial.print("Nilai ADC yang terbaca = " );
  Serial.print(nilaiadc);

  Serial.print("\t tegangan (mV) = ");
  Serial.print(tegangan, 3);

  Serial.print("\t Arus = ");
  Serial.println(nilaiarusakhir, 3);

  Serial.print("Requesting temperatures...");
  sensors.requestTemperatures(); // Send the command to get temperatures
  Serial.println("DONE");
  // After we got the temperatures, we can print them here.
  // We use the function ByIndex, and as an example get the temperature from the first sensor only.
  float tempC = sensors.getTempCByIndex(0);

  if (tempC > 31) {
    digitalWrite(pinRelay, LOW);
  }
  else {
    digitalWrite(pinRelay, HIGH);
  }
  // Check if reading was successful
  if (tempC != DEVICE_DISCONNECTED_C)
  {
    Serial.print("Temperature for the device 1 (index 0) is: ");
    Serial.println(tempC);
  }
  else
  {
    Serial.println("Error: Could not read temperature data");
  }

  // preallocate values for tach
  float hall_count = 1.0;
  float start = micros();
  bool on_state = false;
  // counting number of times the hall sensor is tripped
  // but without double counting during the same trip
  while (true) {
    if (digitalRead(hall_pin) == 0) {
      if (on_state == false) {
        on_state = true;
        hall_count += 1.0;
      }
    } else {
      on_state = false;
    }

    if (hall_count >= hall_thresh) {
      break;
    }
  }

  // print information about Time and RPM
  float end_time = micros();
  float time_passed = ((end_time - start) / 1000000.0);
  Serial.print("Time Passed: ");
  Serial.print(time_passed);
  Serial.println("s");
  float rpm_val = (hall_count / time_passed) * 60.0;
  Serial.print(rpm_val);
  Serial.println(" RPM");
  Blynk.run();
}


BLYNK_WRITE(V4) { // This function gets called each time something changes on the widget
  Pir_State = param.asInt();
  if (Pir_State) {
    Serial.println("Object Detected");
    Blynk.notify("Object Detected");
  }
  else
    Blynk.notify("No Object Detected");
  digitalWrite(Pin_Led, Pir_State);
  Blynk.virtualWrite(V0, Pir_State);
}
