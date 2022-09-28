eint pin1 = 3;
int pin2 = 5;
int pinPwmMotor = 6;
int pwmMotor = 255;
bool flagBalik = false;
int count = 0;
int myCase = 0;
int mySpeed = 0;
//2. pengaturan kecepatan motor 1 arah
//3. pengaturan kecepatan motor 2 arah dengan mengkombinasikan motor ON dan brake
//4. pengaturan kecepatan motor 2 arah dengan mengkombinasikan motor ON dan free running
//5. pengaturan pengereman motor dengan mengkombinasikan motor brake dan free running
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(pin1, OUTPUT);
  pinMode(pin2, OUTPUT);
  pinMode(pinPwmMotor, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  if(mySpeed < 256 && !flagBalik){
    mySpeed++;
    if(mySpeed == 255){
      mySpeed = 0;  
      flagBalik = true;
    }
  }
  else{
    mySpeed--;
    if(mySpeed == -255){
      mySpeed = 0;
      flagBalik = false;
    }
  }
  Serial.println(mySpeed);
//  pokoke_Running();
//  motorRun_Brake(mySpeed);
  motorStop_Brake(mySpeed);
//motorRun_FreeRunning(mySpeed);
}

void pokoke_Running(){
   digitalWrite(pin1, LOW);
   digitalWrite(pin2, HIGH);
   analogWrite(pinPwmMotor, 255);  
  }
// motor on & brake
void motorRun_Brake(int mySpeed){
//  pinPwmMotor = 255;
  if(mySpeed > 255)mySpeed = 255;
  else if(mySpeed < -255) mySpeed = -255;
  if(mySpeed >= 0){
    digitalWrite(pin1, HIGH);
    analogWrite(pin2, 255 - mySpeed);
    }
   else if(mySpeed < 0){
    digitalWrite(pin1, LOW);
    analogWrite(pin2, abs(mySpeed));
    }
   analogWrite(pinPwmMotor, 255);
  }
  
  // motor on & free running
  void motorRun_FreeRunning(int mySpeed){
  if(mySpeed > 255)mySpeed = 255;
  else if(mySpeed < -255) mySpeed = -255;
   if(mySpeed >= 0){
    digitalWrite(pin1, HIGH);
    digitalWrite(pin2, LOW);
    }
   else if(mySpeed < 0){
    digitalWrite(pin1, LOW);
    digitalWrite(pin2, HIGH);
    }
   analogWrite(pinPwmMotor, mySpeed);
   }
   
  // free running & brake
  void motorStop_Brake(int mySpeed){
    if(mySpeed > 255) mySpeed = 254;
    else if(mySpeed < -255) mySpeed = -255;
    else if(mySpeed < 120 && mySpeed > 138) mySpeed = 127;
    digitalWrite(pin1, 254 - mySpeed);digitalWrite(pin2, mySpeed);
    analogWrite(pinPwmMotor, mySpeed);
  }
