/**
 * \file
 * \brief     INSERT A DESCRIPTION HERE
 * \author    INSERT YOUR NAME HERE
 * \copyright Copyright (c) 2017, The R2D2 Team
 * \license   See LICENSE
 */
#include <iostream>
#include "wiringPi.h"
#include "hc-sr04.hh"

int main(int argc, char **argv) {

    wiringPiSetup();

    int Triggerpin = 0;
    int Echopin    = 2;

    hcSr04 sensor(Triggerpin,Echopin);
    sensor.get();
}
