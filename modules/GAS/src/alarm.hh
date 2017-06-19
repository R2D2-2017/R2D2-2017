/**
 * \file
<<<<<<< HEAD
 * \brief     The declarations of the class Alarm of GAS-03
 * \author    Jeroen Kok
 * \author    Robbie Vlakenburg
 * \author    Mike Hilhorst.
 * \author    Nicky van Steensel van der Aa.
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
     * Initializes stuff down below
     * \param warningThreshold is the threshold where the warning-speaker and the yellow led should be turned on.
     * \param dangerThreshold is the threshold where the danger-speaker and the red led should be turned on.
     * \param greenAlarmLed is the green led that is turned on when the gas-value is below both thresholds.
     * \param yellowAlarmLed is the yellow led that should be turned on when gas-value is between warning-threshold and danger-threshold.
     * \param redAlarmLed is the red led that should be turned on when gas-value is above danger-threshold.
     * \param warningPlayer is the speaker that should play when gas-value is between warning-threshold and danger-threshold.
     * \param dangerPlayer is the speaker that should play when gas-value is above danger-threshold.
     */
    Alarm(hwlib::pin_out &greenAlarmLed, hwlib::pin_out &yellowAlarmLed, hwlib::pin_out &redAlarmLed,
          Speaker &warningPlayer, Speaker &dangerPlayer):
            greenAlarmLed(greenAlarmLed),
            yellowAlarmLed(yellowAlarmLed),
            redAlarmLed(redAlarmLed),
            warningPlayer(warningPlayer),
            dangerPlayer(dangerPlayer){}

    /**
     * \brief Check if gas value is above the danger-threshold then it will trigger the danger-speaker and red led
     * When the alarm is between the warning-threshold and the danger-threshold then it will trigger the warning-speaker and yellow led
     * When it's below said thresholds the green led will be triggered.
     * \param gasValue the gas value
     */
    void checkGasValue(int gasValue);

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
	void setWarningThreshold(int Threshold);

	/**
	* \brief Sets the threshold of the danger alarm
	* \param dangerThreshold the value to be set
	*/
	void setDangerThreshold(int Threshold);

private:

    /**
     * Alarm threshold set by constructor
     */
    int warningThreshold;
    int dangerThreshold;

	/**
	* The first note to be played
	*/
	int firstNote = 880;

	/**
	* The second note to be played
	*/
	int secondNote = 698;

    /**
     * The pins the alarm is connected to
     */
    hwlib::pin_out &greenAlarmLed;
    hwlib::pin_out &yellowAlarmLed;
    hwlib::pin_out &redAlarmLed;

    /**
     * The players that will make the speaker play sound.
     **/

    Speaker &warningPlayer;
    Speaker &dangerPlayer;

};
