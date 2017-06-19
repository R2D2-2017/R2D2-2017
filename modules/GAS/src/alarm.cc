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
            dangerPlayer.playNote((int) Note::highNote);
            dangerPlayer.playNote((int) Note::lowNote);
        }
    }

<<<<<<< HEAD
    else if (gasValue >= warningThreshold && gasValue < dangerThreshold){
        greenAlarmLed.set(false);
        yellowAlarmLed.set(true);
        redAlarmLed.set(false);
        warningPlayer.playNote((int) Note::highNote);
        warningPlayer.playNote((int) Note::lowNote);
    }
=======
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
>>>>>>> feat-gas-new-parser

    else {
        greenAlarmLed.set(true);
        yellowAlarmLed.set(false);
        redAlarmLed.set(false);
    }
}




