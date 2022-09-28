int dataInput = 0;
int a,b,c = 0;
int h = 0;
int sum = 0;
int count = 0;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(5,OUTPUT);
  pinMode(6,OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  if(Serial.available()>0) {
//    dataInput = Serial.read();
//    Serial.write(dataInput);
////    Serial.println();
//    if(dataInput == 'a'){
//      digitalWrite(5,HIGH);
//      }
//    else if(dataInput == 'b'){
//      digitalWrite(5,LOW);
//      }
//    else if(dataInput == 'c'){
//      digitalWrite(6,HIGH);
//      }
//    else if(dataInput == 'd'){
//      digitalWrite(6,LOW);
//      }
      if(count == 0){
        delay(10);
        Serial.print("Masukkan nilai C1 = ");
        a = int(Serial.read()) - '0';
        Serial.print(a);
//        a = int(sum);
        Serial.println();
        if(a>0){
          count++;
        }
      }
      else if (count == 1){
        delay(10);
        Serial.print("Masukkan nilai C2 = ");
        b = int(Serial.read()) - '0';
        Serial.print(b);
//        b = int(sum); 
        Serial.println();
        if(b>0){
          count++;
        }
      }
      else if(count == 2){
        delay(10);
//        a = 3;
//        b = 4;
        h = int(sqrt(pow(a,2) + pow(b,2))); 
        Serial.print("Maka panjang sisi miring h adalah ");
//        Serial.write(h);
        Serial.println(h);
        if(h>a||h>b){
          count = 0;
        }
      }  
   }    
}
