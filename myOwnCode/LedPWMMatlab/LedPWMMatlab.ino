//inisiasi variable
double value = 0; //nilai dari PWM
int variableResistor = 0; //nilai variable resistor
double temp = 0; //variable konversi 10 bit ke 8 bit
//////////////////
// setup sistem
void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  Serial.begin(9600);// baudrate serial(harus sama dengan yang di matlab)
  pinMode(3, OUTPUT);// output led
  pinMode(A0,INPUT);// input potensio
}
///////////////
// program sistem
void loop() {
  variableResistor = analogRead(A0); // pembacaan nilai analog potensio
  if(Serial.available()>0)  // pembacaan apakah terjadi komunikasi serial antara matlab dengan arduino
  {
    temp = double(variableResistor*256/1024); //  mengubah tipe data 10 bit ke 8 bit
    Serial.println(temp);// mengirim data ke matlab
    value = double(Serial.read()); // membaca nilai pwm dari matlab
    analogWrite(3,double(value)); //  menghidupkan led sesuai dengan nilai pwm
  }
}
/////////////////
