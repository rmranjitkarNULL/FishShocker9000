#ifndef POLARITY_H
#define POLARITY_H

#include <Arduino.h>

// Global Constants
#define POL_PIN_1 A1                 // Pinout for controlling gate 1 of the H-Bridge
#define POL_PIN_2 A2                 // Pinout for controlling gate 2 of the H-Bridge
#define POLARITY_TIMER_INTERVAL 750000 // Swap the polarity every 75ms (in microseconds)

// Global Variables
extern volatile unsigned long polarity_counter;  // in ms, max

// Timer Objects
extern IntervalTimer polarity_timer;

// Functions
void polarity_setup();
void swap_polarity();

#endif // POLARITY_H
