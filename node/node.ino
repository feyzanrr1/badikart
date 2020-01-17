#include <SoftwareSerial.h>
SoftwareSerial s(D6,D5);
#include <ArduinoJson.h>
#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <UbidotsESPMQTT.h>
#include "DFRobotDFPlayerMini.h"
#include "Arduino.h"
#include "SoftwareSerial.h"
#include <Servo.h>


#define TOKEN "BBFF-k5o07MwwJPelupJorgVCH1FGQukeSO" // Your Ubidots TOKEN
#define WIFINAME "Sevval" //Your SSIDw
#define WIFIPASS "609sevval" // Your Wifi Pass
#define DEVICE_LABEL "iot"

#define ledPin D0
#define pompaPin D1
#define buzzerPin D2
#define servoPin D3
//#define dfplayerPin D4

int isik;
int nem;
int gaz;
int pir;
int mesafe;
int ledControl;


SoftwareSerial mySoftwareSerial(7, 4); 
DFRobotDFPlayerMini myDFPlayer;                                                
Servo motor;                    

int esikDegeri = 100; 
Ubidots client0(TOKEN, "ryfhrf");
Ubidots client1(TOKEN, "fhjfkl");
Ubidots client2(TOKEN, "khdkda");
Ubidots client3(TOKEN, "dklhdl");
Ubidots client4(TOKEN, "şsmaxx");

void callback(char* topic, byte* payload, unsigned int length) {
  String su =  "/v1.6/devices/iot/supompasi/lv";
  String led = "/v1.6/devices/iot/led/lv";
  String alarm = "/v1.6/devices/iot/alarm/lv";
  String servo = "/v1.6/devices/iot/servo/lv";
//  String dfplayer = "/v1.6/devices/iot/dfplayer/lv";
  String t = topic;
  delay(1000);
  Serial.print("Message arrived [");
  Serial.print(t);
  Serial.print("] ");
  
  for (int i=0;i<length;i++) {
    Serial.print((char)payload[i]);
  }
  Serial.println();
  if(t == led)
  {
    
            if ((char)payload[0]=='1'){
              ledControl = 1;
            digitalWrite(ledPin, HIGH);
        
          }
           else if ((char)payload[0]=='0'){
            digitalWrite(ledPin, LOW);
            ledControl = 0;
        
          } 
          else if ((char)payload[0]=='2'){
            ledControl = 2;
            //led_control();
          } 
  }
  if(t == su)
  {
    
    if ((char)payload[0]=='1'){
      //Serial.println("1 geldi");
    digitalWrite(pompaPin, HIGH);
  }
   else if ((char)payload[0]=='0'){
    //Serial.println("0 geldi");
    digitalWrite(pompaPin, LOW);
  } 
  else if ((char)payload[0]=='2'){
            pompa_control();
          } 
  }
  if(t == alarm)
  {
    
    if ((char)payload[0]=='1'){
      //Serial.println("1 geldi");
    digitalWrite(buzzerPin, HIGH);
    
  }
   else if ((char)payload[0]=='0'){
    //Serial.println("0 geldi");
    digitalWrite(buzzerPin, LOW);
    
    
  }
  else if ((char)payload[0]=='2'){
            gaz_control();
          }  
  }
    if(t == servo)
  {
    
    if ((char)payload[0]=='1'){
      //Serial.println("1 geldi");
    digitalWrite(servoPin, HIGH);
    motor.write(30);
    delay(250);
    motor.write(150);
    delay(250);
    motor.write(30);
    delay(250);
    motor.write(150);
    delay(250);
    motor.write(30);
    delay(250);
    motor.write(90);
                  
  }
   else if ((char)payload[0]=='0')
   {
    //Serial.println("0 geldi");
    digitalWrite(servoPin, LOW);
    }
    else if ((char)payload[0]=='2'){
            servo_control();
          } 
   
  }
//    if(t == dfplayer)
//  {
//    
//    if ((char)payload[0]=='1'){
//      //Serial.println("1 geldi");
//    digitalWrite(dfplayerPin, HIGH);
//  }
//   else if ((char)payload[0]=='0'){
//    //Serial.println("0 geldi");
//    digitalWrite(dfplayerPin, LOW);
//  } 
//  }
  //Serial.println("0000000000000000000000000000000000000000000");
   
  
  //delay(4000);
}

   void led_control()
   {
    if(nem < 800 ){                        
      if(isik > 400){ 
      digitalWrite(ledPin, LOW);
      Serial.println("LED L");
       }
      else{ 
          digitalWrite(ledPin, HIGH);  
          Serial.println("LED H");
        }
    }else{
      digitalWrite(ledPin, LOW);
      Serial.println("LED DEVRE DIŞI");
    }
 }
 void pompa_control()
   {
    if(nem > 800 ){ 
    digitalWrite(pompaPin, HIGH);
//    delay(100);
//    digitalWrite(pompaPin, LOW);
//    delay(100);  
Serial.println("POMPA H");             
    }
    else{ 
          digitalWrite(pompaPin, LOW);
          Serial.println("POMPA L");  
        }
    }

    void gaz_control(){
  
    if(gaz > esikDegeri){ 
  
    digitalWrite(buzzerPin, HIGH);
//    delay(100);
//    digitalWrite(buzzerPin, LOW);
//    delay(100);  
Serial.println("GAZ H");      
  }
  else{                             
    digitalWrite(buzzerPin, LOW);
    Serial.println(" GAZ L");
  }
  }

  
   void servo_control()
   {
      if (pir == 1)
         {
           Serial.println(" SERVO H");
             digitalWrite(servoPin, HIGH);
              motor.write(30);
              delay(250);
              motor.write(150);
              delay(250);
              motor.write(30);
              delay(250);
              motor.write(150);
              delay(250);
              motor.write(30);
              delay(250);
              motor.write(90);
          }
          else 
          { 
            Serial.println(" SERVO L");
             digitalWrite(servoPin, LOW);
          }
  }
  void dfplayer_control(){
  
     if(isik < 500)
        { Serial.println("Gece");
                 if (pir == 1) 
                 {
                    Serial.println("HAreket var");
                    if (mesafe > 200 || mesafe < 0)
                    {
//                      myDFPlayer.play(2);
//                      myDFPlayer.volume(30);
                    Serial.println("Menzil Disi");
                    }
                    if (mesafe < 100 && mesafe >= 50)
                    {
//                      myDFPlayer.play(2);
//                      myDFPlayer.volume(15);
                      Serial.println("Menzil1 Disi");
                    }
                     if (mesafe < 50 && mesafe >= 0)
                    {
//                      myDFPlayer.play(2);
//                      myDFPlayer.volume(30);
                      Serial.println("Menzil3 Disi");
                    }
                   }  
       }
  }
  
 
