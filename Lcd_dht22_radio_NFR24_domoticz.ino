#define MY_RADIO_NRF24 

#define MY_NODE_ID 1 


#include <MySensors.h> 
#include "DHT.h" 
#include <DHT.h> 
#include <LCD.h> 
#include <Wire.h> 

#include <LiquidCrystal_I2C.h> 


#define DHTPIN 6     // what digital pin we're connected to 

#define DHTTYPE DHT22   // DHT 22  (AM2302), AM2321 

DHT dht(DHTPIN, DHTTYPE); 
unsigned long MY_SLEEP_TIME = 300000;// tempo attesa 

//ALWAYS USE THIS WITH LCD I2C and Addres 0x3F 
#define I2C_ADDR 0x3F 
#define BACKLIGHT_PIN 3 
#define En_pin 2 
#define Rw_pin 1 
#define Rs_pin 0 
#define D4_pin 4 
#define D5_pin 5 
#define D6_pin 6 
#define D7_pin 7 
LiquidCrystal_I2C lcd(I2C_ADDR,En_pin,Rw_pin,Rs_pin,D4_pin,D5_pin,D6_pin,D7_pin); 


//ASSEGNARE NODO 
#define CHILD_ID_TEMP 0 
#define CHILD_ID_HUM 1 


//MyMessage 
MyMessage msgTemp (CHILD_ID_TEMP,V_TEMP); 
MyMessage msgHum (CHILD_ID_HUM,V_HUM); 




void setup() { 

  lcd.begin(16,2); 
  lcd.setBacklightPin(BACKLIGHT_PIN,POSITIVE); 
  lcd.setBacklight(HIGH); 



Serial.begin(115200); 
  Serial.println("DHTxx test!"); 

  dht.begin(); 




} 


void presentation(){ 
sendSketchInfo("Jordan - termostato", "1.1"); 
present(CHILD_ID_TEMP,S_TEMP); 
present(CHILD_ID_HUM,S_HUM); 
} 

void loop() { 



  float t= dht.readTemperature(); 
  float h= dht.readHumidity(); 
  send (msgTemp.set(t ,2)); 
  send (msgHum.set(h ,2)); 


 lcd.clear();
 lcd.setCursor(0,0); 
lcd.print("Temp: ");     
lcd.print(t);
 lcd.print(" ");
 lcd.print((char)223); 
lcd.print("C"); 
lcd.setCursor(0,1); 
lcd.print("Hum: "); 
lcd.print(h); 
lcd.print(" %"); 

  

  //sleep(MY_SLEEP_TIME); //COME DELAY 
  wait(MY_SLEEP_TIME); 
}
