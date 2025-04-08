#include <SPI.h>

// Define the MCP41100 OP command bits (only one POT)
// Note: command byte format xxCCxxPP, CC command, PP pot number (01 if selected) 
#define MCP_NOP 0b00000000
#define MCP_WRITE 0b00010001
#define MCP_SHTDWN 0b00100001

const int ssMCPin = 10; // Define the slave select for the digital pot

#define WAIT_DELAY 5000
uint16_t cmd = 0b0011000000000000

void setup() {

  // put your setup code here, to run once:


}

void loop() {
 
  // put your main code here, to run repeatedly:
  for (uint16_t adresse=0; adresse<2047; adresse++){

    uint16_t cmdfinal=cmd|adresse;

    for (uint16_t index=13;index>0;index--){
      
    }
    for (uint16_t index=0;index<7;index++){

    }


  }
}
