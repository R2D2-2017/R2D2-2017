//
// Created by Luke Roovers on 16-6-2017.
//

#include "avoidance.hh"


Avoidance::Avoidance(HcSr04 &north, HcSr04 &east, HcSr04 &south, HcSr04 &west, int threshold):
    threshold(threshold)
{
    sensorArray ={north,east,south,west};
}

bool Avoidance::tooClose(sensors arrayIndex) {
   return ( sensorArray[arrayIndex].getDistance() <= threshold );
}
