//
// Created by Robert on 6/14/17.
//

#include "SPI.hh"
#include <wiringPiSPI.h>
#include <stdexcept>

const int channel = 0;

byte SPIClass::transfer(byte _data) {
    if (SPIDescriptor != -1) {
        fwrite(&_data, 1, 1, (FILE *) SPIDescriptor);
    } else {
        throw std::runtime_error("SPI Not opened");
    }
}
void SPIClass::beginTransaction(SPISettings settings) {
    SPIDescriptor = wiringPiSPISetup(0, settings._clock);
}
void SPIClass::endTransaction(void) {
    SPIDescriptor = -1;

}
