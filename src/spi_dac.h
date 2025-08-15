#include <Arduino.h>
#include <SPI.h>

#define MAX_VAL 255.0
#define VREF 5.0
#define AMP_GAIN 4.19
#define MAX_VOLTAGE 21.0

// DAC CS Pin
constexpr int DAC_CS = 11;

/* void DACSetup()
 * @brief setup function to insitialize SPI
 * 
 * This function sets up the DAC with its configured CS pin, default IDLE state,
 * and begins the SPI protocol
 * 
 * @param: NA
 * @return: NA
 */
void DACSetup();

/* void writeDAC(float voltage)
 * @brief Writes a value to the DAC to output the desired voltage
 * 
 * This function takes in a desired voltage, then sets the DAC to output that
 * voltage. It utilizes the voltage gain, Vref, and DAC bit size to calculate the DAC input.
 * CS pin for the DAC is then pulled low, letting us write the wanted voltage value to the DAC.
 * We then pull the CS pin High to end the transaction.
 * 
 * @param: float voltage - Desired voltage
 * @return: NA
 */
void writeDAC(float voltage);

/* void writeDAC(float voltage)
 * @brief converts a value to the DAC Serial transfer protocl
 * 
 * This function takes in a DACValue and converts it to bytes corresponding to the 
 * transfer protocl as provided by the datasheet (See page 25).
 * 
 * Datasheet: https://www.ti.com/product/DAC5311#tech-docs
 *  
 * @param: int DACVal - value ot be converted to bits, between 0 and DAC bit size
 * @return: uint16_t bitFrame - the frame that includes desired bytes for the DAC protocol
 */
uint16_t valToBytes(int DACVal);