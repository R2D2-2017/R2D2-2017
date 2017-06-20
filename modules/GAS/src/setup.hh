#pragma once

#include "wrap-hwlib.hh"
#include "command.hh"
#include "string.h" // for strlen();


class Setup
{
private:

    /**
     * Spi pins
     */
    hwlib::spi_bus & spiBus;
    hwlib::pin_out & chipSelect;

    /**
     * sttings
     */
    int numberOfUnusedMatrices;
    int numberOfMatrices;
    int numberOfRows = 8;

    /**
     * chars that can be displayed.
     */
    uint8_t charSpace[8][8] = {0};
    uint8_t charOne[8][8]   = {{0,0,0,0,0,0,0,0},{0,0,1,1,1,0,0,0},{0,1,1,1,1,0,0,0},{0,0,0,1,1,0,0,0},{0,0,0,1,1,0,0,0},{0,0,0,1,1,0,0,0},{0,1,1,1,1,1,1,0},{0,0,0,0,0,0,0,0}};
    uint8_t charTwo[8][8]   = {{0,0,0,0,0,0,0,0},{0,1,1,1,1,1,0,0},{0,0,0,0,0,1,1,0},{0,0,0,0,0,1,1,0},{0,0,0,0,1,1,0,0},{0,0,0,1,1,0,0,0},{0,1,1,1,1,1,1,0},{0,0,0,0,0,0,0,0}};
    uint8_t charThree[8][8] = {{0,0,0,0,0,0,0,0},{0,1,1,1,1,1,0,0},{0,0,0,0,0,1,1,0},{0,0,0,1,1,1,1,0},{0,0,0,1,1,1,1,0},{0,0,0,0,0,1,1,0},{0,1,1,1,1,1,0,0},{0,0,0,0,0,0,0,0}};
    uint8_t charFour[8][8]  = {{0,0,0,0,0,0,0,0},{0,0,0,0,0,1,0,0},{0,0,0,0,1,1,0,0},{0,0,0,1,0,1,0,0},{0,0,1,0,0,1,0,0},{0,1,1,1,1,1,1,0},{0,0,0,0,0,1,0,0},{0,0,0,0,0,0,0,0}};
    uint8_t charFive[8][8]  = {{0,0,0,0,0,0,0,0},{0,1,1,1,1,1,1,0},{0,1,0,0,0,0,0,0},{0,1,1,1,1,1,0,0},{0,0,0,0,0,0,1,0},{0,0,0,0,0,0,1,0},{0,1,1,1,1,1,0,0},{0,0,0,0,0,0,0,0}};
    uint8_t charSix[8][8]   = {{0,0,0,0,0,0,0,0},{0,0,1,1,1,1,1,0},{0,1,0,0,0,0,0,0},{0,1,1,1,1,1,0,0},{0,1,0,0,0,0,1,0},{0,1,0,0,0,0,1,0},{0,0,1,1,1,1,0,0},{0,0,0,0,0,0,0,0}};
    uint8_t charSeven[8][8] = {{0,0,0,0,0,0,0,0},{0,1,1,1,1,1,1,0},{0,0,0,0,0,1,1,0},{0,0,0,0,1,1,0,0},{0,0,0,1,1,0,0,0},{0,0,1,1,0,0,0,0},{0,1,1,0,0,0,0,0},{0,0,0,0,0,0,0,0}};
    uint8_t charEight[8][8] = {{0,0,0,0,0,0,0,0},{0,0,1,1,1,1,0,0},{0,1,0,0,0,0,1,0},{0,0,1,1,1,1,0,0},{0,1,0,0,0,0,1,0},{0,1,0,0,0,0,1,0},{0,0,1,1,1,1,0,0},{0,0,0,0,0,0,0,0}};
    uint8_t charNine[8][8]  = {{0,0,0,0,0,0,0,0},{0,0,1,1,1,1,0,0},{0,1,0,0,0,0,1,0},{0,0,1,1,1,1,1,0},{0,0,0,0,0,0,1,0},{0,0,0,0,0,0,1,0},{0,0,1,1,1,1,0,0},{0,0,0,0,0,0,0,0}};
    uint8_t charZero[8][8]  = {{0,0,0,0,0,0,0,0},{0,0,1,1,1,1,0,0},{0,1,0,0,0,0,1,0},{0,1,0,0,0,0,1,0},{0,1,0,0,0,0,1,0},{0,1,0,0,0,0,1,0},{0,0,1,1,1,1,0,0},{0,0,0,0,0,0,0,0}};
    uint8_t charMinus[8][8] = {{0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0},{0,1,1,1,1,1,1,0},{0,1,1,1,1,1,1,0},{0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0}};
    uint8_t charPlus[8][8]  = {{0,0,0,0,0,0,0,0},{0,0,0,1,1,0,0,0},{0,0,0,1,1,0,0,0},{0,1,1,1,1,1,1,0},{0,1,1,1,1,1,1,0},{0,0,0,1,1,0,0,0},{0,0,0,1,1,0,0,0},{0,0,0,0,0,0,0,0}};
    uint8_t settings[5][2]  = {{0x09,0x00},{0x0c,0x01},{0x0f,0x00},{0x0A,0x04},{0x0B,0x07}};

public:

    /**
     * \brief Constructor for Setup
     * Initializes stuff down below
     * \param spiBus basic spi stuff
     * \param chipSelect basic spi stuff
     * \param numberOfUnusedMatrices is the number of matrices that aren't used, these will display charSpace a 8x8 matrix filled with zeros. so the display won't display random stuff because of current leaking.
     * \param numberOfMatrices is the number of matrices you have hooked up.
     */
    Setup(hwlib::spi_bus & spiBus, hwlib::pin_out & chipSelect, int numberOfUnusedMatrices, int numberOfMatrices):
            spiBus(spiBus), chipSelect(chipSelect), numberOfUnusedMatrices(numberOfUnusedMatrices),numberOfMatrices(numberOfMatrices)
    {};

    /**
     * \brief This function takes a string and displays it on the matices.
     * There is a limit, you can only display 0 to 9, - and +. The max string length is 500.
     * The number of displayed chars on the this display is limited by the number of matrices
     * \param inputString
     */
    void operate(char* inputString);
};

