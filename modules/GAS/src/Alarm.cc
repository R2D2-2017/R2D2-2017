#include Alarm.hh




//PIOB->PIO_OER = 0x01 << 27; turning the pin to an output for the LED. Not sure where it needs to run.



void check_gas_value( int32_t gas_value ) {
	if( gas_value > gas_value_threshold ) {
		trigger_alarm();
	} else {
		disable_alarm();
		is_alarm_enabled = false;
	}
}

void trigger_alarm() {
	if ( is_alarm_enabled == false ) {
//		PIOB->PIO_SODR = 0x01 << 27;
		is_alarm_enabled = true;
	}
}


void disable_alarm() {
	if ( is_alarm_enabled == true ) {
//		PIOB->PIO_CODR = 0x01 << 27;
		is_alarm_enabled = false;
	}
}