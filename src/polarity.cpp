#include "polarity.h"

// Global Variables
volatile unsigned long polarity_counter = 0;  // in ms, max

// Timer Config
IntervalTimer polarity_timer;

/* void polarity_setup()
 * Sets up the GPIO pins used for the H-bridge as outputs
 * and sets up the timer for calling the swap_polarity function
 * @param: NA
 * @return: NA
 */
void polarity_setup() {
    // Initializing Pins
    Serial.println("Initializing Shock Setup...");
    pinMode(POL_PIN_1, OUTPUT);
    pinMode(POL_PIN_2, OUTPUT);

    digitalWrite(POL_PIN_1, LOW);
    digitalWrite(POL_PIN_2, HIGH);
    Serial.println("Pins Initialized...");

    // Initializing Timer
    polarity_timer.begin(swap_polarity, POLARITY_TIMER_INTERVAL);
    Serial.println("Timer Initialized...");
    Serial.println("Polarity Setup Complete");
}

/* void swap_polarity()
 * @brief Swaps polarity of shock signal
 * @param: NA
 * @return: NA
 *
 * This function sends signals to the H-bridge to swap the polarity
 */
void swap_polarity() {
    digitalWrite(POL_PIN_1, !digitalRead(POL_PIN_1));
    digitalWrite(POL_PIN_2, !digitalRead(POL_PIN_2));
}
