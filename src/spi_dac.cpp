#include "spi_dac.h"
#define VREF 5.0
#define AMP_GAIN 4.19
#define MAX_VOLTAGE 12.0    

// SPI settings: 1 MHz, MSB first, SPI Mode 0
SPISettings settingsA(1000000, MSBFIRST, SPI_MODE1);

void setupDAC(){
    /*
    Pins to check:
    Pin 26: Sync
    Pin 13: SCK
    Pinn 11: MOSI
    */

    Serial.println("SPI Initializing...");
    pinMode(DAC_CS, OUTPUT);
    digitalWrite(DAC_CS, HIGH);                             // idle high for CS
    SPI.begin();
    Serial.println("SPI Initialized...\n");
}

//8-bit dac
void writeDAC(float voltage) {

    // Clamp and scale voltage
    float voltageClamped = constrain(voltage, 0.0, MAX_VOLTAGE);
    uint8_t DACVal = (voltageClamped * 255.0) / (VREF * AMP_GAIN);
    uint16_t frame = valToFrame(DACVal + 6); // Figure out why the math isn't right and why we need the offset

    // Transmit frame MSB-first
    SPI.beginTransaction(settingsA);
    digitalWrite(DAC_CS, LOW);
    SPI.transfer16(frame);
    digitalWrite(DAC_CS, HIGH);
    SPI.endTransaction();
}

uint16_t valToFrame(uint8_t DACVal) {
    return ((DACVal << 6) & 0x3FC0);  
}