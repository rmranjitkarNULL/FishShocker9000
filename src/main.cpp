#include <Arduino.h>
#include "shock.h"
#include "polarity.h"
#include "sample.h"
#include "SerialTransfer.h"

// Serial Transfer from python script
SerialTransfer myTransfer;

// Buffer Variables
#define BUF_SIZ 8
CircularBuffer cell_ids; // Circular buffer for sending a shock when the fish is detected in the correct area
uint8_t buffer[BUF_SIZ] = {0};

// Array of pins
const uint8_t CELL_PINS[] = {LED_BUILTIN, A1, A2, A3, A4};
const uint8_t NUM_PINS = sizeof(CELL_PINS) / sizeof(CELL_PINS[0]);

// Global Variables
uint8_t target_cell = 0;

void setup() {

  // Initialize Serial
  Serial.begin(115200);
  while (!Serial);
  Serial.println("Initializing Setup");

  // Initialize shock setup (Pins, Timers, etc.)
  shock_setup();

  // Initialize polarity setup (Pins, Timers, etc.)
  polarity_setup();

  // Initialize buffer
  cb_init(&cell_ids, buffer, BUF_SIZ);

  // Initialize Serial
  myTransfer.begin(Serial);

  pinMode(LED_BUILTIN, OUTPUT);

  Serial.println("FishShocker9000: Setup Complete\n");
} 

void loop() {

  if(myTransfer.available())
  {
    // Declare Variable to store 
    uint16_t data;
    uint16_t cell_id;

    // send all received data back to Python
    for(uint16_t i=0; i < myTransfer.bytesRead; i++)
      myTransfer.packet.txBuff[i] = myTransfer.packet.rxBuff[i];
    
    myTransfer.sendData(myTransfer.bytesRead);

    // Save recievbed data to circular buffer
    myTransfer.rxObj(data);
    cell_id = data;

    // Push data to circular buffer
    cb_push(&cell_ids, cell_id);
  }

  // If there are cells in the buffer, pop it
  if(cb_pop(&cell_ids, &target_cell)){
    // Send the shock to the corresponding cell
    digitalWrite(target_cell, !digitalRead(target_cell));
  }

}

