/**
 * \file
 * \brief     The definitions of the alarm functionality of GAS-01
 * \author    Jeroen Kok
 * \copyright Copyright (c) 2017, The R2D2 Team
 * \license   See LICENSE
 */


#include "alarm.hh"

void Alarm::checkGasValue(float gasValue) {
    if (gasValue > gasValueThreshold) {
        triggerAlarm();
    } else {
        disableAlarm();
    }
}

void Alarm::triggerAlarm() {
    alarmLed.set(1);
}

void Alarm::disableAlarm() {
    alarmLed.set(0);
}
