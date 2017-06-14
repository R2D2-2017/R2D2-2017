/**
 * \file      matrix-keypad.cc
 * \brief     Library for a 3x4 or 4x4 keypad
 * \author    Tim IJntema, René de Kluis, Ricardo Bouwman
 * \copyright Copyright (c) 2017, The R2D2 Team
 * \license   See LICENSE
 */

#include "matrix-keypad.hh"
#include <iostream>

MatrixKeypad::MatrixKeypad(const int *row, const int *column, int colSize):
    colSize(colSize),
    row(row),
    column(column)
{
    // Making sure the column size is within range
    if (colSize < 3 || colSize > 4){
        std::cerr << "Column size " << colSize << " higher or lower than the allowed range\n";
        exit(EXIT_FAILURE);
    }
}

char MatrixKeypad::getKey() {
    for (int currentCol = 0; currentCol < colSize; currentCol++) {
        pinMode(column[currentCol], OUTPUT);
        digitalWrite(column[currentCol], 0);
        for (int currentRow = 0; currentRow < rowSize; currentRow++) {
            pinMode(row[currentRow], INPUT);
            pullUpDnControl(row[currentRow], PUD_UP);
            if (digitalRead(row[currentRow]) == 0) {
                keypadRow = currentRow;
            }
        }
    }
    for (int currentRow = 0; currentRow < rowSize; currentRow++) {
        pinMode(row[currentRow], OUTPUT);
        digitalWrite(row[currentRow], 0);
        for (int currentCol = 0; currentCol < colSize; currentCol++) {
            pinMode(column[currentCol], INPUT);
            pullUpDnControl(column[currentCol], PUD_UP);
            if (digitalRead(column[currentCol]) == 0) {
                return keypad[keypadRow][currentCol];
            }
        }
    }
    return 'h';
}
