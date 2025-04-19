#include <SoftwareSerial.h>
#define rxPin 8 //Broche 8 en tant que RX, � raccorder sur TX du HC-05
#define txPin 7 //Broche 7 en tant que RX, � raccorder sur TX du HC-05
#define graphPin A0
#define baudrate 9600
SoftwareSerial mySerial(rxPin ,txPin); //D�finition du software serial
// unsigned long previousMillis = 0;
// const long interval = 1000; // 1 seconde

/////// Il faut se connecter d'abord sur le smartphone avec l'appli "serial bluetooth terminal" 
////// Le nom de notre module est HC0523
////// On peut communiquer avec le smartphone en envoyant un message depuis le pc et inversement

void setup(){
  pinMode(rxPin,INPUT);
  pinMode(txPin,OUTPUT);    
  mySerial.begin(baudrate);
  Serial.begin(baudrate);
}

void loop(){
  // unsigned long currentMillis = millis();

  // if (currentMillis - previousMillis >= interval) {
  //   previousMillis = currentMillis;

    int analogValue = analogRead(graphPin);
    float Y = analogValue;
    Serial.println(Y);
    mySerial.println(Y);
    delay(200);
    // mySerial.println(";");
    // mySerial.println(currentMillis);
  //  }
}