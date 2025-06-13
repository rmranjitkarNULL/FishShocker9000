#include <Arduino.h>
#include "shock.h"
#include "polarity.h"

void setup() {
  Serial.begin(115200);
  
  while(!Serial);

  // Initialize pins
  Serial.println("Initializing Pins...");
  shockSetup();
  polaritySetup();
  Serial.println("Pins Initialized...");

  // Initialize timers
  Serial.println("Initializing Timers...");
  shockTimer.begin(countShock, shockTimerInterval);
  polarityTimer.begin(swapPolarity, polarityTimerInterval);
  Serial.println("Initialized Timers...");

  Serial.println("FishShocker9000: Setup Complete\n");
}

void loop() {
  
}