void setup() {
  
  pinMode(ledPin, OUTPUT);
  pinMode(pompaPin, OUTPUT);
  pinMode(buzzerPin, OUTPUT);
  pinMode(servoPin, OUTPUT);
//  pinMode(dfplayerPin, OUTPUT);
  Serial.begin(9600);
  s.begin(19200);
//  client0.wifiConnection(WIFINAME, WIFIPASS);
  connectToWifi();
  //client0.wifiConnection(WIFINAME, WIFIPASS);
  client0.ubidotsSetBroker("industrial.api.ubidots.com"); 
  client0.setDebug(true); // Pass a true or false bool value to activate debug messages
  client0.begin(callback);
  client1.ubidotsSetBroker("industrial.api.ubidots.com"); 
  client1.setDebug(true);
  client1.begin(callback);
  client2.ubidotsSetBroker("industrial.api.ubidots.com"); 
  client2.setDebug(true);
  client2.begin(callback);
  client3.ubidotsSetBroker("industrial.api.ubidots.com"); 
  client3.setDebug(true);
  client3.begin(callback);
  client4.ubidotsSetBroker("industrial.api.ubidots.com"); 
  client4.setDebug(true);
  client4.begin(callback);
//  client4.ubidotsSetBroker("industrial.api.ubidots.com"); 
//  client4.setDebug(true);
//  client4.begin(callback);
  
  //client0.add("led", 0); //Insert your variable Labels and the value to be sent
  //client0.ubidotsPublish("iot");
  
  client1.add("supompasi", 0); 
  client1.ubidotsPublish("iot");
  
  client2.add("alarm", 0); 
  client2.ubidotsPublish("iot");

  client3.add("servo", 0); 
  client3.ubidotsPublish("iot");

  client4.add("led", 0); //Insert your variable Labels and the value to be sent
  client4.ubidotsPublish("iot");

//  client2.add("dfplayer", 0); 
//  client2.ubidotsPublish("iot");

  //client0.ubidotsSubscribe("iot","led");
  client1.ubidotsSubscribe("iot","supompasi");
  client2.ubidotsSubscribe("iot","alarm");
  client3.ubidotsSubscribe("iot","servo");
  client4.ubidotsSubscribe("iot","led");
//  client4.ubidotsSubscribe("iot","dfplayer");

   motor.attach(servoPin);   
}

void offline()
{
  while (WiFi.status() != WL_CONNECTED) 
          {
            yield();
            if(!json_al())continue;
            led_control();
            
            pompa_control();
            
            gaz_control();
            
            servo_control();
            
            dfplayer_control();
            delay(1000);
          }
          
}

void connectToWifi()
{
  int baslamaZamani = millis();
  while (WiFi.status() != WL_CONNECTED) 
          {
            delay(500);
            Serial.print(".");
            if(millis() - baslamaZamani > 10000)
            {
              Serial.println("Offline");
              offline();
            }
          }
            Serial.println("Online");
      
}
bool json_al(){
  Serial.println("veri");
  StaticJsonBuffer<200> jsonBuffer;
  JsonObject& root = jsonBuffer.parseObject(s);
  if (root == JsonObject::invalid())
    return false;
  root.prettyPrintTo(Serial);
   nem = root["nem"];
   isik = root["isik"];
   gaz = root["gaz"];
   pir = root["pir"];
   mesafe = root["mesafe"];
    return true;
  }
void loop() {
  if(WiFi.status() != WL_CONNECTED) 
          {
            connectToWifi();
            //client0.ubidotsSubscribe("iot","led");
            client1.ubidotsSubscribe("iot","supompasi");
            client2.ubidotsSubscribe("iot","alarm");
            client3.ubidotsSubscribe("iot","servo");
            client4.ubidotsSubscribe("iot","led");
          }
         if(!json_al())return; 

  if(ledControl == 2)
  {
    led_control();
  }
  
  client0.add("isik", isik); 
  client0.add("nem", nem);
  client0.add("gaz", gaz);
  client0.ubidotsPublish("iot");

  client0.loop();
  client1.loop();
  client2.loop();
  client3.loop();
  client4.loop();

}
