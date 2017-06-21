/**
 * \file
 * \author    Mike Hilhorst
 * \copyright Copyright (c) 2017, The R2D2 Team
 * \license   See LICENSE
 */
#include "setup.hh"

/// Chars that can be displayed.
static const uint8_t charSpace[8][8] = {
        {1,1,0,0,0,0,0,0}, {0,0,1,1,1,0,0,0},
        {0,1,1,1,1,0,0,0}, {0,0,0,1,1,0,0,0},
        {0,0,0,1,1,0,0,0}, {0,0,0,1,1,0,0,0},
        {0,1,1,1,1,1,1,0}, {0,0,0,0,0,0,0,0}};
static const uint8_t charOne[8][8] = {
        {0,0,0,0,0,0,0,0}, {0,0,1,1,1,0,0,0},
        {0,1,1,1,1,0,0,0}, {0,0,0,1,1,0,0,0},
        {0,0,0,1,1,0,0,0}, {0,0,0,1,1,0,0,0},
        {0,1,1,1,1,1,1,0}, {0,0,0,0,0,0,0,0}};
static const uint8_t charTwo[8][8] = {
        {0,0,0,0,0,0,0,0}, {0,1,1,1,1,1,0,0},
        {0,0,0,0,0,1,1,0}, {0,0,0,0,0,1,1,0},
        {0,0,0,0,1,1,0,0}, {0,0,0,1,1,0,0,0},
        {0,1,1,1,1,1,1,0}, {0,0,0,0,0,0,0,0}};
static const uint8_t charThree[8][8] = {
        {0,0,0,0,0,0,0,0}, {0,1,1,1,1,1,0,0},
        {0,0,0,0,0,1,1,0}, {0,0,0,1,1,1,1,0},
        {0,0,0,1,1,1,1,0}, {0,0,0,0,0,1,1,0},
        {0,1,1,1,1,1,0,0}, {0,0,0,0,0,0,0,0}};
static const uint8_t charFour[8][8] = {
        {0,0,0,0,0,0,0,0}, {0,0,0,0,0,1,0,0},
        {0,0,0,0,1,1,0,0}, {0,0,0,1,0,1,0,0},
        {0,0,1,0,0,1,0,0}, {0,1,1,1,1,1,1,0},
        {0,0,0,0,0,1,0,0}, {0,0,0,0,0,0,0,0}};
static const uint8_t charFive[8][8] = {
        {0,0,0,0,0,0,0,0}, {0,1,1,1,1,1,1,0},
        {0,1,0,0,0,0,0,0}, {0,1,1,1,1,1,0,0},
        {0,0,0,0,0,0,1,0}, {0,0,0,0,0,0,1,0},
        {0,1,1,1,1,1,0,0}, {0,0,0,0,0,0,0,0}};
static const uint8_t charSix[8][8] = {
        {0,0,0,0,0,0,0,0}, {0,0,1,1,1,1,1,0},
        {0,1,0,0,0,0,0,0}, {0,1,1,1,1,1,0,0},
        {0,1,0,0,0,0,1,0}, {0,1,0,0,0,0,1,0},
        {0,0,1,1,1,1,0,0}, {0,0,0,0,0,0,0,0}};
static const uint8_t charSeven[8][8] = {
        {0,0,0,0,0,0,0,0}, {0,1,1,1,1,1,1,0},
        {0,0,0,0,0,1,1,0}, {0,0,0,0,1,1,0,0},
        {0,0,0,1,1,0,0,0}, {0,0,1,1,0,0,0,0},
        {0,1,1,0,0,0,0,0}, {0,0,0,0,0,0,0,0}};
static const uint8_t charEight[8][8] = {
        {0,0,0,0,0,0,0,0}, {0,0,1,1,1,1,0,0},
        {0,1,0,0,0,0,1,0}, {0,0,1,1,1,1,0,0},
        {0,1,0,0,0,0,1,0}, {0,1,0,0,0,0,1,0},
        {0,0,1,1,1,1,0,0}, {0,0,0,0,0,0,0,0}};
static const uint8_t charNine[8][8] = {
        {0,0,0,0,0,0,0,0}, {0,0,1,1,1,1,0,0},
        {0,1,0,0,0,0,1,0}, {0,0,1,1,1,1,1,0},
        {0,0,0,0,0,0,1,0}, {0,0,0,0,0,0,1,0},
        {0,0,1,1,1,1,0,0}, {0,0,0,0,0,0,0,0}};
static const uint8_t charZero[8][8] = {
        {0,0,0,0,0,0,0,0}, {0,0,1,1,1,1,0,0},
        {0,1,0,0,0,0,1,0}, {0,1,0,0,0,0,1,0},
        {0,1,0,0,0,0,1,0}, {0,1,0,0,0,0,1,0},
        {0,0,1,1,1,1,0,0}, {0,0,0,0,0,0,0,0}};
static const uint8_t charMinus[8][8] = {
        {0,0,0,0,0,0,0,0}, {0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0}, {0,1,1,1,1,1,1,0},
        {0,1,1,1,1,1,1,0}, {0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0}, {0,0,0,0,0,0,0,0}};
static const uint8_t charPlus[8][8] = {
        {0,0,0,0,0,0,0,0}, {0,0,0,1,1,0,0,0},
        {0,0,0,1,1,0,0,0}, {0,1,1,1,1,1,1,0},
        {0,1,1,1,1,1,1,0}, {0,0,0,1,1,0,0,0},
        {0,0,0,1,1,0,0,0}, {0,0,0,0,0,0,0,0}};
static const uint8_t settings[5][2] = {{0x09,0x00},{0x0c,0x01},{0x0f,0x00},{0x0A,0x04},{0x0B,0x07}};

void Setup::displayString(const char *inputString) {
    int stringLength = sizeof(inputString) / sizeof(inputString[0]) + numberOfUnusedMatrices;
    MatrixDisplayParser display(spiBus, chipSelect, numberOfMatrices, numberOfRows);
    display.settings(settings);

    for (int i = 0; i < numberOfUnusedMatrices; i++) {
        display.render(charSpace, stringLength);
    }

    for (int i = 0; i < stringLength - numberOfUnusedMatrices; i++) {
        switch (inputString[i]) {
            case '1' : display.render(charOne,   stringLength); break;
            case '2' : display.render(charTwo,   stringLength); break;
            case '3' : display.render(charThree, stringLength); break;
            case '4' : display.render(charFour,  stringLength); break;
            case '5' : display.render(charFive,  stringLength); break;
            case '6' : display.render(charSix,   stringLength); break;
            case '7' : display.render(charSeven, stringLength); break;
            case '8' : display.render(charEight, stringLength); break;
            case '9' : display.render(charNine,  stringLength); break;
            case '0' : display.render(charZero,  stringLength); break;
            case '+' : display.render(charPlus,  stringLength); break;
            case '-' : display.render(charMinus, stringLength); break;
            default  : display.render(charSpace, stringLength); break;
        }
    }
}
