
//////////////////////////////////////// libraries ////////////////////////////////////////////
#include "DHT.h"
#define DHTPIN 2     // what pin we're connected to
#define DHTTYPE DHT11   // DHT 11



/////////////////////////////////////// first definations ////////////////////////////////////
DHT dht(DHTPIN, DHTTYPE);

////////////////////////////////////// define pins ///////////////////////////////////////////
int pht_reader_1 = A0;
int pht_reader_2 = A1;
int pht_reader_3 = A2;
int relay_2_pin = 12;
int relay_1_pin = 13;

////////////////////////////////////// define others //////////////////////////////////////////
int delay_1 = 30000;                       // ms cinsinden
int relay_1_t = 3;                        // dk cinsinden eşit aralıklarla açıp kapatma
int relay_2_t = 10;                        // dk cinsinden kapalı kalma süresi 12 saat 720 dk 


//////////////////////////////////// define no touch ///////////////////////////////////////////

int relay_1_tt = relay_1_t;
int relay_2_tt = relay_2_t;
int water_air_pump_on = 0;
int lights_on = 0;
int seconds = 60;
int secondss = seconds;
int t_con_1 = 0;                          
int t_con_2 = 0;
///////////////////////////////////// void set UP /////////////////////////////////////////////
void setup() {
  Serial.begin(9600);
  pinMode(pht_reader_1, INPUT);
  pinMode(pht_reader_2, INPUT);
  pinMode(pht_reader_3, INPUT);
  pinMode(relay_1_pin, OUTPUT);
  pinMode(relay_2_pin, OUTPUT);
  Serial.println("***...ANDA HYROPONICS...***");
  dht.begin();
 
}


//////////////////////////////////// Photon Meter /////////////////////////////////////////////////
void light_fn(){
 float Lgt_1 = analogRead(pht_reader_1);
 float Lgt_2 = analogRead(pht_reader_2);
 float Lgt_3 = analogRead(pht_reader_3);
 float lgt = (Lgt_1 + Lgt_2 + Lgt_3) / 30;
 Serial.print ("LIGHT = ");
 Serial.print (Lgt_1);
 Serial.print (" + ");
 Serial.print (Lgt_2);
 Serial.print (" + ");
 Serial.print (Lgt_3);
 Serial.print (" = ");
 Serial.print (lgt);
 Serial.println (" % light ");
}
///////////////////////////////////// Timer Func //////////////////////////////////////////////////////

void time_fn () {
  Serial.print ("seconds = ");
  Serial.print(secondss);
  Serial.print ("   relay_1_tt = ");
  Serial.print(relay_1_tt);
  Serial.print ("   relay_2_tt = ");
  Serial.println(relay_2_tt);
  secondss -= delay_1 / 1000;
     if (secondss < 1){
      secondss = seconds;

    /////////////////////////////////// minute complate ///////////////////////////////////////////////////
    /////////////////////////////////// realay 1 fn ///////////////////////////////////////////////////////
    relay_1_tt --;
    if (relay_1_tt == 0){
     relay_1_tt = relay_1_t;
      if (water_air_pump_on == 0){
       water_air_pump_on = 1;
     }
     else{
        water_air_pump_on = 0;
        }
      water_air_pump_fn();
     };

     //////////////////////////////////// relay 2 fn //////////////////////////////////////////////////////
     relay_2_tt --;
     if (relay_2_tt == 0){
       relay_2_tt = relay_2_t;
      if (lights_on == 0){
         lights_on = 1;
       }
       else{
         lights_on = 0;
       }
         lights_fn();
       }
     }
}
///////////////////////////////////// Water Air Pump on and OFF /////////////////////////////////////
void water_air_pump_fn(){
  if (water_air_pump_on == 1){
    digitalWrite(relay_1_pin,HIGH);
    Serial.println("PUMPS ARE OPEN ...");
  }else{
    digitalWrite(relay_1_pin,0);
    Serial.println("PUMPS ARE SHUT DOWN ...");
  }
}
///////////////////////////////////// Lights on and OFF /////////////////////////////////////
void lights_fn(){
  if (lights_on == 1){
    digitalWrite(relay_2_pin,HIGH);
    Serial.println("LIGHTS ARE OPEN ...");
  }else{
    digitalWrite(relay_2_pin,0);
    Serial.println("LIGHTS ARE SHUT DOWN ...");
  }
}


///////////////////////////////////// LOOP //////////////////////////////////////////////////////////
void loop() {
 time_fn ();
 light_fn();
 float h = dht.readHumidity();
  // Read temperature as Celsius (the default)
  float t = dht.readTemperature();
  // Check if any reads failed and exit early (to try again).
  if (isnan(h) || isnan(t)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }
  // Compute heat index in Celsius (isFahreheit = false)
  float hic = dht.computeHeatIndex(t, h, false);

  Serial.print("Humidity: ");
  Serial.print(h);
  Serial.print(" %\t");
  Serial.print("Temperature: ");
  Serial.print(t);
  Serial.print(" *C \t");
  Serial.print("Heat index: ");
  Serial.print(hic);
  Serial.println(" *C ");
  delay (delay_1);
}
