#include <Arduino.h>
#include <SPI.h>

#define MAX_VAL 255.0
#define VREF 5.0
#define AMP_GAIN 4.19
#define MAX_VOLTAGE 21.0

// DAC CS Pin
constexpr int DAC_CS = 11;

void DACSetup();

void voltageOff();

uint16_t valToBytes(int DACVal);