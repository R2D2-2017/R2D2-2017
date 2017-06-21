/**
 * \file
 * \brief       The declarations of the class Parser of GAS-03, used for reading and setting the config variables
 *              from an given array with these variables.
 *
 * \author      Wilco Louwerse
 * \author      Nicky van Steensel van der Aa
 * \author      David de Jong
 * \copyright   Copyright (c) 2017, The R2D2 Team
 * \license     See LICENSES
 *              https://trello.com/c/zSJnP0Rw/5-a-parser-must-be-made-that-can-read-the-conftxt-and-set-the-variables
 */

#pragma once

#include "wrap-hwlib.hh"
#include "alarm.hh"
#include "mq5.hh"

/**
 * \brief Checks if a given array contains a given string.
 *
 * \param[in] array     The given array to check with.
 * \param[in] string    The given string to check with.
 * \return          Returns true if the given array contains the given string.
 */
bool ifContainsString(const char *array, const char *string);

/**
* \brief Read and set the settings from a read given input array.
*
* \param    input The input array to parse.
* \return   Returns whether parsing was successful or not.
*/
bool parseArray(const char *input, int &measureWaitTime, Alarm &alarm, Mq5 &mq5);

// Variables that the parser checks for in the conf file and their associated strings.
typedef const struct ParserStrings {
    static constexpr char *firstNote            = (char*)"firstNote";
    static constexpr char *secondNote           = (char*)"secondNote";
    static constexpr char *warningThreshold     = (char*)"warningThreshold";
    static constexpr char *dangerThreshold      = (char*)"dangerThreshold";
    static constexpr char *mq5CalibrationValue  = (char*)"mq5CalibrationValue";
    static constexpr char *measureWaitTime      = (char*)"measureWaitTime";
    static constexpr char *isCalibrated         = (char*)"isCalibrated";
} parserStrings_t;


