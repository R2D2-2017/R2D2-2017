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

bool ifContainsString(const char *array, const char *string) {
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

bool parseArray(const char *input, int &measureWaitTime, Alarm &alarm, Mq5 &mq5) {

    char variableName[20];
    int variableValue = 0;

    // Read input array variables.
    for (int i = 0, j = 0; input[i] != '\0'; ++i) {

        // Start reading new variable at '@'.
        if (input[i] == '@') {
            variableValue = 0;

            // Skip '@' character.
            i++;

            // Read variable name from input array.
            for (j = 0; input[i] != ':'; ++i, ++j) {
                // Prevent endless loop.
                if (input[i] == '\0') {
                    hwlib::cout << "Error while reading variable name" << "\r\n";
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
                    hwlib::cout << "Unexpected end of string after '@': [ " << variableName
                                << " ]\r\n";
                    return false;
                }
                // Multiply the value to add an extra zero so the next number can be added.
                variableValue *= 10;


                // Check if variable value is an integer or not.
                if ((input[i] < '0') || (input[i] > '9')) {
                    hwlib::cout << "Error while reading variable value for [ " << variableName
                                << " ], [ " << input[i] << " ] is not an integer\r\n";
                    return false;
                }
                // Convert a single char to an integer.
                variableValue += input[i] - '0';
            }

            // Set all variables.
            if (ifContainsString(variableName, parserStrings_t::firstNote)) {
                alarm.setFirstNote(variableValue);
            }
            else if (ifContainsString(variableName, parserStrings_t::secondNote)) {
                alarm.setSecondNote(variableValue);
            }
            else if (ifContainsString(variableName, parserStrings_t::warningThreshold)) {
                alarm.setWarningThreshold(variableValue);
            }
            else if (ifContainsString(variableName, parserStrings_t::dangerThreshold)) {
                alarm.setDangerThreshold(variableValue);
            }
            else if (ifContainsString(variableName, parserStrings_t::mq5CalibrationValue)) {
                if (mq5.isMq5Calibrated()) {
                    mq5.setMq5CalibrationValue(variableValue);
                    mq5.setMq5IsCalibrated(true);
                } else {
                    hwlib::cout << "isCalibrated is false calibration value will not be set \r\n";
                }
            }
            else if (ifContainsString(variableName, parserStrings_t::measureWaitTime)) {
                measureWaitTime = variableValue;
            }
            else if (ifContainsString(variableName, parserStrings_t::isCalibrated)) {
                mq5.setMq5IsCalibrated(static_cast<bool>(variableValue));
                hwlib::cout << "is calibrated = " << static_cast<bool>(variableValue) << "\r\n";
            } else {
                hwlib::cout << ">>>PARSER ERROR : [ " << variableName << " ] is not a valid/known variable!" << "\r\n";
                return false;
            }
        }
    }
    return true;
}
