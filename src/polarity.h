#include <Arduino.h>

// Global Constants
#define POL_PIN_1 A1          // Pinout for controlling gate 1 of the H-Bridge
#define POL_PIN_2 A2          // Pinout for controlling gate 2 of the H-Bridge
#define polarityTimerInterval 750000 // Swap the polarity every 75ms

// Global Variables
extern volatile unsigned long polarityCounter;  // in ms, max

// Timer Objects
extern IntervalTimer polarityTimer;

// Functions
void polaritySetup();
void swapPolarity();