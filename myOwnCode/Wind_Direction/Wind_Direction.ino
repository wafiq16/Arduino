int Wind_Direction;
int Sensor_Pin = 36;
char *Hasil_Pembacaan;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(Sensor_Pin , INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  Wind_Direction = analogRead(Sensor_Pin);
  // if(Serial.available() > 0){
//  sprintf(Hasil_Pembacaan, "Arah Sensor = %d\n",Wind_Direction);
  Serial.println(Hasil_Pembacaan);
  // }
    
}
