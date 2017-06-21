/**
 * \led-controller.cc
 * \author    Koen de Groot, Ricardo Bouwman
 * \copyright Copyright (c) 2017, The R2D2 Team
 * \license   See LICENSE
 */

#include "led-controller.hh"

#include <wiringPi.h>

LedController::LedController(int pin) : pin(pin){
	pinMode(pin, OUTPUT); // set GPIO pin to output
}

void LedController::blinkLed(unsigned int time) {
    digitalWrite(pin, 1); // turns led on
    delay(time);          // delays for time in ms
    digitalWrite(pin, 0); // turns led off
}
