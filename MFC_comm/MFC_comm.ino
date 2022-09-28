wwechar dataKirim[6] = "123456";
char myData;
void setup() {
  // put your setup code here, to run once:
    Serial.begin(9600);
  pinMode(LED_BUILTIN, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  if (Serial.available() > 0) {
    // read the most recent byte (which will be from 0 to 255):
    myData = Serial.read();
    for(int i=0; i<6 ; i++){
      Serial.print((String)dataKirim[i]);
    }
    if(myData == '3')
      digitalWrite(LED_BUILTIN, OUTPUT); 
  }
}
