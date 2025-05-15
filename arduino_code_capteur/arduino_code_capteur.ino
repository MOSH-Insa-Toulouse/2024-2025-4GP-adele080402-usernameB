
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
#define rxPin 8 //Broche 8 en tant que RX, a raccorder sur TX du HC-05
#define txPin 7 //Broche 7 en tant que RX, a raccorder sur TX du HC-05
SoftwareSerial Bluetooth(rxPin ,txPin); //Definition du software serial

// Flex Sensor commercial
const int flexPin = A1;
const float VCC = 5.0;      // voltage at Arduino 5V line
const float R_DIV = 10000.0;  // resistor used to create a voltage divider
const float flatResistance = 36000.0; // resistance when flat
const float bendResistance = 102000.0;  // resistance at 90 deg
const float kohm = 0.001; //convert resistance value to kohms (simplifies the display)

//Graphite sensor
const int graphPin = A0;
const float R8 = 100000;
const float R4 = 100000;
float R2 = 50000; //A modifier c'est la valeur du pot digital
const float R5 = 10000;
const float Mohm = 0.000001;


// Digital Potentiometer
#define CSpin 10
#define SDIpin 11
#define SCKpin 13
#define MCP_NOP 0b00000000
#define MCP_WRITE 0b00010001
#define MCP_SHTDWN 0b00100001
const byte address = 0x11;
int pos = 0;      // pour déterminer R2 (potentiomètre) (0<pos<255) , plus pos -> 0, plus R2 est grand


// Rotatory Encoder 
#define encodeur0pinA 2
#define encodeur0pinB 4
#define SWITCHpin 5
// int encodeurVal = 0;
// int lastEncodeurVal = 0;
// int encodeurValB =0;
// bool buttonPressed = false;

// //Menu variables
// volatile int menuIndex = 0;
// int lastMenuIndex = -1;
// bool inSubMenu = false;
// int currentMenu =-1; // valeur du menu principal
// String menus[] = {"graph","flex","pot"};
// const int menuCount = sizeof(menus) / sizeof(menus[0]);


#define baudrate 9600

void setup() {

  Serial.begin(baudrate);

  // Initialisation de l'écran OLED
  if(!ecranOLED.begin(SSD1306_SWITCHCAPVCC, adresseI2CecranOLED)){
    while(1);                               // Arrêt du programme (boucle infinie) si échec d'initialisation
  }
  
  ecranOLED.clearDisplay();                                            // Effaçage de l'intégralité du buffer

  // Initialisation pins
  pinMode(rxPin,INPUT);
  pinMode(txPin,OUTPUT);
  pinMode(flexPin, INPUT);
  pinMode(CSpin, OUTPUT);
  // pinMode(encodeur0pinA,INPUT);
  // pinMode(encodeur0pinB,INPUT);
  // pinMode(SWITCHpin, INPUT);



  //Potentiometer setup
  digitalWrite(CSpin,HIGH); //SPI chip disabled
  SPI.begin();
  int R2 = digitalPotWrite(pos);

  // //Encodeur rotatoire setup
  // digitalWrite(encodeur0pinA, HIGH);
  // digitalWrite(encodeur0pinB, HIGH);
  // // attachInterrupt(0,doEncoder,RISING);

}

//////////////Digital Potentiometer///////////////////////////

float digitalPotWrite (int value){

  digitalWrite(CSpin, LOW);
  SPI.transfer(address);
  SPI.transfer(value);
  digitalWrite(CSpin, HIGH);
  float Rdp = (50000.0 * (255 - value)) / 255.0; 
  //Serial.println(Rdp);
  return Rdp;
}

///////////////////Measure/////////////////////////////////////////

float flexMeasure() {

  // Read the ADC, and calculate voltage and resistance from it
  int ADCflex = analogRead(flexPin);
  float Vflex = ADCflex * VCC / 1024.0;
  float Rflex = (R_DIV * (VCC / Vflex - 1.0))*kohm;
  Serial.println("Resistance : " + String(Rflex) + " kohms");
  // Use the calculated resistance to estimate the sensor's bend angle:
  float angle = map(Rflex/kohm, flatResistance, bendResistance, 0, 90.0);
  Serial.println("Bend : " + String(angle) + " degrees");
  Serial.println();
  delay(100);
  return angle;
}

