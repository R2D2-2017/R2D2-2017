/**
 * \led-controller.cc
 * \author    Koen de Groot
 * \copyright Copyright (c) 2017, The R2D2 Team
 * \license   See LICENSE
 */

#include "led-controller.hh"

#include <wiringPi.h>

void LedController::blinkLed(int pin,int time){
    pinMode(pin, OUTPUT);   //set GPIO pin to output
    digitalWrite(pin,1);    //turns led on
    delay(time);            //delays for time in ms
    digitalWrite(pin,0);    //turns led off
}
 