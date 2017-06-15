/**
 * \file
 * \brief     Sonar Sensor definition
 * \author    Luke Roovers
 * \copyright Copyright (c) 2017, The R2D2 Team
 * \license   See LICENSE
 */
#include "hc-sr04.hh"
#include "wiringPi.h"


HcSr04::HcSr04( int & TriggerPin,int & EchoPin ):
    TriggerPin( TriggerPin ),
    EchoPin( EchoPin )
{}



double HcSr04::getDistance(){
    // set pins
    pinMode (TriggerPin, OUTPUT);
    pinMode (EchoPin, INPUT);
    // Send signal to sensor
    digitalWrite ( TriggerPin, 1 );
    delayMicroseconds( 10 );
    digitalWrite ( TriggerPin, 0 );
    //Keep setting the start time untill Echo is high
    while (!digitalRead(EchoPin)){
        startTimeUsec = micros();
    }
    // While Echo is high, set end time. When echo goes low again
    // we have the latest result. We're looking for the amount of time
    // the Echo pin was high. 
    while(digitalRead(EchoPin)){
        endTimeUsec = micros();
    }
    
    // Distance =  Time * speed of sound / 2 
    // Micros() gives us microseconds, there are 1 million microseconds
    // in a second, which means we need to divide by that amount to get
    // seconds. We need second because the speed of sound is 
    // 340.29 is meter per second. I only divide by 10k to make up
    // for the fact that I want centimeters. 
    distanceInCm = (((endTimeUsec - startTimeUsec)/10000.0)*340.29)/2;

    return distanceInCm;

}

