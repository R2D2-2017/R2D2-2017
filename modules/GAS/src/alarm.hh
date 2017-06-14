/**
 * \file
 * \brief     The declarations of the class Alarm of GAS-01
 * \author    Jeroen Kok, Robbie Vlakenburg en Mike Hilhorst.
 * \copyright Copyright (c) 2017, The R2D2 Team
 * \license   See LICENSE
 */

#pragma once

#include "wrap-hwlib.hh"
#include "speaker.hh"
#include "enum.hh"

class Alarm {
public:

    /**
     * \brief Constructor for Alarm
     * Initializes gasValueThreshold ,alarmLed and speaker
     */
    Alarm(float gasValueThreshold, hwlib::pin_out &alarmLed, Speaker &player):
            gasValueThreshold(gasValueThreshold),
            alarmLed(alarmLed),
            player(player) {}

    /**
     * \brief Check if gas value is above the threshold then trigger the alarm
     * Take the gas value and call triggerAlarm() when it's above the
     * threshold or disableAlarm() when it's below said threshold.
     * \param gasValue the gas value
     */
    void checkGasValue(float gasValue);

private:

    /**
     * Alarm threshold set by constructor
     */
    float gasValueThreshold;

    /**
     * The pin the alarm is connected to
     */
    hwlib::pin_out &alarmLed;

    /**
     * The player that will make the speaker play sound.
     **/

    Speaker &player;

    /**
     * \brief Turn the alarm on
     */
    void triggerAlarm();

};
