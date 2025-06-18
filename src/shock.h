#pragma once

// Libraries
#include <Arduino.h>

// Global Constants
#define DELTA_SHOCK 10                                  // Time of shock in ms
#define DELTA_REST 740                                  // Time of rest in ms
#define SHOCK_CYCLE (DELTA_SHOCK + DELTA_REST)          // Shock Cycle Period
#define shockTimerInterval 1000                         // Timer configuration for shock timer, triggers every 1ms
#define CELL1 A0                                         // Pinout for sending signal

// Timer Object
extern IntervalTimer shockTimer;

// Global Variables
extern volatile unsigned long shockCounter;

// Function Prototypes
void countShock();
void shockSetup();
int inArea();
void sendShock(int cellPin);