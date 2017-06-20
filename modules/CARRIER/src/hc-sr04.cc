/**
 * \file
 * \brief     Sonar Sensor definition
 * \author    Luke Roovers
 * \copyright Copyright (c) 2017, The R2D2 Team
 * \license   See LICENSE
 */
#include "hc-sr04.hh"

HcSr04::HcSr04( int triggerPin,int echoPin ):
    triggerPin( triggerPin ),
    echoPin( echoPin )
{
    // Set pins
    pinMode (triggerPin, OUTPUT);
    pinMode (echoPin, INPUT);
}

int HcSr04::getDistance(){
    // Send signal to sensor
    digitalWrite ( triggerPin, 1 );
    delayMicroseconds( 10 );
    digitalWrite ( triggerPin, 0 );

    // Keep setting the start time untill Echo is high
    long startTimeUsec = 0;
    while (!digitalRead(echoPin)){
        startTimeUsec = micros();
    }

    // While Echo is high, set end time. When echo goes low again
    // we have the latest result. We're looking for the amount of time
    // the Echo pin was high.
    long endTimeUsec = 0;
    while(digitalRead(echoPin)){
        endTimeUsec = micros();
    }

    // Distance =  Time * speed of sound / 2
    // Micros() gives us microseconds, there are 1 million microseconds
    // in a second, which means we need to divide by that amount to get
    // seconds. We need second because the speed of sound is
    // 340.29 is meter per second. I only divide by 10k to make up
    // for the fact that I want centimeters.
    return (int)((((endTimeUsec - startTimeUsec) / 10000.0f) * 340.29f) / 2);
}
