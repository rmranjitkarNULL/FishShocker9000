#ifndef POLARITY_H
#define POLARITY_H

#include <Arduino.h>

// Global Constants
#define POL_PIN_1 A17                 // Pinout for controlling gate 1 of the H-Bridge
#define POL_PIN_2 A16                 // Pinout for controlling gate 2 of the H-Bridge
#define POLARITY_TIMER_INTERVAL 750000 // Swap the polarity every 75ms (in microseconds)

// Global Variables
extern volatile unsigned long polarity_counter;  // in ms, max

// Timer Objects
extern IntervalTimer polarity_timer;

// Functions

/* void polarity_setup()
 * Sets up the GPIO pins used for the H-bridge as outputs
 * and sets up the timer for calling the swap_polarity function
 * @param: NA
 * @return: NA
 */
void polarity_setup();

/* void swap_polarity()
 * @brief Swaps polarity of shock signal
 * @param: NA
 * @return: NA
 *
 * This function sends signals to the H-bridge to swap the polarity
 */
void swap_polarity();

#endif // POLARITY_H
