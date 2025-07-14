#pragma once

// Libraries
#include <Arduino.h>

// Global Constants
#define DELTA_SHOCK 10                                   // Time of shock in ms
#define DELTA_REST 740                                   // Time of rest in ms
#define SHOCK_CYCLE (DELTA_SHOCK + DELTA_REST)           // Shock cycle period
#define SHOCK_TIMER_INTERVAL 1000                        // Timer configuration for shock timer, triggers every 1ms
#define CELL1 A0                                         // Pinout for sending signal
#define CELL2 A1                                         // Pinout for sending signal
#define CELL3 A2                                         // Pinout for sending signal
#define CELL4 A3                                         // Pinout for sending signal
#define CELL5 A4                                         // Pinout for sending signal

// Timer Object
extern IntervalTimer shock_timer;

// Global Variables
extern volatile uint32_t shock_counter;

// Cell Struct
struct Cell{
    int cell_id;                                         //
    volatile bool in_zone = false;
    bool shock_on = false;
    uint32_t last_toggle_time = 0;
};

// Function Prototypes

/* void count_shock()
 * @brief Timer callback function that increments the shock counter
 * 
 * This function is triggered every millisecond. It increments the `shock_counter` until it reaches
 * the defined SHOCK_CYCLE period (shock duration + rest duration), then resets it back to zero.
 * Used to schedule shock output within a cycle.
 * 
 * @param: NA
 * @return: NA
 */
void count_shock();

/* void shock_setup()
 * @brief Initializes GPIO pins and timer for the shock mechanism
 * 
 * Sets the shock output pin to OUTPUT mode and initializes the timer that controls
 * the shock pulse cycle.
 * 
 * @param: NA
 * @return: NA
 */
void shock_setup();

/* void send_signal(Cell *cell, int level)
 * @brief Sends a HIGH or LOW to the corresponding pin
 * 
 * Sends the corresponding level to the corresponding GPIO pin, either HIGH (3.3v)
 * or LOW (0v). Utilizes the cell structure to find the corresponding GPIO pin to
 * send out the signal
 * 
 * @param: Cell *cell - Cell to send the signal to
 * @param: int level - HIGH or LOW (3.3v or 0v)
 * @return: NA
 */
void send_signal(Cell *cell, int level);

/* void control_shock(Cell *cell)
 * @brief Controls the shock being sent out
 * 
 * Sends a signal (shock) to the corresponding cell at the rate desired in
 * the delta parameters. Turns off the shock if the fish is no longer in the area
 * 
 * @param: Cell *cell - Cell to send the signal to
 * @return: NA
 */
void control_shock(Cell *cell);

/* void check_start(Cell *cell)
 * @brief Checks if the cell is just starting a shock
 * 
 * If the fish enters the area, this will start the shock on the correspondign cell
 * without waiting the rest period.
 * 
 * @param: Cell *cell - Cell to send the signal to
 * @return: Bool
 */
bool check_start(Cell *cell);

/* void check_shock(Cell *cell, uint32_t curr_time)
 * @brief Checks if the fish has been shocked for the delta shock time
 * 
 * Checks if the fish has been shocked for the delta shock time.
 * 
 * @param: Cell *cell -> Cell to send the signal to
 * @param: uint32_t time -> The "Current" time at this function call
 * @return: Bool
 */
bool check_shock(Cell *cell, uint32_t curr_time);

/* void check_rest(Cell *cell, uint32_t curr_time)
 * @brief Checks if the fish has not been shocked for the delta rest time
 * 
 * Checks if the fish has not been shocked for the delta rest time
 * 
 * @param: Cell *cell -> Cell to send the signal to
 * @param: uint32_t time -> The "Current" time at this function call
 * @return: NA
 */
bool check_rest(Cell *cell, uint32_t curr_time);