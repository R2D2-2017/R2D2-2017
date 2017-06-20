/**
 * \file
 * \brief     This is a module for reading the KY-024 Hall Sensor.
 * \author    Luke Roovers, Jan Halsema
 * \copyright Copyright (c) 2017, The R2D2 Team
 * \license   See LICENSE
 */
#include "slit-sensor.hh"

SlitSensor::SlitSensor(const int hallSensorPin, const std::chrono::nanoseconds pollTime)
: hallSensorPin(hallSensorPin),
  pollTime(pollTime),
  pollThread() /* explicitly call default constructor thread first */ {
    pinMode(hallSensorPin, INPUT);
    // finally move thread into place so it doesn't start running when we're not yet fully constructed
    pollThread = std::thread(&SlitSensor::threadMain, this);
}

SlitSensor::~SlitSensor() {
    running = false;
    pollThread.join(); // after joining it should be safe to destruct
}

int SlitSensor::rotations() {
    return rotationCount;
}

void SlitSensor::reset() {
    rotationCount = 0;
}

void SlitSensor::threadMain() {
    bool triggerdFlag = false;
    bool state = 0;
    while (running) {
        state = digitalRead(hallSensorPin);
        if (!triggerdFlag && state) {
            rotationCount++;
            triggerdFlag = true;
        } else if (!state && triggerdFlag) {
            triggerdFlag = false;
        }
        std::this_thread::sleep_for(pollTime);
    }
}
