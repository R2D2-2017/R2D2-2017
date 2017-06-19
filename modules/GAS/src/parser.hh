/**
 * \file
 * \brief     The declarations of the class Parser of GAS-03, used for ...
 * \author    Wilco Louwerse
 * \author	  Nicky van Steensel van der Aa
 * \copyright Copyright (c) 2017, The R2D2 Team
 * \license   See LICENSE
 * \wiki      ...
 * \trello    https://trello.com/c/zSJnP0Rw/5-a-parser-must-be-made-that-can-read-the-conftxt-and-set-the-variables
 */

#pragma once

#include "wrap-hwlib.hh"
#include "alarm.hh"
#include "mq5.hh"

class Parser {
public:

    /**
     * \brief Constructor for Parser
     */
    Parser(Alarm &alarm, Mq5 &mq5);

    /**
     * \brief
     * @param input the input to parse
     */
    void parseArray(char* input);

private:

    Alarm &alarm;
    Mq5 &mq5;

    char variableName[20];
    int variableValue = 0;

    char firstNoteString[10]            = "firstNote";
    char secondNoteString[11]           = "secondNote";
    char warningThresholdString[17]     = "warningThreshold";
    char dangerThresholdString[16]      = "dangerThreshold";
    char mq5CalibrationValueString[20]  = "mq5CalibrationValue";
    char measureFrequencyString[17]     = "measureFrequency";
	char isCalibratedString[13]			= "isCalibrated";

    bool ifContainsString(char array[], char* string);

};
