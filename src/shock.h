#pragma once

// Libraries
#include <Arduino.h>

// Global Constants
#define DELTA_SHOCK 10                                   // Time of shock in ms
#define DELTA_REST 740                                   // Time of rest in ms
#define SHOCK_CYCLE (DELTA_SHOCK + DELTA_REST)           // Shock cycle period
#define SHOCK_TIMER_INTERVAL 1000                        // Timer configuration for shock timer, triggers every 1ms
#define CELL1 A0                                          // Pinout for sending signal

// Timer Object
extern IntervalTimer shock_timer;

// Global Variables
extern volatile unsigned long shock_counter;

// Function Prototypes
void count_shock();
void shock_setup();
int in_area();
void send_shock(int cell_pin);
