/**
 * \file
 * \author    Wilco Louwerse
 * \author    Nicky van Steensel van der Aa
 * \author    David de Jong
 * \copyright Copyright (c) 2017, The R2D2 Team
 * \license   See LICENSE
 * \trello    https://trello.com/c/zSJnP0Rw/5-a-parser-must-be-made-that-can-read-the-conftxt-and-set-the-variables
 */

#include "parser.hh"

Parser::Parser(Alarm &alarm, Mq5 &mq5, int *measureWaitTime) :
        alarm(alarm),
        mq5(mq5),
        measureWaitTime(measureWaitTime) {}

bool Parser::ifContainsString(char array[], const char *string) {
    bool containsString = false;
    for (int i = 0; array[i] != '\0'; i++) {
        if (containsString) {break;}
        int stringPartial = 0;
        while (string[stringPartial] == array[i+stringPartial]) {
            if (string[stringPartial] == '\0') {
                containsString = true;
                break;
            }
            stringPartial++;
        }
    }
    return containsString;
}

bool Parser::parseArray(char* input) {

    // For loop integers.
    int i, j;

    // Read input array variables.
    for (i = 0; input[i] != '\0'; ++i) {

        // Start reading new variable at '@'.
        if (input[i] == '@') {

            // Reset variable value to 0.
            variableValue = 0;

            // Skip '@' character.
            i++;

            // Read variable name from input array.
            for (j = 0; input[i] != ':'; ++i, ++j) {
                // Prevent endless loop.
                if (input[i] == '\0') {
                    hwlib::cout << ">>>PARSER ERROR : while reading variable name, prevent endless loop!" << "\r\n";
                    return false;
                }
                variableName[j] = input[i];
            }
            variableName[j] = '\0';

            // Skip ':' character.
            i++;

            // Read variable value from input array (always int).
            for (j = 0; input[i] != '\n'; ++i, ++j) {
                // Prevent endless loop.
                if (input[i] == '\0') {
                    hwlib::cout << ">>>PARSER ERROR : while reading variable value for [ " << variableName
                                << " ], prevent endless loop!" << "\r\n";
                    return false;
                }
                if (variableValue != 0) {
                    // Multiply the value to add an extra zero so the next number can be added.
                    variableValue *= 10;
                }
                // Check if variable value is an integer or not.
                if ((input[i] < '0') || (input[i] > '9')) {
                    hwlib::cout << ">>>PARSER ERROR : while reading variable value for [ " << variableName
                                << " ], [ " << input[i] << " ] is not an integer!" << "\r\n";
                    return false;
                }
                // Convert a single char to an integer.
                variableValue += input[i] - '0';
            }

            // Set all variables.
            if (ifContainsString(variableName, firstNoteString)) {
                alarm.setFirstNote(variableValue);
            }
            else if (ifContainsString(variableName, secondNoteString)) {
                alarm.setSecondNote(variableValue);
            }
            else if (ifContainsString(variableName, warningThresholdString)) {
                alarm.setWarningThreshold(variableValue);
            }
            else if (ifContainsString(variableName, dangerThresholdString)) {
                alarm.setDangerThreshold(variableValue);
            }
            else if (ifContainsString(variableName, mq5CalibrationValueString)) {
                if (mq5.getMq5Iscalibrated()) {
                    mq5.setMq5CalibrationValue(variableValue);
                    mq5.setMq5Iscalibrated(true);
                } else {
                    hwlib::cout << "isCalibrated is false callibrationvalue will not be set \r\n";
                }
            }
            else if (ifContainsString(variableName, measureWaitTimeString)) {
                *measureWaitTime = variableValue;
            }
            else if (ifContainsString(variableName, isCalibratedString)) {
                mq5.setMq5Iscalibrated(static_cast<bool>(variableValue));
                hwlib::cout << "is calibrated = " << static_cast<bool>(variableValue) << "\r\n";
            } else {
                hwlib::cout << ">>>PARSER ERROR : [ " << variableName << " ] is not a valid/known variable!" << "\r\n";
                return false;
            }
        }
    }
    return true;
}
