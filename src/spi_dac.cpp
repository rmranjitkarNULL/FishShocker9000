#include "spi_dac.h"


void DACSetup(){
    SPI.begin();
    pinMode(DAC_CS, OUTPUT);
    digitalWrite(DAC_CS, HIGH);
}

void writeDAC(float voltage){

    // ! Draw this out to confirm equation
    // Write the desired voltage to the dac
    voltage = max(0.0f, min(voltage, MAX_VOLTAGE));     // Clamp voltage to be between 0-21
    float DACVoltage = voltage / AMP_GAIN;
    uint8_t DACVal = (DACVoltage * MAX_VAL) / VREF;    

    // Convert Value to DAC Bytes
    uint16_t bitFrame = valToBytes(DACVal);

    digitalWrite(DAC_CS, LOW);  // Write CS LOW to initialize data writing
    SPI.transfer16(bitFrame);   // Send bitFrame of value
    digitalWrite(DAC_CS, HIGH); // Write CS High to latch the data
}

uint16_t valToBytes(int DACVal){
    uint8_t commandByte = 0x00 | (DACVal >> 2);                     // Upper byte (PD Bits + D7 - D2)
    uint8_t dataByte = (DACVal & 0x03) << 6;                        // Lower Byte (D1 - D0 + 0 Pads)
    uint16_t bitFrame = (uint16_t(commandByte) << 8) | dataByte;    // Combine bytes to one bitFrame
    
    return bitFrame;
}