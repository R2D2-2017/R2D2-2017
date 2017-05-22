#pragma once

//#include hwlib.h

// Code standard not followed because llvm.com couldn't be reached.

//! a boolean
bool is_alarm_enabled = false;

//! just a magic number at the moment
int32_t gas_value_threshold = 100;

//! /brief take the gass value and see if it's above the threshold
//! Take the gass value and call trigger_alarm() when it's above the threshold or disable_alarm() when it's below said threshold
//! @param gas_value the gas value
void check_gas_value( int32_t gas_value );

//! /brief turn the alarm on
//! Only triggers the alarm once
void trigger_alarm();

//! turn the alarm off
//! Only disables the alarm once
void disable_alarm();