/**
 * \file
 * \brief     The definitions of the alarm functionality of GAS-01
 * \author    Jeroen Kok
 * \author    Robbie valkenburg
 * \author    Mike Hilhorst
 * \author    Nicky van Steensel van der Aa
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
            dangerPlayer.playNote(firstNote);
            dangerPlayer.playNote(secondNote);
        }
    }

    else if (gasValue >= warningThreshold && gasValue <= dangerThreshold){
        greenAlarmLed.set(false);
        yellowAlarmLed.set(true);
        redAlarmLed.set(false);
        warningPlayer.playNote(firstNote);
        warningPlayer.playNote(secondNote);
    }
	else {
		greenAlarmLed.set(true);
		yellowAlarmLed.set(false);
		redAlarmLed.set(false);
	}
}

void Alarm::setFirstNote(int Note) {
	firstNote = Note;
}

void Alarm::setSecondNote(int Note) {
	secondNote = Note;
}

void Alarm::setWarningThreshold(int Threshold) {
	warningThreshold = Threshold;
}

void Alarm::setDangerThreshold(int Threshold) {
	dangerThreshold = Threshold;
}
