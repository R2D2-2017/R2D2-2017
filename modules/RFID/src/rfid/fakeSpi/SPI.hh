//
// Created by Robert on 6/14/17.
//

#pragma  once
#include <cstdint>
#include <wiringShift.h>
#include <libio.h>
typedef uint8_t byte;

class SPISettings {
public:
    SPISettings() :_clock(1000000), _bitOrder(LSBFIRST){}
    SPISettings(uint32_t clock, uint8_t bitOrder, uint8_t dataMode) :_clock(clock), _bitOrder(bitOrder){}
    uint32_t _clock;
    uint8_t  _bitOrder;
};

class SPIClass {
public:
    void beginTransaction(SPISettings settings);
    uint8_t transfer(uint8_t data);
    void endTransaction(void);
private:
    int SPIDescriptor;
};

extern SPIClass SPI;