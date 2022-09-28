// now.pde
// Prints a snapshot of the current date and time along with the UNIX time
// Modified by Andy Wickert from the JeeLabs / Ladyada RTC library examples
// 5/15/11

#include <Wire.h>
#include <DS3231.h>

RTClib myRTC;
DS3231 myTime;

void setup () {
    Serial.begin(57600);
    Wire.begin();
//    myRTC.setDOW(RABU);           // Set Hari
//    myRTC.setTime(13, 40, 00);      // Set waktu JJ:MM:DD (24hr format)
//    myRTC.setDate(23, 6, 2021);     // Set tanggal 20 September 2016
//    myRTC.begin();

}
//RTCnow ke 1/1/2000 pukul 00:00:00 jadi kalo dibuat sekarang ya tahun ditambah 21 hari ditambah 21 bulan ditambah 5 jamnya menyesuaikan 13:26:00

void loop () {
  
    delay(1000);
  
    DateTime now = myRTC.now();

    int tahun_sekarang  = now.year();
    int bulan_sekarang  = now.month();
    int hari_sekarang   = now.day();
    int jam_sekarang    = now.hour();
    int menit_sekarang  = now.minute();
    int detik_sekarang  = now.second();
    
//    Serial.print(tahun_sekarang);
//    Serial.print('/');
//    Serial.print(bulan_sekarang);
//    Serial.print('/');
//    Serial.print(hari_sekarang);
//    Serial.print(' ');
//    Serial.print(jam_sekarang);
//    Serial.print(':');
//    Serial.print(menit_sekarang);
//    Serial.print(':');
//    Serial.print(detik_sekarang);
//    Serial.println();
    
//    Serial.print(" since midnight 1/1/1970 = ");
//    Serial.print(now.unixtime());
//    Serial.print("s = ");
//    Serial.print(now.unixtime() / 86400L);
//    Serial.println("d");
      Serial.println(myTime.getYear());
}
