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
* \brief Read and set the settings from a read given input array.
*
* \param    input The input array to parse.
* \return   Returns whether parsing was successful or not.
*/
bool parseArray(const char *input, int &measureWaitTime, Alarm &alarm, Mq5 &mq5);

// Variables that the parser checks for in the conf file and their associated strings.
namespace ParserStrings {
    const char *firstNote            = "firstNote";
    const char *secondNote           = "secondNote";
    const char *warningThreshold     = "warningThreshold";
    const char *dangerThreshold      = "dangerThreshold";
    const char *mq5CalibrationValue  = "mq5CalibrationValue";
    const char *measureWaitTime      = "measureWaitTime";
    const char *isCalibrated         = "isCalibrated";
};


