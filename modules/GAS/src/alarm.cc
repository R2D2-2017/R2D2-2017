/**
 * \file
 * \brief     The definitions of the alarm functionality of GAS-01
 * \author    Jeroen Kok
 * \author    Robbie valkenburg
 * \author    Mike Hilhorst
 * \copyright Copyright (c) 2017, The R2D2 Team
 * \license   See LICENSE
 */

#include "alarm.hh"

void Alarm::checkGasValue(int gasValue) {
    if(gasValue > dangerThreshold){
        greenAlarmLed.set(false);
        yellowAlarmLed.set(false);
        redAlarmLed.set(true);

        for(int amountOfPlaying = 3; amountOfPlaying >= 0; amountOfPlaying--) {
            dangerPlayer.playNote((int) Note::highNote);
            dangerPlayer.playNote((int) Note::lowNote);
        }
    }

    else if (gasValue >= warningThreshold && gasValue < dangerThreshold){
        greenAlarmLed.set(false);
        yellowAlarmLed.set(true);
        redAlarmLed.set(false);
        warningPlayer.playNote((int) Note::highNote);
        warningPlayer.playNote((int) Note::lowNote);
    }

    else {
        greenAlarmLed.set(true);
        yellowAlarmLed.set(false);
        redAlarmLed.set(false);
    }
}




