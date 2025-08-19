#include "shock.h"

// Global Variables
volatile unsigned long shockCounter = 0;

// Timer config
IntervalTimer shockTimer;

/* void countShock()
* @brief Swaps polarity of shock signal
* @param: NA
* @return: NA
*
* Timer function that counts up to the SHOCK_CYCLE and resets
*/
void countShock(){

    // Counter for shocking
    shockCounter++;
}

/* void countShock()
* @brief Swaps polarity of shock signal
* @param: NA
* @return: NA
*
* This setup function sets up the pins and timers for this source file
*/
void shockSetup(){
    // Initializing Pins
    Serial.println("Initializing Shock Setup...");
    Serial.println("Pins Initialized...");

    // Initializing Timer
    shockTimer.begin(countShock, SHOCK_TIMER_INTERVAL);
    Serial.println("Timer Initialized...");
    Serial.println("Shock Setup Complete");
}


// Comment
void controlShock(Cell *cell){
    uint32_t curr_time = shockCounter;

    if(cell->in_zone){
        if(checkStart(cell)){
            cell->last_toggle_time = curr_time;
            cell->shock_on = true;
            sendSignal(cell, HIGH);
        }else if(checkShock(cell, curr_time)){
            cell->last_toggle_time = curr_time;
            cell->shock_on = false;
            sendSignal(cell, LOW);
        }else if(checkRest(cell, curr_time)){
            cell->last_toggle_time = curr_time;
            cell->shock_on = true;
            sendSignal(cell, HIGH);
        }  
    } else{
        cell-> last_toggle_time = 0;
        cell->shock_on = false;
        return;
    }
}

bool checkStart(Cell *cell){
    return ((cell->last_toggle_time == 0) && (!cell->shock_on));
}

bool checkShock(Cell *cell, uint32_t curr_time){
    return ((curr_time - cell->last_toggle_time >= DELTA_SHOCK) && (cell->shock_on));
}

bool checkRest(Cell *cell, uint32_t curr_time){
    return ((curr_time - cell->last_toggle_time >= DELTA_REST) && (!cell->shock_on));
}
