int pin1 = 3;
int pin2 = 5;
int pinpwmMotor = 6;
long pwmMotor = 0;
int countPerlambat = 0;
bool perlambat = false;
bool balik = false;
int count = 0;
int myCase = 0;
enum motorCase{
  motor1arah = 1,
  motorOnBrake = 2,
  motorOnFreeRunning = 3,
  motorBrakeFreeRunning = 4
  };
//2. pengaturan kecepatan motor 1 arah
//3. pengaturan kecepatan motor 2 arah dengan mengkombinasikan motor ON dan brake
//4. pengaturan kecepatan motor 2 arah dengan mengkombinasikan motor ON dan free running
//5. pengaturan pengereman motor dengan mengkombinasikan motor brake dan free running
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(pin1, OUTPUT);
  pinMode(pin2, OUTPUT);
  pinMode(pinpwmMotor, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  //Serial.println("program berjalan");
//  switch(myCase){
//    case motor1arah:
//      case2();
//      myCase = motorOnBrake ;
//    case motorOnBrake :
//      case3();
//      myCase = motorOnFreeRunning;
//    case motorOnFreeRunning:
//      case4();
//      myCase = motorBrakeFreeRunning;
//    case motorBrakeFreeRunning:
//      case5();
//      myCase = motor1arah;
//     default : motor1arah;
//    }
//  case2();
//  case3();
//case4();
case5();
  //coba++;
  Serial.println(pwmMotor);
}

int percepatMotor() {
    pwmMotor++;
    if(pwmMotor >= 255){ 
      //delay(5000);
      pwmMotor = 255;
      perlambat = true;
      if(count%2 == 1){
        balik = true;  
        }
        else{
          balik = false;
       }
       count++;
      countPerlambat = 0;
     }
  //Serial.print(balik);
  Serial.println("percepat");

}

int perlambatMotor() {
  countPerlambat++;
  if(countPerlambat >= 255){ 
      //delay(5000);
      countPerlambat = 255;
      if(count%2 == 1){
        balik = true;  
        }
        else{
          balik = false;
       }
       count++;
       perlambat = false;
   }
   pwmMotor = 255 - countPerlambat;
  Serial.println("perlambat");
}

int case2() {
  Serial.println("case2");
  digitalWrite(pin1, LOW);
  digitalWrite(pin2, HIGH);
  //perlambatMotor();
  if (perlambat) {
    perlambatMotor();
  }
  else{
    percepatMotor();
  }
  analogWrite(pinpwmMotor, pwmMotor);
}

void case3() {
  //perlambatMotor();
  if (balik) {
    digitalWrite(pin1, HIGH);
    digitalWrite(pin2, LOW);
  }
  else{
    digitalWrite(pin1, LOW);
  digitalWrite(pin2, HIGH);
    }
  if (perlambat) {
    perlambatMotor();
  }
  else{
    percepatMotor();
  }
  analogWrite(pinpwmMotor, pwmMotor);
}

void case4() {
  if (balik) {
    digitalWrite(pin1, HIGH);
    digitalWrite(pin2, LOW);
  }
  else{
    digitalWrite(pin1, LOW);
  digitalWrite(pin2, HIGH);
    }
  if (perlambat) {
    //perlambatMotor();
    pwmMotor = 0;
    perlambat = false;
    //count=1;
  }
  else{
    percepatMotor();
  }
  analogWrite(pinpwmMotor, pwmMotor);
}

void  case5() {
  if (balik) {
    digitalWrite(pin1, HIGH);
    digitalWrite(pin2, LOW);
  }
  else{
    digitalWrite(pin1, LOW);
    digitalWrite(pin2, HIGH);    
    }
  if (perlambat) {
    if (countPerlambat > 128) {
      pwmMotor = 0;
      perlambat = false;
    }
    else {
      perlambatMotor();
    }
  }
  else{
    percepatMotor();
  }
  analogWrite(pinpwmMotor, pwmMotor);
}
