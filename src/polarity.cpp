#include "polarity.h"

// Global Variables
volatile unsigned long polarityCounter = 0;  // in ms, max

// Timer Config
IntervalTimer polarityTimer;

/* void polaritySetup()
* Sets up the GPIO pins used for the h bridge as outputs
* and sets up the timer for calling the swapPolarity Function
* @param: NA
* @return: NA
*/
void polaritySetup(){
    // Initializing Pins
    Serial.println("Initializing Shock Setup...");
    pinMode(POL_PIN_1, OUTPUT);
    pinMode(POL_PIN_2, OUTPUT);

    digitalWrite(POL_PIN_1, LOW);
    digitalWrite(POL_PIN_1, HIGH);
    Serial.println("Pins Initialized...");

    // Initializing Timer
    polarityTimer.begin(swapPolarity, polarityTimerInterval);
    Serial.println("Timer Initialized...");
    Serial.println("Polarity Setup Complete");
}

/* void swapPolarity()
* @brief Swaps polarity of shock signal
* @param: NA
* @return: NA
*
* This function swaps the sends signals to the H-Bridge enable to swap the polarity
*/
void swapPolarity(){
    digitalWrite(POL_PIN_1, !digitalRead(POL_PIN_1));
    digitalWrite(POL_PIN_2, !digitalRead(POL_PIN_2));
}