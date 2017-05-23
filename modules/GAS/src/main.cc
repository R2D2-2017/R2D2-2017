#include <sam3x8e.h>
#include "wrap-hwlib.hh" 

#include "Alarm.hh"

int main( void ){

	// kill the watchdog
	WDT->WDT_MR = WDT_MR_WDDIS;
    hwlib::wait_ms( 500 );

    int thing = 50;
    checkGasValue( thing );

}