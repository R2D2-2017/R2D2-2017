
#pragma once

#include "wrap-hwlib.hh"


class Command
{
private:

    /**
     * spi pins
     */
    hwlib::spi_bus & spiBus;
    hwlib::pin_out & chipSelect;

    /**
     * variables used in .cc names represents their functionality
     */
    int numberOfMatrices;
    int numberOfRows;
    int stringLength;
    int numberOfWrites = 0;
    int numberOfCommands = 5;

    /**
    * matrices used in .cc names represents their functionality
    */
    uint8_t processedCommands[1000];
    uint8_t converterOutput[8][2];
    uint8_t commands[1000][8][2];


public:
    /**
     * \brief Constructor for command
     * Initializes stuff down below
     * \param spiBus basic spi stuff
     * \param chipSelect basic spi stuff
     * \param numberOfMatrices is the number of matrices you have hooked up.
     * \param numberOfRows contains the amount of rows that the matrices have.
     * \param stringLength contains length of given string
     */

    Command(hwlib::spi_bus & spiBus, hwlib::pin_out & chipSelect, int & numberOfMatrices , int & numberOfRows, int & stringLength):
    spiBus(spiBus), chipSelect(chipSelect), numberOfMatrices(numberOfMatrices), numberOfRows(numberOfRows), stringLength(stringLength)
    {};

    /**
     * \brief This function exsprects a 3d array. its is a array of matrices.
     * [1] Matrix number.
     * [2] Row number.
     * [3] Data that you want to write to the MAX7219.
     * \param commands commands you want to send to the MAX7219 chip.
     */
    void commander(uint8_t (*commands)[8][2]);

    /**
     * \brief This function is alot like commander but it sends settings to the MAX7219.
     * [1] Address you want to speak to
     * [2] Data you want to send
     * \param settingsList list of settings.
     */
    void settings(const uint8_t (*settingsList)[2]);

    /**
     * \brief This function converts a 8x8 matrix to a 8x2 matrix. This conversion makes the data use able for commander.
     * \param renderInput input
     * \param converterOutput output
     */
    void converter(uint8_t (*renderInput)[8], uint8_t (*converterOutput)[2]);

    /**
     * \brief This function accepts a 8x8 matrix and displays it on the matrices using commander and converter.
     * @param renderInput input
     */
    void render(uint8_t (*renderInput)[8]);

};





