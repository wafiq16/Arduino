
        void setup() {
          // put your setup code here, to run once:
          Serial.begin(9600);
          pinMode(13,OUTPUT);
        }
        unsigned char myEnable = 0;
        int counter1,counter2,counter3;
        void loop() {
          // put your main code here, to run repeatedly:
          unsigned char myHeader = 0;
          unsigned char myChecksum = 0;
          unsigned char totalChecksum = 0;
          if(Serial.available() > 0) {
            if(myEnable == 0){
              myHeader = Serial.read();
              if(myHeader == 0x54){
                myEnable = 1;
                }
            }
            if(Serial.available() > 2){
                counter1 = Serial.read();
                counter2 = Serial.read();
                counter3 = Serial.read();
                myChecksum = Serial.read();
         
                totalChecksum ^= myHeader ^ counter1 ^ counter2 ^counter3;
         
                if(totalChecksum == myChecksum){
                  digitalWrite(13,HIGH);
                  }
                  else {
                    digitalWrite(13,LOW);
                    }
                    myEnable = 0;
              }
            }
        }
