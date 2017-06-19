//
// Created by Luke Roovers on 16-6-2017.
//

#pragma once

#include "hc-sr04.hh"
#include "motor-controller.hh"

enum sensors{
    north = 0, east , south ,west
};

enum situations{
    block = 0,
    cornerLeft,
    cornerRight,
    canyon,
    deadEnd,
    wall,
};

class Avoidance{
private:
    int threshold;
    HcSr04 sensorArray[];
public:
    Avoidance(HcSr04 &north, HcSr04 &east, HcSr04 &south, HcSr04 &west, int threshold);

    bool tooClose(sensors arrayIndex);


};

