#pragma once

// Libraries
#include <Arduino.h>

// Global Constants
#define DELTA_SHOCK 10                                   // Time of shock in ms
#define DELTA_REST 740                                   // Time of rest in ms
#define SHOCK_CYCLE (DELTA_SHOCK + DELTA_REST)           // Shock cycle period
#define SHOCK_TIMER_INTERVAL 1000                        // Timer configuration for shock timer, triggers every 1ms
#define CELL1 A0                                          // Pinout for sending signal

// Timer Object
extern IntervalTimer shock_timer;

// Global Variables
extern volatile unsigned long shock_counter;

// Function Prototypes

/* void count_shock()
 * @brief Timer callback function that increments the shock counter
 * 
 * This function is triggered every millisecond. It increments the `shock_counter` until it reaches
 * the defined SHOCK_CYCLE period (shock duration + rest duration), then resets it back to zero.
 * Used to schedule shock output within a cycle.
 * 
 * @param: NA
 * @return: NA
 */
void count_shock();

/* void shock_setup()
 * @brief Initializes GPIO pins and timer for the shock mechanism
 * 
 * Sets the shock output pin to OUTPUT mode and initializes the timer that controls
 * the shock pulse cycle.
 * 
 * @param: NA
 * @return: NA
 */
void shock_setup();

/* int in_area()
 * @brief Placeholder function to check if target is within the shock area
 * 
 * Returns the pin number of the active shock region (currently hardcoded).
 * 
 * @param: NA
 * @return: int - pin number of the active shock region
 */
int in_area();

/* void send_shock(int cell_pin)
 * @brief Sends a HIGH pulse to a specific pin if within shock duration
 * 
 * Based on the current value of `shock_counter`, sends a HIGH or LOW signal to
 * the specified pin. The pin is set HIGH during the first DELTA_SHOCK ms of the cycle.
 * 
 * @param: int cell_pin - pin number to which the shock signal is sent
 * @return: NA
 */
void send_shock(int cell_pin);
