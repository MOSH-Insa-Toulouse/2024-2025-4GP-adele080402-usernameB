/*
MCP41xxx Digital Pot Control
 
This example controls an MCP41xxx digital potentiometer.
PBn - One side of potentiometer
PWn - Pot wiper
PAn - Other side of potentiometer
 
The MCP41xxx is SPI-compatible. The hardware is managed by 
sending two bytes:
BYTE 1 - is a command byte (NOP, WRITE, SHUTDOWN)
BYTE 2 - is the data byte (new setpoint value 0-255). 
 
The MCP IC circuit:
* PB0 to ground 
* PA0 to Vcc
* PW0 Connect a multimeter between PW0 and ground to measure resistance 
* CS - to digital pin 10 (SS pin)
* SDI - to digital pin 11 (MOSI pin)
* CLK - to digital pin 13 (SCK pin)
*/

#include <SPI.h>

// Define the MCP41100 OP command bits (only one POT)
// Note: command byte format xxCCxxPP, CC command, PP pot number (01 if selected) 
#define MCP_NOP 0b00000000
#define MCP_WRITE 0b00010001
#define MCP_SHTDWN 0b00100001

const int ssMCPin = 10; // Define the slave select for the digital pot

#define WAIT_DELAY 500

void SPIWrite(uint8_t cmd, uint8_t data, uint8_t ssPin) // SPI write the command and data to the MCP IC connected to the ssPin
{
  SPI.beginTransaction(SPISettings(14000000, MSBFIRST, SPI_MODE0)); //https://www.arduino.cc/en/Reference/SPISettings
  
  digitalWrite(ssPin, LOW); // SS pin low to select chip
  
  SPI.transfer(cmd);        // Send command code
  SPI.transfer(data);       // Send associated value
  digitalWrite(ssPin, HIGH);// SS pin high to de-select chip
  SPI.endTransaction();
}

void initialize() {                     // send the command byte of value 100 (initial value)
  spi_out(CLKpin, cmd_byte2, initial_value);
}

void spi_out(int CS, byte cmd_byte, byte data_byte){                        // we need this function to send command byte and data byte to the chip
    
    digitalWrite (CS, LOW);                                                 // to start the transmission, the chip select must be low
    spi_transfer(cmd_byte); // invio il COMMAND BYTE
    delay(2);
    spi_transfer(data_byte); // invio il DATA BYTE
    delay(2);
    digitalWrite(CS, HIGH);                                                 // to stop the transmission, the chip select must be high
}

void spi_transfer(byte working) {
    for(int i = 1; i <= 8; i++) {                                           // Set up a loop of 8 iterations (8 bits in a byte)
     if (working > 127) { 
       digitalWrite (MOSI_signal,HIGH) ;                                    // If the MSB is a 1 then set MOSI high
     } else { 
       digitalWrite (MOSI_signal, LOW) ; }                                  // If the MSB is a 0 then set MOSI low                                           
    
    digitalWrite (CLK_signal,HIGH) ;                                        // Pulse the CLK_signal high
    working = working << 1 ;                                                // Bit-shift the working byte
    digitalWrite(CLK_signal,LOW) ;                                          // Pulse the CLK_signal low
    }
}

void setup() 
{
  pinMode (ssMCPin, OUTPUT); //select pin output
  digitalWrite(ssMCPin, HIGH); //SPI chip disabled
  SPI.begin(); 
 
  Serial.begin(57600);
  Serial.println(F("[MCP Digital Pot Test]")); //print to serial
}

void loop() 
{
  // step through the range of the digital pot
  for (int i = 0; i < 256; i++) 
  {
    Serial.println(i);
    SPIWrite(MCP_WRITE, i, ssMCPin);
    delay(WAIT_DELAY);
  }
  delay (WAIT_DELAY*5);
}
