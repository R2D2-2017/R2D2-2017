/**
 * \file
 * \brief     The declarations of the class Parser of GAS-03, used for reading and setting the config variables
 *            from an given array with these variables.
 *
 * \author      Wilco Louwerse
 * \author      Nicky van Steensel van der Aa
 * \author      David de Jong
 * \copyright Copyright (c) 2017, The R2D2 Team
 * \license   See LICENSES
 * \trello    https://trello.com/c/zSJnP0Rw/5-a-parser-must-be-made-that-can-read-the-conftxt-and-set-the-variables
 */

#pragma once

#include "wrap-hwlib.hh"
#include "alarm.hh"
#include "mq5.hh"

class Parser {
public:

    /**
    * \brief Constructor for Parser.
    *
    * \param alarm                 This is the alarm object where some of the alarm related settings will be set.
    * \param mq5                   This is the mq5 object where some of the mq-5 sensor related settings will be set.
    * \param measureWaitTime       This is a pointer to a setting value in the main that will be set.
    */
    Parser(Alarm &alarm, Mq5 &mq5, int *measureWaitTime);

    /**
    * \brief Read and set the settings from a read given input array.
    *
    * \param    Input The input array to parse.
    * \return   Returns whether parsing was successful or not.
    */
    bool parseArray(char *input);

private:

    /**
     * \brief Checks if a given array contains a given string.
     *
     * \param array     The given array to check with.
     * \param string    The given string to check with.
     * \return          Returns true if the given array contains the given string.
     */
    bool ifContainsString(char array[], const char *string);

    Alarm &alarm;
    Mq5 &mq5;

    int *measureWaitTime;
    char variableName[20];
    int variableValue = 0;

    // Variables that the parser checks for in the conf file and their associated strings.
    const char *firstNoteString             = "firstNote";
    const char *secondNoteString            = "secondNote";
    const char *warningThresholdString      = "warningThreshold";
    const char *dangerThresholdString       = "dangerThreshold";
    const char *mq5CalibrationValueString   = "mq5CalibrationValue";
    const char *measureWaitTimeString       = "measureWaitTime";
	const char *isCalibratedString          = "isCalibrated";

};
