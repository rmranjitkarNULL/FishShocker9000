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

// Declare Variable to store for pyserial
char ch;

// key Mapping to cells
const char keyMap[NUM_CELLS] = {
    '1','2','3','4','5','6','7','8','9','0','-','='
};

uint32_t keyLastSeen[12] = {0};
const uint32_t KEY_TIMEOUT = 50;  // ms or ticks


void setup() {

  // Initialize Serial
  Serial.begin(115200);
  while (!Serial);
  Serial.println("Initializing Setup\n");

  // Initialize shock setup (Pins, Timers, etc.)
  shockSetup();

  // Initialize polarity setup (Pins, Timers, etc.)
  polarity_setup();

  // Initialize SPI and DAC
  setupDAC();

  // Initialize Serial for python script
  myTransfer.begin(Serial);

  Serial.println("\nFishShocker9000: Setup Complete\n");

  // * Testing: Set all cells to have the fish "in_zone" so the shocks can turn on
  for(int i = 0; i < NUM_CELLS; i++){
      cells[i]->in_zone = true;
  }

  writeDAC(0.75);

} 

void loop() {

  // if (myTransfer.available()) {

  //   // Receive a single character
  //   myTransfer.rxObj(ch);

  //   // Echo back to Python (optional, but matches your Python code)
  //   uint16_t sendSize = 0;
  //   sendSize += myTransfer.txObj(ch);
  //   myTransfer.sendData(sendSize);

  //   // Update matching cell
  //   for (int i = 0; i < NUM_CELLS; i++) {
  //     if (ch == keyMap[i]) {
  //       cells[i]->in_zone = true;
  //       keyLastSeen[i] = shockCounter;
  //     }
  //   }

  //   ch = '\0';
  // }

  // // Handle Key Timeouts
  // for (int i = 0; i < NUM_CELLS; i++) {
  //   if (cells[i]->in_zone &&
  //       (shockCounter - keyLastSeen[i] > KEY_TIMEOUT)) {
  //     cells[i]->in_zone = false;
  //   }
  // } 



  // Run the shock controller
  for (int i = 0; i < NUM_CELLS; i++) {
    controlShock(cells[i]);
  }


}