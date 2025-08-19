#include "spi_dac.h"
#define MAX_VAL 255.0
#define VREF 5.0
#define AMP_GAIN 4.19
#define MAX_VOLTAGE 12.0    

SPISettings settingsA(1000000, MSBFIRST, SPI_MODE0);

void DACSetup(){
    pinMode(DAC_CS, OUTPUT);
    SPI.begin();
}

void writeDAC(float voltage){

    // ! Draw this out to confirm equation
    // Write the desired voltage to the dac
    // voltage = max(0.0f, min(voltage, MAX_VOLTAGE));     // Clamp voltage to be between 0-MAX_VOLTAGE
    // float DACVoltage = voltage / AMP_GAIN;
    // uint8_t DACVal = (DACVoltage * MAX_VAL) / VREF;    

    // Convert Value to DAC Bytes
    uint16_t bitMask = valToBits(255);

    digitalWrite(DAC_CS, LOW);                                                                // Write CS LOW to initialize data writing
    SPI.transfer16(bitMask);   // Send bitFrame of value
    digitalWrite(DAC_CS, HIGH); // Write CS High to latch the data
}   



uint16_t valToBits(int DACVal){
    uint8_t firstByte = 0x00 | (DACVal >> 2); // Upper byte (PD Bits + D7 - D2)
    uint8_t secondByte = (DACVal << 6);
    uint16_t mask = (uint16_t(firstByte) << 8) | secondByte;

    //? Could probably make this just << 5...
    // uint16_t mask = (uint16_t(DACVal) << 5);
    
    return mask;
}