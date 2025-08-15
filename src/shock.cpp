#include "shock.h"

// Global Variables
volatile uint32_t shock_counter = 0;  // Counter for shock timing (in ms)

// Timer Configuration
IntervalTimer shock_timer;

void count_shock() {
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


void send_signal(Cell *cell, int level) {
    if(cell->in_zone){
        uint8_t pin = cell->cell_id;
        cell->shock_on = true;
        digitalWrite(pin, level);
    }
}


// Comment
void control_shock(Cell *cell){
    uint32_t curr_time = shock_counter;

    if(cell->in_zone){
        if(check_start(cell)){
            cell->last_toggle_time = curr_time;
            cell->shock_on = true;
            send_signal(cell, HIGH);
        }else if(check_shock(cell, curr_time)){
            cell->last_toggle_time = curr_time;
            cell->shock_on = false;
            send_signal(cell, LOW);
        }else if(check_rest){
            cell->last_toggle_time = curr_time;
            cell->shock_on = true;
            send_signal(cell, HIGH);
        }  
    } else{
        cell-> last_toggle_time = 0;
        cell->shock_on = false;
        return;
    }
}

bool check_start(Cell *cell){
    return ((cell->last_toggle_time == 0) && (!cell->shock_on));
}

bool check_shock(Cell *cell, uint32_t curr_time){
    return ((curr_time - cell->last_toggle_time >= DELTA_SHOCK) && (cell->shock_on));
}

bool check_rest(Cell *cell, uint32_t curr_time){
    return ((curr_time - cell->last_toggle_time >= DELTA_REST) && (!cell->shock_on));
}
