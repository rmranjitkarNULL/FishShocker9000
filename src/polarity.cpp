#include "polarity.h"

// Timer Config
IntervalTimer polarity_timer;

void polarity_setup() {
    // Initializing Pins
    Serial.println("Initializing Polarity Setup...");
    pinMode(POL_PIN_1, OUTPUT);
    pinMode(POL_PIN_2, OUTPUT);

    digitalWrite(POL_PIN_1, LOW);
    digitalWrite(POL_PIN_2, HIGH);
    Serial.println("Pins Initialized...");

    // Initializing Timer
    polarity_timer.begin(swapPolarity, POLARITY_TIMER_INTERVAL);
    Serial.println("Timer Initialized...");
    Serial.println("\nPolarity Setup Complete\n");
}

void swapPolarity() {
    digitalWrite(POL_PIN_1, !digitalRead(POL_PIN_1));
    digitalWrite(POL_PIN_2, !digitalRead(POL_PIN_2));
}
