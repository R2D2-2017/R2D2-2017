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

void Alarm::checkGasValue(float gasValue) {
    if (gasValue > gasValueThreshold) {
        triggerAlarm();
    } else {
        alarmLed.set(false);
    }
}

void Alarm::setFirstNote(int Note) {
	firstNote = Note;
}

void Alarm::setSecondNote(int Note) {
	secondNote = Note;
}

void Alarm::setWarningThreshold(int warningThreshold) {
	//TODO implement shit
}

void Alarm::setDangerThreshold(int dangerThreshold) {
	//TODO implement shit
}

void Alarm::triggerAlarm() {
    alarmLed.set(true);
    for(int amountOfPlaying = 3; amountOfPlaying >= 0; amountOfPlaying--) {
        player.playNote((int) firstNote);
        player.playNote((int) secondNote);
    };

}



