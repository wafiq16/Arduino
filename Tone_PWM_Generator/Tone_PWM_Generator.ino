#define Do 523
#define Re 587
#define Mi 659
#define Fa 698
#define Sol 784
#define La 880
#define Si 990
#define Dol 1056

String tohex(int dec){
  
  char hexaDeciNum[100];
    int i = 0;
    while (dec != 0) {
        // temporary variable to store remainder
        int temp = 0;
 
        // storing remainder in temp variable.
        temp = dec % 16;
 
        // check if temp < 10
        if (temp < 10) {
            hexaDeciNum[i] = temp + 48;
            i++;
        }
        else {
            hexaDeciNum[i] = temp + 55;
            i++;
        }
 
        dec = dec / 16;
    }String tops;
 //Serial.print("hexa:");
    // printing hexadecimal number array in reverse order
    for (int j = i - 1; j >= 0; j--){Serial.print(hexaDeciNum[j]);
    tops+=hexaDeciNum[j];
    }
   // Serial.println(" ");
    //Serial.print("hexa str:");
    //Serial.println(tops);
    return tops;
}
void tonePFC(int freq,int lengths,int pauses){
 long decimalnum, quotient, remainder;
 //int i, j = 0;
int top;
    long fclk=16000000;
    //Serial.print("freq:");
    //Serial.println(freq);
    //Serial.print("fclk:");
    //Serial.println(fclk);
    top=fclk/(16*freq);
int duty=top/2; 
    //Serial.print("top:");
    //Serial.println(top);
    
    String tops,sduty;
    //tops=tohex(top);  
    //sduty=tohex(duty);  
    ICR1H=(top>>8)&0x00FF;
ICR1L=top;
OCR1AH=(duty>>8)&0x00FF;
OCR1AL=duty;
delay(lengths);
ICR1H=0;
ICR1L=0;
OCR1AH=0;
OCR1AL=0;
delay(pauses);
}

void setup() {
Serial.begin(1105200);
pinMode(9,OUTPUT);
TCCR1A=(1<<COM1A1) | (0<<COM1A0) | (1<<COM1B1) | (1<<COM1B0) | (0<<WGM11) | (0<<WGM10);
TCCR1B=(0<<ICNC1) | (0<<ICES1) | (1<<WGM13) | (0<<WGM12) | (0<<CS12) | (1<<CS11) | (0<<CS10);
TCNT1H=0x00;
TCNT1L=0x00;
ICR1H=0x07;
ICR1L=0x78;
OCR1AH=0x03;
OCR1AL=0x89;
OCR1BH=0x03;
OCR1BL=0x89;

  // put your setup code here, to run once:

}

void loop() {
  tonePFC(Do,220,120);
  
  tonePFC(Mi,110,120);
  tonePFC(Dol,220,200);
  tonePFC(Mi,150,60);
  tonePFC(Fa,55,120);

  tonePFC(Sol,220,120);
  tonePFC(Mi,200,200);
  tonePFC(Mi,120,120);
  tonePFC(Re,130,120);

    tonePFC(Do,220,120);
  tonePFC(Dol,160,200);
  tonePFC(Sol,120,120);
  tonePFC(Mi,100,120);

    tonePFC(Fa,220,120);
  tonePFC(Mi,220,200);
  tonePFC(Mi,110,200);
  tonePFC(Fa,220,120);

    tonePFC(Sol,220,120);
  tonePFC(La,110,200);
  tonePFC(Si,220,120);
  tonePFC(Dol,220,120);

    tonePFC(Sol,220,120);
  tonePFC(Mi,220,200);
  tonePFC(Re,220,120);
  tonePFC(Do,110,120);

    tonePFC(Mi,220,120);
  tonePFC(Fa,110,200);
  tonePFC(Re,55,120);
  tonePFC(Do,220,120);

    tonePFC(Fa,220,120);
  tonePFC(Sol,110,200);
  tonePFC(Mi,220,120);
  tonePFC(Re,110,120);

    tonePFC(Sol,220,120);
  tonePFC(Mi,150,100);
  tonePFC(Mi,110,120);
  tonePFC(Fa,220,120);
   
  delay(2000);
}
