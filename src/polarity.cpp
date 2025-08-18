#include "polarity.h"

// Global Variables
volatile unsigned long polarity_counter = 0;  // in ms, max

// Timer Config
IntervalTimer polarity_timer;

void polarity_setup() {
    // Initializing Pins
    Serial.println("Initializing Shock Setup...");
    pinMode(POL_PIN_1, OUTPUT);
    pinMode(POL_PIN_2, OUTPUT);

    digitalWrite(POL_PIN_1, LOW);
    digitalWrite(POL_PIN_2, HIGH);
    Serial.println("Pins Initialized...");

    // Initializing Timer
    polarity_timer.begin(swapPolarity, POLARITY_TIMER_INTERVAL);
    Serial.println("Timer Initialized...");
    Serial.println("Polarity Setup Complete");
}

void swapPolarity() {
    digitalWrite(POL_PIN_1, !digitalRead(POL_PIN_1));
    digitalWrite(POL_PIN_2, !digitalRead(POL_PIN_2));
}
