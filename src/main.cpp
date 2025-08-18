#include <Arduino.h>
#include "shock.h"
#include "polarity.h"
#include "sample.h"
#include "SerialTransfer.h"
#include "spi_dac.h"

// Serial Transfer from python script
SerialTransfer myTransfer;

// Cells
Cell cell_1 = {CELL1};
Cell cell_2 = {CELL2};
Cell cell_3 = {CELL3};
Cell cell_4 = {CELL4};
Cell cell_5 = {CELL5};
Cell cell_6 = {CELL6};
Cell cell_7 = {CELL7};
Cell cell_8 = {CELL8};
Cell cell_9 = {CELL9};
Cell cell_10 = {CELL10};
Cell cell_11 = {CELL11};
Cell cell_12 = {CELL12};


Cell* cells[] = {&cell_1, &cell_2, &cell_3, &cell_4, &cell_5, &cell_6,
                       &cell_7, &cell_8, &cell_9, &cell_10, &cell_11, &cell_12};
                       
const uint8_t NUM_CELLS = sizeof(cells) / sizeof(cells[0]);

void setup() {

  // Initialize Serial
  Serial.begin(115200);
  while (!Serial);
  Serial.println("Initializing Setup");

  // Initialize shock setup (Pins, Timers, etc.)
  shock_setup();

  // Initialize polarity setup (Pins, Timers, etc.)
  // polarity_setup();

  // Initialize SPI and DAC
  DACSetup();

  // Initialize Serial for python script
  // myTransfer.begin(Serial);

  //? Debug LED
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, LOW);

  Serial.println("\nFishShocker9000: Setup Complete\n");
} 

void loop() {
 
  // if(myTransfer.available())
  // {
  //   // Declare Variable to store 
  //   uint16_t data;
  //   uint16_t value;

  //   // send all received data back to Python
  //   for(uint16_t i=0; i < myTransfer.bytesRead; i++)
  //     myTransfer.packet.txBuff[i] = myTransfer.packet.rxBuff[i];
    
  //   myTransfer.sendData(myTransfer.bytesRead);

  //   myTransfer.rxObj(data);
  //   value = int(data);

  //   if(value == 1){
  //     digitalWrite(LED_BUILTIN, !(digitalRead(LED_BUILTIN)));
  //   }
  // }

  writeDAC(12);


}

