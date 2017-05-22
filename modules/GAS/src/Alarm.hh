/**
 * \file
 * \brief     The declarations of the alarm functionality of GAS-01
 * \author    Jeroen Kok
 * \copyright Copyright (c) 2017, The R2D2 Team
 * \license   See LICENSE
 */

#pragma once

//#include hwlib.h

/// just a magic number at the moment
int32_t gasValueThreshold = 100;

/// /brief Check if the gass value is above the threshold then trigger the alarm
/// Take the gass value and call trigger_alarm() when it's above the
/// threshold or disable_alarm() when it's below said threshold.
/// @param gas_value the gas value
void checkGasValue(int32_t gasValue);

/// /brief turn the alarm on
void triggerAlarm();

/// turn the alarm off
void disableAlarm();