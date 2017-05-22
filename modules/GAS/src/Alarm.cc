/**
 * \file
 * \brief     The definitions of the alarm functionality of GAS-01
 * \author    Jeroen Kok
 * \copyright Copyright (c) 2017, The R2D2 Team
 * \license   See LICENSE
 */


#include Alarm.hh




void checkGasValue(int32_t gas_value) {
    if (gas_value > gasValueThreshold) {
        triggerAlarm();
    } else {
        disableAlarm();
    }
}

void triggerAlarm() {
//  fuction for turning the right pin on
}


void disableAlarm() {
//  fuction for turning the right pin off
}
