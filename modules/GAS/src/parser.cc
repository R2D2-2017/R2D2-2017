/**
 * \file
 * \brief     The definitions of the parser functionality of GAS-03.
 * \author    Wilco Louwerse
 * \author	  Nicky van Steensel van der Aa
 * \copyright Copyright (c) 2017, The R2D2 Team
 * \license   See LICENSE
 * \wiki      ...
 * \trello    https://trello.com/c/zSJnP0Rw/5-a-parser-must-be-made-that-can-read-the-conftxt-and-set-the-variables
 */

#include "parser.hh"

void Parser::parseArray(char inputArray[]) {

    char variableName[20];
    char variableValue[5];
    int i, j;

    //read array values
    //example:      @highNote:880#
    for(i = 0; i < inputArray[i] != '\0'; i++) {
        if(inputArray[i] == '@') {
            for(j = 0; inputArray[i] != ':'; i++, j++) {
                variableName[j] = inputArray[i];
            }
            i++;
            for(j = 0; inputArray[i] != '#'; i++, j++) {    //zou een #achteraan moeten om dit te kunnen laten werken
                variableValue[j] = inputArray[i];
            }
            if(variableName == "highNote") {            //dit is waarschijnlijk niet mogelijk?
                Note::highNote = (int)variableValue;    //en dit moet ook anders :) , maar je snapt hopelijk het idee.
            }
            memset( variableName, 0, sizeof(variableName) );
            memset( variableValue, 0, sizeof(variableValue) );
        }
    }

    //set read values in enum
    Note::highNote = 880;
    Note::lowNote = 698;
    ConfigStorage::warningThreshold = 0;
    ConfigStorage::dangerThreshold = 0;
    ConfigStorage::mq5BaseValue = 0;
    ConfigStorage::measureFrequency = 0;
}