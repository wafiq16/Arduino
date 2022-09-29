#include <ESP8266WiFi.h>
#include "DHT.h"

#define DHTTYPE DHT11
#define sensor 14 

DHT dht(sensor, DHTTYPE);

char ssid[] = "hehehe";
char pass[] = "12345679";

WiFiServer server(80);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  delay(20);
  dht.begin();
  Serial.println();
  Serial.print("menghubungkan ke WiFi ==> ");
  Serial.println(ssid);
  WiFi.begin(ssid, pass);
  while(WiFi.status() != WL_CONNECTED){
    delay(300);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi telah terhubung");
  server.begin();
  Serial.println("Koneksi Server telah dimulai");
  Serial.print("Alamat IP : ");
  Serial.println("http://");
  Serial.println(WiFi.localIP());
  Serial.println("/");
  
}

void loop() {
  // put your main code here, to run repeatedly:
    WiFiClient client = server.available();
    if(!client){
      return;
      }
    Serial.println("Koneksi Ditemukan");
    while(!client.available()){
      delay(5);
    }
    float h = dht.readHumidity();
    // Read temperature as Celsius (the default)
    float t = dht.readTemperature();
    // Read temperature as Fahrenheit (isFahrenheit = true)
    float f = dht.readTemperature(true);
    if(client){
      while(client.connected()){
        if(client.available()){
          char c = client.read();
          if(c == '\n'){
            if (isnan(h) || isnan(t) || isnan(f)) {
               Serial.println("Gagal membaca sensor DHT");
            }
            else{
                Serial.print("Kelembaban udara = ");
                Serial.print(h);
                Serial.print("% ");
                Serial.print("Suhu = ");
                Serial.print(t); 
                Serial.println(" C ");
                Serial.print("Suhu = ");
                Serial.print(f); 
                Serial.println(" F ");
             }

             client.println("HTTP/1.1 200 OK");
             client.println("Content-Type: text/html");
             client.println("Connection close");
             client.println();
             client.println("<!DOCTYPE HTML>");
             client.println("<html>");
             client.println("<head></head><body><h2>Monitoring Suhu dan Kelembapan</h2><h3>Suhu Celcius : ");
             client.println(t);
             client.println("Celcius</h3><h3>Suhu Fahrenheit : ");
             client.println(f);
             client.println("Fahrenheit</h3><h3>Kelembapan : ");
             client.println(h);
             client.println("</h3><h3>");
             client.println("</body></html>");
             break;
          }
        }
        delay(5);
      }
   }  
}