float graphiteMeasure () {

  float V = analogRead(graphPin);
  Serial.println("V =" + String(V));
  float Vadc = V*5.0/1024.0;
  Serial.println("Vadc =" + String(Vadc));
  float Rg = (R8*(1+R4/R2)*(VCC/Vadc)-R8-R5)*kohm;
  Serial.println("Rgraphite ="+ String(Rg) + "kohms");
  delay(200);
  return V;

}

//////////////BLUETOOTH/////////////////////////////

void bluetooth () {
  int analogValue = analogRead(graphPin);
  float Y = analogValue;
  Bluetooth.println(Y);
  delay(200);
}


/////////////// FONCTIONS DISPLAY MENUS////////////////////
void principalMenu() {

  ecranOLED.clearDisplay();
  ecranOLED.setCursor(0, 0);
  int tailleDeCaractere=1;
  ecranOLED.setTextColor(SSD1306_WHITE, SSD1306_BLACK); // Couleur du texte, et couleur du fond
  ecranOLED.setTextSize(tailleDeCaractere);
  ecranOLED.println("Graphite Sensor");
  ecranOLED.println("Flex Sensor");
  ecranOLED.println("Digital Potentiometer");
  ecranOLED.display();
  
}

void graphiteMenu(float V) {

  ecranOLED.clearDisplay(); // Effaçage de l'intégralité du buffer
  ecranOLED.setCursor(0, 0);

  //for(byte numeroDeLigne=1; numeroDeLigne<=8; numeroDeLigne++) {
  int tailleDeCaractere=1;
  float Vadc = V*5.0/1024;

  ecranOLED.setTextColor(SSD1306_WHITE, SSD1306_BLACK); // Couleur du texte, et couleur du fond
  ecranOLED.setTextSize(tailleDeCaractere);
  ecranOLED.println("--Menu GraphSensor--");
  ecranOLED.println();
  ecranOLED.print("Tension =");
  ecranOLED.println(Vadc);
  ecranOLED.print("R =");
  ecranOLED.print((R8*(1+R4/R2)*(VCC/Vadc)-R8-R5)*kohm);
  ecranOLED.println(" kOhm");
  ecranOLED.println();
  ecranOLED.print("             BACK");
  ecranOLED.display(); // Transfert le buffer à l'écran
  delay(200);
  ecranOLED.clearDisplay();
  ecranOLED.setCursor(0, 0);
}

void flexMenu(float angle) {

  int ADCflex = analogRead(flexPin);
  float Vflex = ADCflex * VCC / 1023.0;
  int tailleDeCaractere=1;
  
  ecranOLED.clearDisplay();
  ecranOLED.setCursor(0, 0);

  ecranOLED.setTextColor(SSD1306_WHITE, SSD1306_BLACK); // Couleur du texte, et couleur du fond
  ecranOLED.setTextSize(tailleDeCaractere);
  ecranOLED.println(" --Menu FlexSensor--");
  ecranOLED.println();
  ecranOLED.print("R=");
  ecranOLED.println(String((R_DIV * (VCC / Vflex - 1.0))*kohm) +"Kohms");
  ecranOLED.print("Angle =");
  ecranOLED.println(String(angle) + "degrees");
  ecranOLED.println();
  ecranOLED.print("             BACK");

  delay(500);
  ecranOLED.display();
}

void potMenu(float Rdp) {

  ecranOLED.clearDisplay();
  ecranOLED.setCursor(0, 0);
  int tailleDeCaractere = 1;

  ecranOLED.setTextColor(SSD1306_WHITE, SSD1306_BLACK); // Couleur du texte, et couleur du fond
  ecranOLED.setTextSize(tailleDeCaractere);
  ecranOLED.println("-Menu Potentiometre-");
  ecranOLED.println();
  ecranOLED.print("Rdp =");                           //Résistance choisie pour le potentiomètre digital
  ecranOLED.println(String(Rdp)+"ohms");
  ecranOLED.println();
  ecranOLED.println();
  ecranOLED.print("             BACK");

  delay(500);
  ecranOLED.display();
  
}
//////////////////////////////////////////////////////////////////////////////




void loop() {
graphiteMeasure();
graphiteMenu(graphiteMeasure());
delay(100);

//digitalPotWrite(0);
// delay(500);
// flexMenu(flexMeasure());
// //bluetooth();
// delay(500);
}