/* Health Monitioring System using NodeMCU and ThingSpeak
 *  Author @ Dr.Rishabh Raj
 */


#include "ThingSpeak.h"
#include <ESP8266WiFi.h>
#include <Wire.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#include <SimpleTimer.h>
#define ONE_WIRE_BUS 14 //Data pin of DS18B20 at D1 in NodeMCU

const char *ssid     = "iPhone 12";     //  WiFi name
const char *password = "monday456";    // WiFi password

 //---------------------Channel Details--------------------//
unsigned long Channel_ID = 1427538; // Channel ID
const char *WriteAPIKey = "17MUQ90S3BKG9ARH"; // Your write API Key

WiFiClient client;

OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);

const int pulseSensorPin = A0;
int signal;
int led = 16;

int d =0,f=0;
#define UpperThreshold 550
#define LowerThreshold 530

 
void setup() {
Serial.begin(9600);
pinMode(pulseSensorPin, INPUT);
delay(100);

WiFi.begin(ssid, password);
  while ( WiFi.status() != WL_CONNECTED ) {
    delay ( 500 );
    Serial.print ( "WiFi Not Connected" );
  }
sensors.begin(); //start up the library  
ThingSpeak.begin(client);

delay(100);
}
 
void loop() {
   
//ThisTime=millis();
signal = analogRead(pulseSensorPin);  // Read the PulseSensor's value and assign it to signal
Serial.println(signal);

if(signal > UpperThreshold){                          // If the signal is above "550", then "turn-on" Arduino's on-Board LED.
     digitalWrite(led,HIGH);
     } else {
     digitalWrite(led,LOW);                //  Else, the sigal must be below "550", so "turn-off" this LED.
   }
d = ThingSpeak.writeField(Channel_ID, 1, signal, WriteAPIKey);
delay(100);


sensors.requestTemperatures();
float temp = sensors.getTempCByIndex(0);
Serial.println(temp);
f = ThingSpeak.writeField(Channel_ID, 2, temp, WriteAPIKey);
}
