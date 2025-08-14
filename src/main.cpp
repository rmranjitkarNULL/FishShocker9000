#include <Arduino.h>
#include "shock.h"
#include "polarity.h"
#include "sample.h"
#include "SerialTransfer.h"

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
  polarity_setup();

  // Initialize Serial for python script
  myTransfer.begin(Serial);

  Serial.println("FishShocker9000: Setup Complete\n");
} 

void loop() {
 
  // // * This will become a CAN Interrupt in the future. Potentially need FIFO for that.
  // if(myTransfer.available())
  // {
  //   uint16_t cell_id;

  //   // send all received data back to Python
  //   for(uint16_t i=0; i < myTransfer.bytesRead; i++)
  //     myTransfer.packet.txBuff[i] = myTransfer.packet.rxBuff[i];
    
  //   myTransfer.sendData(myTransfer.bytesRead);

  //   // Save recievbed data to circular buffer
  //   myTransfer.rxObj(cell_id);
  // }

  

}

// Test new timing to make sure it works
// Add Fifo for can
// ensure everything works and create a demo for it