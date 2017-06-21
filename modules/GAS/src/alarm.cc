/**
 * \file
 * \author    Jeroen Kok
 * \author    Robbie Valkenburg
 * \author    Mike Hilhorst
 * \author    Nicky van Steensel van der Aa
 * \copyright Copyright (c) 2017, The R2D2 Team
 * \license   See LICENSE
 */

#include "alarm.hh"

void Alarm::checkGasValue(uint32_t gasValue) {
    if (gasValue > dangerThreshold) {
        greenAlarmLed.set(false);
        yellowAlarmLed.set(false);
        redAlarmLed.set(true);

        for (int amountOfPlaying = 3; amountOfPlaying >= 0; amountOfPlaying--) {
            dangerPlayer.playNote(firstNote);
            dangerPlayer.playNote(secondNote);
        }
    } else if (gasValue > warningThreshold && gasValue <= dangerThreshold) {
        greenAlarmLed.set(false);
        yellowAlarmLed.set(true);
        redAlarmLed.set(false);
        warningPlayer.playNote(firstNote);
        warningPlayer.playNote(secondNote);
    } else {
        greenAlarmLed.set(true);
        yellowAlarmLed.set(false);
        redAlarmLed.set(false);
    }
}

void Alarm::setFirstNote(int note) {
    firstNote = note;
}

void Alarm::setSecondNote(int note) {
    secondNote = note;
}

void Alarm::setWarningThreshold(int threshold) {
    warningThreshold = threshold;
}

void Alarm::setDangerThreshold(int threshold) {
    dangerThreshold = threshold;
}
