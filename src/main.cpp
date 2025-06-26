#include <Arduino.h>
#include "shock.h"
#include "polarity.h"
#include "sample.h"

// Buffer Variables
#define BUF_SIZE 8
CircularBuffer cell_cycle; // Circular buffer for sending a shock when the fish is detected in the correct area
uint8_t buffer[BUF_SIZE] = {0};

void setup() {
  Serial.begin(115200);
  
  while (!Serial);
  Serial.println("Initializing Setup");

  // Initialize shock setup
  shock_setup();

  // Initialize polarity setup
  polarity_setup();

  // Initialize buffer
  cb_init(&cell_cycle, buffer, BUF_SIZE);

  Serial.println("FishShocker9000: Setup Complete\n");
}

void loop() {
  // Setup variables
  uint8_t target_cell = 0;

  /*
    TODO: Modify for CAN protocol in the future
    * Make sure it's in an ISR (that's where the data is pushed)
  */
  cb_push(&cell_cycle, in_area());

  // Pop the circular buffer and then send the shock to that pin
  cb_pop(&cell_cycle, target_cell);
}
