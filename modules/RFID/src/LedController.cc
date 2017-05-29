/**
 * \LedController.cc
 * \author    Koen de Groot
 * \copyright Copyright (c) 2017, The R2D2 Team
 * \license   See LICENSE
 */

#include "LedController.hh"

void blinkLed(int Pin,int time)
{
    pinMode(pin,OUTPUTE);   //set GPIO pin to outpute
    digitalWrite(pin,1);    //turns led on
    delay(time);            //delays for time in ms
    digitalWrite(pin,0);    //turns led off
}
 