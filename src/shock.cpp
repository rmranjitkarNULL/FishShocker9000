#include "shock.h"

// Global Variables
volatile unsigned long shock_counter = 0;

// Timer config
IntervalTimer shock_timer;

#ifdef SHOCK_PULSE
    int state = 0;
#endif

/* 
    void count_shock()

    This function is used as a counter for sending out the shocking signals towards the corresponding y-cell.
    The max count is the duration of the shock (ms) plus the duration of rest (ms), which resets the counter to zero after.
*/
void count_shock() {

    // Debug flag to check if the timer counts up to desired time period
    #ifdef SHOCK_TIMER
        Serial.printf("%dms... \n", shock_counter);
        if (shock_counter > DELTA_SHOCK + DELTA_REST - 1) {
            return;
        }
    #endif

    if (shock_counter > SHOCK_CYCLE - 1) shock_counter = 0;
    shock_counter++;
}

/* 
    void shock_setup()

    Initializes pins and timer for shock signal.
*/
void shock_setup() {
    // Initializing Pins
    Serial.println("Initializing Shock Setup...");
    pinMode(CELL1, OUTPUT);
    digitalWrite(CELL1, LOW);
    Serial.println("Pins Initialized...");

    // Initializing Timer
    shock_timer.begin(count_shock, SHOCK_TIMER_INTERVAL);
    Serial.println("Timer Initialized...");
    Serial.println("Shock Setup Complete");
}

/*
    int in_area()

    Placeholder for detecting whether a fish is in the designated shock zone.
    Returns the y-cell as a number to look up the corresponding pin.
*/
int in_area() {
    return CELL1;
}

/*
    void send_shock(int cell_pin)

    Sends a shock signal to the specified pin if the counter is within the shock duration.
    - int cell_pin: The pin that corresponds to the cell that is being shocked
*/
void send_shock(int cell_pin) {
    #ifdef SHOCK_PULSE
        Serial.print(">State:");
        Serial.println(state);

        Serial.print(">Time (ms):");
        Serial.println(shock_counter);
    #endif

    // Send a shock if the counter is less than delta_shock
    if (shock_counter < DELTA_SHOCK - 1) {
        digitalWrite(cell_pin, HIGH);

        #ifdef SHOCK_PULSE
            Serial.printf("Sending shock to pin %d: %dms\n", cell_pin, shock_counter);
            state = 1;
        #endif
    } else {
        digitalWrite(cell_pin, LOW);

        #ifdef SHOCK_PULSE
            // Serial.printf("Ending shock on pin %d: %dms\n", cell_pin, shock_counter);
            state = 0;
        #endif
    }
}
