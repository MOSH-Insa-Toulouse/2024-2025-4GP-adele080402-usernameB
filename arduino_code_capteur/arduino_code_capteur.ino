
////////////// INCLUSION DES BIBLIOTHEQUES////////////

#include <Adafruit_SSD1306.h>               // Bibliothèque de l'écran OLED
#include <SPI.h>                            // Bibliothèque pour communiquer avec le potentiomètre digital
#include <SoftwareSerial.h>                 // Bibliothèque pour gérer la communication avec l'appareil bluetooth

////////////// DEFINITION VARIABLES ////////////

// Ecran OLED
#define nombreDePixelsEnLargeur 128         // Taille de l'écran OLED, en pixel, au niveau de sa largeur
#define nombreDePixelsEnHauteur 64          // Taille de l'écran OLED, en pixel, au niveau de sa hauteur
#define brocheResetOLED         -1          // Reset de l'OLED partagé avec l'Arduino (d'où la valeur à -1, et non un numéro de pin)
#define adresseI2CecranOLED     0x3C        // Adresse de "mon" écran OLED sur le bus i2c (généralement égal à 0x3C ou 0x3D) 
Adafruit_SSD1306 ecranOLED(nombreDePixelsEnLargeur, nombreDePixelsEnHauteur, &Wire, brocheResetOLED);


// Module bluetooth
#define rxPin 11 //Broche 11 en tant que RX, a raccorder sur TX du HC-05
#define txPin 10 //Broche 10 en tant que RX, a raccorder sur TX du HC-05
SoftwareSerial mySerial(rxPin ,txPin); //Definition du software serial

// Flex Sensor commercial
const int flexPin = A0;
const float VCC = 5.0;      // voltage at Arduino 5V line
const float R_DIV = 10000.0;  // resistor used to create a voltage divider
const float flatResistance = 32600.0; // resistance when flat
const float bendResistance = 101000.0;  // resistance at 90 deg

//Graphite sensor
const float R8 = 100000;
const float R4 = 100000;
const float R2 = 50000; //A modifier c'est la valeur du pot digital
const float R5 = 10000;

#define baudrate 9600

void setup() {

  Serial.begin(baudrate);

  // Initialisation de l'écran OLED
  if(!ecranOLED.begin(SSD1306_SWITCHCAPVCC, adresseI2CecranOLED)){
    while(1);                               // Arrêt du programme (boucle infinie) si échec d'initialisation
  }
  
  ecranOLED.clearDisplay();                                            // Effaçage de l'intégralité du buffer

  for(byte numeroLigne=0 ; numeroLigne < nombreDePixelsEnHauteur ; numeroLigne++) {
    for(byte numeroColonne=0 ; numeroColonne < nombreDePixelsEnLargeur ; numeroColonne++) {
      //delay(50);
      ecranOLED.drawPixel(numeroColonne, numeroLigne, WHITE);          // On demande l'allumage de chaque pixel, un à un, avec la commande : drawPixel(posX,posY,couleur);
    }
  }

  ecranOLED.display();

  // Initialisation pins
  pinMode(rxPin,INPUT);
  pinMode(txPin,OUTPUT);
  pinMode(flexPin, INPUT);

}

void flexMeasure() {

  // Read the ADC, and calculate voltage and resistance from it
  int ADCflex = analogRead(flexPin);
  float Vflex = ADCflex * VCC / 1023.0;
  float Rflex = R_DIV * (VCC / Vflex - 1.0);
  Serial.println("Resistance : " + String(Rflex) + " ohms");
  // Use the calculated resistance to estimate the sensor's bend angle:
  float angle = map(Rflex, flatResistance, bendResistance, 0, 90.0);
  Serial.println("Bend : " + String(angle) + " degrees");
  Serial.println();

  delay(500);
  
}

void graphiteMeasure () {
  
  float V = analogRead(A0);
  Serial.println("V =" + String(V));
  float Vadc = V*5.0/1024;
  Serial.println("Vadc =" + String(Vadc));
  float Rg = (R8*(1+R4/R2)*(VCC/Vadc)-R8-R5);
  Serial.println("Rgraphite ="+ String(Rg));

}

void loop() {

  //graphiteMeasure();
  //delay(500);


}
