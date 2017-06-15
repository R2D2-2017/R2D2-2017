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

    //read array values

    //set read values in enum
    Note::highNote = 880;
    Note::lowNote = 698;
    ConfigStorage::warningThreshold = 0;
    ConfigStorage::dangerThreshold = 0;
    ConfigStorage::mq5BaseValue = 0;
    ConfigStorage::measureFrequency = 0;
}

void setConfigSettings() {

}