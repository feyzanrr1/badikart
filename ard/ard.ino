#define PIR_INPUT 11  //  sensor pir out
#include "Arduino.h"
#include "SoftwareSerial.h"
#include <ArduinoJson.h>
SoftwareSerial mySoftwareSerial(5, 6); 
#define trigPin 7
#define echoPin 8
#define nemPin A1
#define isikPin A0
#define gazPin A2

void setup() {
  mySoftwareSerial.begin(19200);
  Serial.begin(9600);  
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(PIR_INPUT, INPUT);  
}

void loop() {
  int isik = analogRead(isikPin); //Işık değişkenini A0 pinindeki LDR ile okuyoruz
  int nem = analogRead(nemPin);
  int gaz = analogRead(gazPin);
  int pir = digitalRead(PIR_INPUT);                 
  long sure, mesafe;
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  sure = pulseIn(echoPin, HIGH);
  mesafe = sure/58.2;
  //Serial.println(isik);
  //Serial.println(pir);
  //Serial.println(mesafe);
  
  StaticJsonBuffer<200> jsonBuffer;
  JsonObject& root = jsonBuffer.createObject();
  root["isik"] = isik;
  root["pir"] = pir;
  root["mesafe"] = mesafe;
  root["nem"] = nem;
  root["gaz"] = gaz;
  //root.prettyPrintTo(Serial);
//if(mySoftwareSerial.available()>0)
//{
  root.prettyPrintTo(Serial);
 root.printTo(mySoftwareSerial);
//}
  //delay(500);
} 
