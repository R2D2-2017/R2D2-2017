/**
 * \file
 * \brief     The declarations of the alarm functionality of GAS-01
 * \author    Jeroen Kok
 * \copyright Copyright (c) 2017, The R2D2 Team
 * \license   See LICENSE
 */

#pragma once

#include "wrap-hwlib.hh" 

/// /brief Check if the gass value is above the threshold then trigger the alarm
/// Take the gass value and call triggerAlarm() when it's above the
/// threshold or disableAlarm() when it's below said threshold.
/// @param gasValue the gas value
void checkGasValue(float gasValue);

/// /brief turn the alarm on
void triggerAlarm();

/// turn the alarm off
void disableAlarm();