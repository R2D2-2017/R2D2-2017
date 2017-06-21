/**
 * \file
 * \brief     This is a module for reading the KY-024 Hall Sensor.
 * \author    Luke Roovers, Jan Halsema
 * \copyright Copyright (c) 2017, The R2D2 Team
 * \license   See LICENSE
 */
#include "slit-sensor.hh"

SlitSensor::SlitSensor(const int frontPin, const int backPin, const std::chrono::nanoseconds pollTime)
: frontPin(frontPin),
  backPin(backPin),
  pollTime(pollTime),
  pollThread() /* explicitly call default constructor thread first */ {
    pinMode(frontPin, INPUT);
    pinMode(backPin, INPUT);
    // finally move thread into place so it doesn't start running when we're not yet fully constructed
    pollThread = std::thread(&SlitSensor::threadMain, this);
}

SlitSensor::~SlitSensor() {
    running = false;
    pollThread.join(); // after joining it should be safe to destruct
}

int SlitSensor::rotations() {
    //return rotationCount;
    if(NewRotations<16) {
        return 0;
    }
    return rotationCount = NewRotations;
}

void SlitSensor::reset() {
    rotationCount = 0;
}

void SlitSensor::threadMain() {
    bool waitingForBack = false;
    bool statusFront, statusBack;
    while (running) {
        statusFront = digitalRead(frontPin);
        statusBack  = digitalRead(backPin);
        if (!waitingForBack && statusFront) {
            waitingForBack = true;
        } else if (waitingForBack && statusBack) {
            waitingForBack = false;
            rotationCount++;
        }

        if (statusFront) {
                if(!statusBack){
                    NewRotations++;
                }
            }
        }
        std::this_thread::sleep_for(pollTime);
    }

