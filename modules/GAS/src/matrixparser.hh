/**
 * \file
 * \brief     Class that contains the functions that are needed to display text on the MAX7219.
 * \author    Mike Hilhorst
 * \copyright Copyright (c) 2017, The R2D2 Team
 * \license   See LICENSE
 */

#pragma once

#include "wrap-hwlib.hh"


class MatrixDisplayParser {
private:

    /**
     * SPI pins.
     */
    hwlib::spi_bus &spiBus;
    hwlib::pin_out &chipSelect;

   /// Amount of matrices used to display text.
    int numberOfMatrices;

    /// Number of rows per matrix.
    int numberOfRows;

    /// Used to give each character its proper location in the array
    /// and at the end it is used to check if all characters have been processed.
    ///int numberOfWrites = 0;

    /// Represents the size of a matrix and is used to prevent no junk data is added to them.
    int numberOfCommands = 5;

    /**
    * \brief Matrices used in .cc names represents their functionality.
     *
     * The size of the matrices and arrays support up to 20 characters.
    */
    uint8_t processedCommands[20];
    uint8_t converterOutput[8][2];
    uint8_t commands[20][8][2];
    /**
     * \brief Allows commands to be send via Hwlib SPI to the led matrix.
     *
     * This function expects a pointer to an array. This array contains a set of 8x2 matrices
     * that in turn contains the data that to be written per row, to the display matrices.
     * A example of one of these matrices {{0x00, 0xff},{0x01, 0xff}...{0x07, 0xff}
     * where the first hexadecimal value of the size 2 array is the address of of the led row on the matrix
     * and the second hexadecimal value is which leds to light up in bitwise fassion.
     * As in {0x00, 0xFF} light up all leds on row 0 of the matrix in question.
     *
     * \param[in] dataToSend A pointer to a location in an array that contains an 8x2 matrix.
     */
    void spiParseAndSend(const uint8_t (*dataToSend)[8][2]);

    /**
     * \brief This function converts a 8x8 matrix to a 8x2 matrix.
     *
     * This conversion makes the data use able for commander.
     * \param[in] renderInput       Accept 8x8 matrix.
     * \param[out] converterOutput  8x2 matrix.
     */
    void converter(const uint8_t (*renderInput)[8], uint8_t (*converterOutput)[2]);

public:
    /**
     * \brief Constructor for command.
     *
     * Initializes stuff down below.
     * \param spiBus            Basic spi stuff.
     * \param chipSelect        Basic spi stuff.
     * \param numberOfMatrices  Is the number of matrices you have hooked up.
     * \param numberOfRows      Contains the amount of rows that the matrices have.
     */

    MatrixDisplayParser(hwlib::spi_bus &spiBus, hwlib::pin_out &chipSelect, int numberOfMatrices, int numberOfRows) :
            spiBus(spiBus), chipSelect(chipSelect), numberOfMatrices(numberOfMatrices), numberOfRows(numberOfRows){};

    /**
     * \brief This function is allot like commander but it sends settings to the MAX7219.
     *
     * [1] Address you want to speak to.
     * [2] Data you want to send.
     * \param settingsList list of settings.
     */
    void settings(const uint8_t (*settingsList)[2]);

    /**
     * \brief This function accepts a 8x8 matrix and displays it on the display matrices using commander and converter.
     *
     * \param[in] renderInput   Accepts 8x8 matrix.
     * \param[in] stringLength  Size of text to display on led matrices.
     */
    void render(const uint8_t (*renderInput)[8], const int stringLength);
};
