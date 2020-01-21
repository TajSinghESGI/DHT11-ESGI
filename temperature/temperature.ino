#include "DHT.h"        // including the library of DHT11 temperature and humidity sensor
#define DHTTYPE DHT11   // DHT 11

#define dht_dpin D4
DHT dht(dht_dpin, DHTTYPE); 


float temp[10];
float hum[10];
float moyenneT = 0;
float new_moyT = 0;
float new_moyH = 0;
float moyenneH = 0;
float sumT = 0;
float sumH = 0;

int i=0;
void setup(void)
{ 
  dht.begin();
  pinMode(D2, OUTPUT);
  pinMode(D1, OUTPUT);
  pinMode(D3, OUTPUT);
  pinMode(D4, OUTPUT);
  Serial.begin(9600);
  delay(500);

}
void loop() {
    float h = dht.readHumidity();
    float t = dht.readTemperature();         
    
    if(i < 10) {
      temp[i] = t;
      hum[i] = h;
  
      i++;
    } else {
      
      for(int j = 0; j < 9; j++){
        temp[j] = temp[j+1];
      }
      temp[9] = t;
      for(int x = 0; x < 10; x++){
        sumT += temp[x];
      }
      moyenneT = sumT/10;
      digitalWrite(D2, LOW);
      digitalWrite(D1, LOW);
      sumT = 0;
      
      for(int j = 0; j < 9; j++){
        hum[j] = hum[j+1];
      }
      hum[9] = h;
      for(int y = 0; y < 10; y++){
        sumH += hum[y];
      }
      moyenneH = sumH/10;
      
      sumH = 0;

      Serial.print("Moyenne Humidié = ");
      Serial.print(moyenneH);
      Serial.print("\t");
      Serial.print("Moyenne Temperature = ");
      Serial.println(moyenneT);
      

      if(new_moyH != moyenneH){
        if(new_moyH > moyenneH){
          digitalWrite(D2, HIGH);
          digitalWrite(D1, LOW);
        } else {
          digitalWrite(D2, LOW);
          digitalWrite(D1, HIGH);
        }
      }

      if(new_moyT != moyenneT){
        if(new_moyT > moyenneT){
          digitalWrite(D3, HIGH);
          digitalWrite(D3, LOW);
        } else {
          digitalWrite(D3, LOW);
          digitalWrite(D4, HIGH);
        }
      }
      new_moyT = moyenneT;
      new_moyH = moyenneH;
      moyenneT = 0;
      moyenneH = 0;
      
    }
   
  delay(500);
}
