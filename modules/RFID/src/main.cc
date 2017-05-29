#include <stdio.h>
#include <wiringPi.h>
#inlcude <LedController.hh>

int main (void)
{
    wiringPiSetup ();
    blinkLed(0,1000); // wiringPi pin 0 is BCM_GPIO 17. 1000 ms = 1 sec
}
