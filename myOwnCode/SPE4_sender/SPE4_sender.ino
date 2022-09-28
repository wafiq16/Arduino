void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}
int  counter1 = 0;
int  counter2 = 0;
int  counter3 = 0;
unsigned char checksum[15];
void loop() {
  // put your main code here, to run repeatedly:
  counter1 = 0x5;
  counter2 = 0x45;
  counter3 = 0xf8;
  kirim(String(counter1 + counter2 + counter3));
}

void kirim(String isiPesan){
  int panjangPesan = isiPesan.length();
  char karPesan[panjangPesan + 2];

  checksum[0] = 0;
  
  for(int i=0; i<panjangPesan;i++){
    karPesan[i+1] = isiPesan.charAt(i);
    checksum[0] ^= karPesan[i+1];
    }
    karPesan[0] = 0x54;
    karPesan[panjangPesan + 1] = checksum[0];
    Serial.print(karPesan);
    delay(10);
  }
