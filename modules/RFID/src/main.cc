#include <stdio.h>
#include <wiringPi.h>
#inlcude <led-controller.hh>

int main (void)
{
    wiringPiSetup ();
    LedControler();
    blinkLed(0,1000); // wiringPi pin 0 is BCM_GPIO 17. 1000 ms = 1 sec
}
