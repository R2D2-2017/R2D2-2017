//===========================================================//
//             Copyright Mike Hilhorst 2016.                 //
// Distributed under the Boost Software License, Version 1.0.//
//    (See accompanying file LICENSE_1_0.txt or copy at      //
//          http://www.boost.org/LICENSE_1_0.txt)            //
//===========================================================//
#pragma once

#include <array>
#include "wrap-hwlib.hh"


class command
{
private:
    hwlib::spi_bus & spiBus;
    hwlib::pin_out & chipSelect;
    int numberOfMatrices;
    int numberOfRows;
    int stringLength;
    uint8_t processedCommands[1000];
    uint8_t converterOutput[8][2];
    uint8_t commands[1000][8][2];


public:
    command(hwlib::spi_bus & spiBus, hwlib::pin_out & chipSelect, int & numberOfMatrices , int & numberOfRows, int & stringLength):
    spiBus(spiBus), chipSelect(chipSelect), numberOfMatrices(numberOfMatrices), numberOfRows(numberOfRows), stringLength(stringLength)
    {};

    void commander(uint8_t (*commands)[8][2]);

    void settings(const uint8_t (*settingsList)[2]);

    void converter(uint8_t (*renderInput)[8], uint8_t (*converterOutput)[2]);

    void render(uint8_t (*renderInput)[8]);

};





