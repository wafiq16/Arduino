//inisiasi variable
double value = 0; //nilai dari PWM
double suhu = 0; //nilai variable resistor untuk suhu
double jarak = 0; // nilai variable resistor untuk jarak
double temp = 0; //variable konversi 10 bit ke 8 bit
int i = 0; // nilai data key untuk komunikasi
int sendTime = 0;
//////////////////
// setup sistem
void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  Serial.begin(115200);// baudrate serial(harus sama dengan yang di matlab)
  pinMode(3, OUTPUT);// output led
  pinMode(A0,INPUT);// input potensio suhu
  pinMode(A1,INPUT);// input potensio jarak
}
///////////////
// program sistem
void loop() {
  suhu = analogRead(A0); // pembacaan nilai analog suhu
  jarak = analogRead(A1); // pembacaan nilai analog jarak
  double(suhu*256/1024); //  mengubah tipe data 10 bit ke 8 bit
  double(jarak*256/1024); //  mengubah tipe data 10 bit ke 8 bit
  if(Serial.available()>0 && (millis()-sendTime>5 || sendTime == 0))  // pembacaan apakah terjadi komunikasi serial antara matlab dengan arduino
  {  
    sendTime = millis();
    if(i == 1){
      Serial.print('A');
      temp = 'A';
    }
    else if(i == 3){
      Serial.print('B');
      temp += 'B';
    }
    else if(i == 5){
      Serial.print(suhu);// mengirim data ke matlab
      temp += suhu;
    }
    else if(i==7)
    {
      Serial.print(jarak);// mengirim data ke matlab
      temp += jarak;
    }
    else if(i == 9){
      Serial.print(temp);// mengirim data ke matlab
    }
    value = double(Serial.read()); // membaca nilai pwm dari matlab
    analogWrite(3,double(value)); //  menghidupkan led sesuai dengan nilai pwm
    i++;
    if(i>9)
      i = 1;
  }
}
/////////////////
