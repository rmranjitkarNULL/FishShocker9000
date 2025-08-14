#include "shock.h"

// Global Variables
volatile unsigned long shockCounter = 0;

// Timer config
IntervalTimer shockTimer;

void countShock(){

    //? Debug flag to check if the timer counts up to desired time period
    #ifdef SHOCK_TIMER
        Serial.printf("%dms... \n", shockCounter);
        if(shockCounter > DELTA_SHOCK + DELTA_REST - 1){
            return;
        }
    #endif

    // Counter for shocking
    if(shockCounter > SHOCK_CYCLE - 1) shockCounter = 0;
    shockCounter++;
}

void shock_setup(){
    // Initializing Pins
    Serial.println("Initializing Shock Setup...");
    
    for(int i = 0; i < NUM_CELLS; i++){
        pinMode(cells[i]->cell_id, OUTPUT);
        digitalWrite(cells[i]->cell_id, HIGH);
    }

    Serial.println("Pins Initialized...");

    // Initializing Timer
    shockTimer.begin(countShock, SHOCK_TIMER_INTERVAL);
    Serial.println("Timer Initialized...");
    Serial.println("Shock Setup Complete");
}

int inArea(){
    return CELL1;
}

/* void sendShock(int cellPin)
* @brief Swaps polarity of shock signal
* @param:
*   int cellPin: The pin number of the gpio output for the corresponding cell
* @return: NA
! Maybe have multiple counters that only go up after the time is done? and have
! Multiple counters per section that only counts if its being triggered?
* This function sends out a shock signal based on the timer and pin parameter
*/
void sendShock(int cellPin){

    // Send a shock if the counter is less then deltaShock
    if(shockCounter < DELTA_SHOCK - 1) {
        digitalWrite(cellPin, HIGH);

        #ifdef SHOCK_PULSE
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