#include "polarity.h"

// Global Variables
volatile unsigned long polarityCounter = 0;  // in ms, max

// Timer Config
IntervalTimer polarityTimer;

void polaritySetup(){
    pinMode(POL_PIN_1, OUTPUT);
    pinMode(POL_PIN_2, OUTPUT);

    digitalWrite(POL_PIN_1, LOW);
    digitalWrite(POL_PIN_1, HIGH);
}

void swapPolarity(){
    digitalWrite(POL_PIN_1, !digitalRead(POL_PIN_1));
    digitalWrite(POL_PIN_2, !digitalRead(POL_PIN_2));
}