/**
 * \file
 * \brief     The declarations of the class Alarm of GAS-01
 * \author    Jeroen Kok
 * \copyright Copyright (c) 2017, The R2D2 Team
 * \license   See LICENSE
 */

#pragma once

#include "wrap-hwlib.hh"

class Alarm {
public:

	/// \brief Constructor for Alarm
	/// initializes gasValueThreshold and alarmLed
	Alarm(float gasValueThreshold, hwlib::pin_out &alarmLed)
        : alarmLed(alarmLed), gasValueThreshold(gasValueThreshold) {}

    /// \brief Check if gas value is above the threshold then trigger the alarm
	/// Take the gas value and call triggerAlarm() when it's above the
	/// threshold or disableAlarm() when it's below said threshold.
	/// \param gasValue the gas value
	void checkGasValue(float gasValue);
private:

    /// The pin the alarm is connected to
	hwlib::pin_out &alarmLed;

	/// Alarm threshold set by constructor
	float gasValueThreshold;

	/// \brief Turn the alarm on
	void triggerAlarm();
	/// \brief Turn the alarm off
	void disableAlarm();
};
