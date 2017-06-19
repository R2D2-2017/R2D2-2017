/**
 * \file
 * \brief     The declarations of the class Alarm of GAS-01
 * \author    Jeroen Kok, Robbie Vlakenburg, Mike Hilhorst en Nicky van Steensel van der Aa.
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

	/**
	* \brief Set the firstNote to this value
	* \param Note the first tone to be played 
	*/
	void setFirstNote(int Note);

	/**
	* \brief Set the SecondNote to this value
	* \param Note the second tone to be played
	*/
	void setSecondNote(int Note);

	/**
	* \brief Sets the threshold of the alarm warning
	* \param warningThreshold the value to be set
	*/
	void setWarningThreshold(int warningThreshold);

	/**
	* \brief Sets the threshold of the danger alarm
	* \param dangerThreshold the value to be set
	*/
	void setDangerThreshold(int dangerThreshold);

private:

    /**
     * Alarm threshold set by constructor
     */
    float gasValueThreshold;

	/**
	* The first note to be played
	*/
	int firstNote = 880;

	/**
	* The second note to be played
	*/
	int secondNote = 698;

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
