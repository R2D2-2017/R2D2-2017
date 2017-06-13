//
// Created by Luke Roovers on 12-6-2017.
//
#include "hc-sr04.hh"

hcSr04::hcSr04(TriggerPin,EchoPin):
    TriggerPin(TriggerPin),
    EchoPin(EchoPin)
{}

float hcSr04::get(){
    return distance;
}

void hcSr04::getDistance(){
    pinMode (TriggerPin, OUTPUT);
    pinMode (EchoPin, INPUT);


}