/**
 * \file
 * \brief     The definitions of the alarm functionality of GAS-01
 * \author    Jeroen Kok, Robbie valkenburg en Mike Hilhorst
 * \copyright Copyright (c) 2017, The R2D2 Team
 * \license   See LICENSE
 */

#include "alarm.hh"

void Alarm::checkGasValue(float gasValue) {
    if (gasValue < gasValueThreshold) {
        triggerAlarm();
    } else {
        alarmLed.set(false);
    }
}

void Alarm::triggerAlarm() {
    alarmLed.set(true);
    for(int amountOfPlaying = 3; amountOfPlaying >= 0; amountOfPlaying--) {
        player.playNote((int) Note::highNote);
        player.playNote((int) Note::lowNote);
    };

}



