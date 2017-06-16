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
#include "speaker.hh"
#include "mq5.hh"

class Parser {
public:

    /**
     * \brief Constructor for Parser
     */
    Parser(Alarm &alarm, Speaker &speaker, Mq5 &mq5):
        alarm(alarm),
        speaker(speaker),
        mq5(mq5) {}

    //methode voor array lezen, naar enum toe.
    //verplaatsen van enum.hh naar een eigen configStorage.hh struct/class
    void parseArray(char* input);

private:

    Alarm &alarm;
    Speaker &speaker;
    Mq5 &mq5;

    bool ifContainsString(char array[], char* string);

};