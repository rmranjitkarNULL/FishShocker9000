#include "shock.h"

// Global Variables
volatile uint32_t shockCounter = 0;

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

    shockCounter++;
}

void shock_setup(){
    // Initializing Pins
    Serial.println("Initializing Shock Setup...");
    
    // * Make LEDS do a cool bootup animation...?
    for(int i = 0; i < NUM_CELLS; i++){
        pinMode(cells[i]->cell_id, OUTPUT);
        digitalWrite(cells[i]->cell_id, HIGH);
    }

    Serial.println("Pins Initialized...");

    // Initializing Timer
    shockTimer.begin(countShock, SHOCK_TIMER_INTERVAL);

    // LED Timer setup
    uint16_t lastTime = shockCounter;
    uint8_t cell_marker = 0;
    bool isBooting = true;
    while(isBooting){
        // Get last 16 bits of shockCounter for same type int conversion
        if((shockCounter & 0xFFFF) - lastTime > 250){
            digitalWrite(cells[cell_marker]->cell_id, LOW);
            lastTime = shockCounter;
            cell_marker++;

            if(cell_marker == 12) isBooting = false;
        }
    }


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