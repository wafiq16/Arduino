float tdsValue = 283; //TDS
float suhuAir = 30.38; //Suhu
float ph = 5.59; //pH
int jarak = 20; //jarak
char dataHari[7][12] = {"Minggu", "Senin", "Selasa", "Rabu", "Kamis", "Jumat", "Sabtu"};
String hari; //pakan
int tanggal, bulan, tahun, jam, menit, detik; //pakan
// LCD State
String State_lcd1_waktu = "";
String State_lcd1_tanggal = "";
int State_lcd1_hari = 0;
int State_lcd2_motor = 0;
int State_lcd2_pakan = 0;
int State_lcd3_air = 0;
int State_lcd3_kipas = 0;

int serial_delay = 0;
int counter = 0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
}

void loop() {
  // put your main code here, to run repeatedly:
  State_lcd1_hari = 3; 
  State_lcd1_waktu   = String(jam = 10) + ":" + String(menit = 50) + ":" + String(detik = 40);
  State_lcd3_kipas = 1;
  State_lcd3_air = 1;
  State_lcd2_pakan = 2;
  State_lcd2_motor = 0;
//  if(millis() - serial_delay > 30000 ){
//        serial_delay = millis();
//        Serial.println(millis());
//        Serial.println(serial_delay);
//        if(counter > 4){
//          counter = 0;
//        }
//        if(counter == 0){
          Serial.print("A" + String(ph) + String(suhuAir) + String(int(tdsValue)) + State_lcd3_kipas + State_lcd3_air + State_lcd2_pakan + State_lcd2_motor + State_lcd1_waktu + String(State_lcd1_hari) + String(jarak) + "B"); 
          delay(30000);
//        }
//        else if(counter == 1){
          Serial.print("A6.6934.56312000010:50:40120B");
          delay(30000);
//        }
//        else if(counter == 2){
          Serial.print("A7.0033.38424000110:50:4049B");
          delay(30000); 
//        }
//        else if(counter == 3){
          Serial.print("A8.3232.52576001010:50:40528B");
          delay(30000);
//        }
//        else if(counter == 4){
          Serial.print("A4.2731.73681001110:50:4024B");
          delay(30000);
//        }
//        counter++;
//   }
  }
