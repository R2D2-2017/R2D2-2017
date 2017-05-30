#include <sam3x8e.h>
#include "wrap-hwlib.hh" 

#include "alarm.hh"

int main( void ){

	// kill the watchdog
	WDT->WDT_MR = WDT_MR_WDDIS;
    hwlib::wait_ms( 500 );

    auto alarmled = hwlib::target::pin_out( hwlib::target::pins::d51 );
//    auto alarmled = hwlib::target::pin_out( hwlib::target::pins::d49 );
//    auto alarmled = hwlib::target::pin_out( hwlib::target::pins::d47 );
    Alarm test_alarm = Alarm( 50.1f, alarmled);

    int threshold = 50;
    test_alarm.checkGasValue( threshold );

}