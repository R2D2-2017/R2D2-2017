/**
 * \file
 * \brief     This is a module for reading the KY-024 Hall Sensor.
 * \author    Luke Roovers, Jan Halsema
 * \copyright Copyright (c) 2017, The R2D2 Team
 * \license   See LICENSE
 */
#include "hallsensor.hh"


HallSensor::HallSensor(const int hallSensorPin, const std::chrono::nanoseconds pollTime)
: hallSensorPin(hallSensorPin), pollTime(pollTime) {
    pinMode(hallSensorPin, INPUT);
}

HallSensor::~HallSensor() {
    running = false;
    poller.join();
}

int revelations() {
    return revelationCount;
}

void reset() {
    revelationCount = 0;
}
