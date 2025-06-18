#include <Arduino.h>
#include "shock.h"
#include "polarity.h"

void setup() {
  Serial.begin(115200);
  
  while(!Serial);

  // Initialize pins
  Serial.println("Initializing Setup");
  shockSetup();
  polaritySetup();
  Serial.println("FishShocker9000: Setup Complete\n");
}

void loop() {
  sendShock(CELL1);
}

