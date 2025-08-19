#include "spi_dac.h"
#define MAX_VAL 255.0
#define VREF 5.0
#define AMP_GAIN 4.19
#define MAX_VOLTAGE 12.0    

// SPI settings: 1 MHz, MSB first, SPI Mode 0
SPISettings settingsA(1000000, MSBFIRST, SPI_MODE0);

void setupDAC(){
    /*
    Pins to check:
    Pin 26: Sync
    Pin 13: SCK
    Pinn 11: MOSI
    */

    pinMode(DAC_CS, OUTPUT);
    digitalWrite(DAC_CS, HIGH);                             // idle high for CS
    Serial.println("SPI test starting...");
    SPI.begin();
}

void writeDAC(float voltage){

    // ! Draw this out to confirm equation
    Write the desired voltage to the dac
    voltage = max(0.0f, min(voltage, MAX_VOLTAGE));     // Clamp voltage to be between 0-MAX_VOLTAGE
    float DACVoltage = voltage / AMP_GAIN;
    uint8_t DACVal = (DACVoltage * MAX_VAL) / VREF;    


    digitalWrite(DAC_CS, LOW);              // Select the device
    SPI.beginTransaction(settingsA);
    SPI.transfer(DACVal);                     
    SPI.endTransaction();
    digitalWrite(DAC_CS, HIGH);             // Deselect
}   


uint16_t valToBits(int DACVal){
    uint8_t firstByte = 0x00 | (DACVal >> 2); // Upper byte (PD Bits + D7 - D2)
    uint8_t secondByte = (DACVal << 6);
    uint16_t mask = (uint16_t(firstByte) << 8) | secondByte;

    // ? Could probably make this just << 5...
    // uint16_t mask = (uint16_t(DACVal) << 5);
    
    return mask;
}