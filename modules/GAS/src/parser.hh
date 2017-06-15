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

#include "wrap-hwlib.hh"
#include "enum.hh"

class Parser {
public:

    /**
     * \brief Constructor for Parser
     */
    parser(){}

    //methode voor array lezen, naar enum toe.
    void parseArray(char inputArray[]);

    //methode voor uit enum alle settings setten.
    //verplaatsen van enum.hh naar een eigen configStorage.hh struct/class
    void setConfigSettings();

};