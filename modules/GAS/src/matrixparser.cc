/**
 * \file
 * \author    Mike Hilhorst
 * \copyright Copyright (c) 2017, The R2D2 Team
 * \license   See LICENSE
 */

#include "matrixparser.hh"

void MatrixDisplayParser::spiParseAndSend(const uint8_t (*dataToSend)[8][2]) {
    for (int j = 0; j <= numberOfRows; j++) {
        int l = 0;
        for (int k = 0; k < numberOfMatrices; k++) {
            processedCommands[l++] = {(uint8_t) j};
            processedCommands[l++] = {dataToSend[k][j - 1][1]};
        }
        spiBus.write_and_read(chipSelect, static_cast<const size_t >(2 * numberOfMatrices), processedCommands, nullptr);
    }
}

void MatrixDisplayParser::settings(const uint8_t (*settingsList)[2]) {
    for (int i = 0; i < numberOfCommands; i++) {
        int l = 0;
        for (int k = 0; k < numberOfMatrices; k++) {
            processedCommands[l++] = {settingsList[i][0]};
            processedCommands[l++] = {settingsList[i][1]};
        }
        spiBus.write_and_read(chipSelect, static_cast<const size_t >(2 * numberOfMatrices), processedCommands, nullptr);
    }
}

void MatrixDisplayParser::converter(const uint8_t (*renderInput)[8], uint8_t (*converterOutput)[2]) {
    for (uint8_t i = 0; i < 8; i++) {
        uint8_t shiftVariable = 0;
        int rowCounter = 0;
        for (int j = 8; j >= 0; j--) {
            shiftVariable |= renderInput[i][rowCounter - 1] << (j);
            rowCounter++;
        }
        converterOutput[i][0] = i + static_cast<uint8_t >(1);
        converterOutput[i][1] = shiftVariable;
    }

}

void MatrixDisplayParser::render(const uint8_t (*renderInput)[8], const size_t stringLength) {
    converter(renderInput, converterOutput);
    for (int i = 0; i < numberOfRows; i++) {
        commands[numberOfWrites++][i][1] = converterOutput[i][1];
    }
    if (numberOfWrites == stringLength) {
        numberOfWrites = 0;
        spiParseAndSend(commands);
    }
}

