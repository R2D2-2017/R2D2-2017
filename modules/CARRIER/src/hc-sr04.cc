//
// Created by Luke Roovers on 12-6-2017.
//
#include "hc-sr04.hh"
#include "wiringPi.h"
#include <ctime>
#include <iostream>

hcSr04::hcSr04( int & TriggerPin,int & EchoPin ):
    TriggerPin( TriggerPin ),
    EchoPin( EchoPin )
{}

float hcSr04::get(){
    getDistance();
    return distance;
}

double hcSr04::getDistance(){



    pinMode (TriggerPin, OUTPUT);
    pinMode (EchoPin, INPUT);


    digitalWrite ( TriggerPin, 1 );
    delayMicroseconds( 10 );
    digitalWrite ( TriggerPin, 0 );



    while ( digitalRead(EchoPin)==0);
        ding();


    travelTimeUsec = endTimeUsec - startTimeUsec;
    distanceMeters= 100*((travelTimeUsec/1000000.0)*340.29)/2;

    std::cout<<"print:"<<distanceMeters<<"\n";
    //std::cout<<"print:"<<temp<<"\n";

}

void hcSr04::Timer(){
    startTimeUsec = micros();
    while(digitalRead(EchoPin) == HIGH);
    endTimeUsec = micros();
    }
