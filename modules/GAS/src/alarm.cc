/**
 * \file
 * \brief     The definitions of the alarm functionality of GAS-01
 * \author    Jeroen Kok
 * \copyright Copyright (c) 2017, The R2D2 Team
 * \license   See LICENSE
 */


#include "alarm.hh"

// Magicly decided on which pin to use. Feel free to change.
auto led0 = hwlib::target::pin_out( hwlib::target::pins::d7 );

/// Just a magic number at the moment
float gasValueThreshold = 2.0f;

void checkGasValue(float gasValue) {
    if (gasValue > gasValueThreshold) {
        triggerAlarm();
    } else {
        disableAlarm();
    }
}

void triggerAlarm() {
    led0.set( 1 );
}

void disableAlarm() {
    led0.set( 0 );
}