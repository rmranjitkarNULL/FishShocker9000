#include "shock.h"

// Global Variables
volatile unsigned long shockCounter = 0;

// Timer config
IntervalTimer shockTimer;

#ifdef SHOCK_PULSE
    int state = 0;
#endif

/* 
    void countShock()

    This function is used as a counter for sending out the shocking signals towards the corresponding y cell
    The max count is the duration of the shock (ms) plus the duration of rest (ms), which resets the counter
    to zero after.
*/
void countShock(){

    // Debug flag to check if the timer counts up to desired time period
    #ifdef SHOCK_TIMER
        Serial.printf("%dms... \n", shockCounter);
        if(shockCounter > DELTA_SHOCK + DELTA_REST - 1){
            return;
        }
    #endif

    if(shockCounter > SHOCK_CYCLE - 1) shockCounter = 0;
    shockCounter++;
}

void shockSetup(){
    // Initializing Pins
    Serial.println("Initializing Shock Setup...");
    pinMode(CELL1, OUTPUT);
    digitalWrite(CELL1, LOW);
    Serial.println("Pins Initialized...");

    // Initializing Timer
    shockTimer.begin(countShock, shockTimerInterval);
    Serial.println("Timer Initialized...");
    Serial.println("Shock Setup Complete");
}

/*
    void inArea()
    ! Place Holder for now to always return the first cell'
    ? use a dictionary/set for the final lookup from the pins to the actual cell
    ? Use a fifo for getting the cellPins for proper time efficiency

    This function detects whether the corresponding fish is in the designated shock zone
    and returns the zebra fish's corresponding y-cell as a number to lookup the correct pin
*/
int inArea(){
    return CELL1;
}

/*
    void sendShock(int cellPin)
        int cellPin: The pin that corresponds to the cell that is being shocked
    
    This function sends out the signal to the corresponding cell based on the pin
    ! Maybe have multiple counters that only go up after the time is done? and have
    ! Multiple counters per section that only counts if its being triggered?

*/
void sendShock(int cellPin){
    #ifdef SHOCK_PULSE
        Serial.print(">State:");
        Serial.println(state);

        Serial.print(">Time (ms):");
        Serial.println(shockCounter);
    #endif

    // Send a shock if the counter is less then deltaShock
    if(shockCounter < DELTA_SHOCK - 1) {
        digitalWrite(cellPin, HIGH);

        #ifdef SHOCK_PULSECan you 
            Serial.printf("Sending shock to pin %d: %dms\n", cellPin, shockCounter);
            state = 1;
        #endif
    } else {
        digitalWrite(cellPin, LOW);

        #ifdef SHOCK_PULSE
            //Serial.printf("Ending shock on pin %d: %dms\n", cellPin, shockCounter);
            state = 0;
        #endif
    }
}