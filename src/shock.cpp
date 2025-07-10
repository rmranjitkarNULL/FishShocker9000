#include "shock.h"

// Global Variables
volatile unsigned long shock_counter = 0;  // Counter for shock timing (in ms)

// Timer Configuration
IntervalTimer shock_timer;

#ifdef SHOCK_PULSE
int state = 0;  // State flag for debugging
#endif

void count_shock() {
    #ifdef SHOCK_TIMER
        Serial.printf("%dms... \n", shock_counter);
        if (shock_counter > DELTA_SHOCK + DELTA_REST - 1) {
            return;
        }
    #endif

    if (shock_counter > SHOCK_CYCLE - 1) shock_counter = 0;
    shock_counter++;
}   

void shock_setup() {
    Serial.println("Initializing Shock Setup...");

    // Set cell pin as output and default LOW
    pinMode(CELL1, OUTPUT);
    digitalWrite(CELL1, LOW);
    Serial.println("Pins Initialized...");

    // Start timer with defined interval
    shock_timer.begin(count_shock, SHOCK_TIMER_INTERVAL);
    Serial.println("Timer Initialized...");
    Serial.println("Shock Setup Complete");
}

int in_area() {
    return CELL1;
}

#ifdef SHOCK_PULSE
void send_shock(int cell_pin) {
    #ifdef SHOCK_PULSE
        Serial.print(">State:");
        Serial.println(state);

        Serial.print(">Time (ms):");
        Serial.println(shock_counter);
    #endif

    if (shock_counter < DELTA_SHOCK - 1) {
        digitalWrite(cell_pin, HIGH);

        #ifdef SHOCK_PULSE
            Serial.printf("Sending shock to pin %d: %dms\n", cell_pin, shock_counter);
            state = 1;
        #endif
    } else {
        digitalWrite(cell_pin, LOW);

        #ifdef SHOCK_PULSE
            state = 0;
        #endif
    }
}
#endif

#ifndef SHOCK_PULSE
void send_shock(int cell_pin) {
    if (shock_counter < DELTA_SHOCK - 1) {
        digitalWrite(cell_pin, HIGH);


    } else {
        digitalWrite(cell_pin, LOW);
    }
}
#endif
