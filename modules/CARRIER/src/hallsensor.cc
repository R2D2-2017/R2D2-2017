/**
 * \file
 * \brief     This is a module for reading the KY-024 Hall Sensor.
 * \author    Luke Roovers, Jan Halsema
 * \copyright Copyright (c) 2017, The R2D2 Team
 * \license   See LICENSE
 */
#include "hallsensor.hh"

HallSensor::HallSensor(const int hallSensorPin, const std::chrono::nanoseconds pollTime)
: hallSensorPin(hallSensorPin),
  pollTime(pollTime),
  pollThread() /* explicitly call default constructor thread */ {
    pinMode(hallSensorPin, INPUT);
    // move thread into place so it doesn't start running when we're not yet fully constructed
    pollThread = std::thread(&HallSensor::threadMain, this);
}

HallSensor::~HallSensor() {
    running = false;
    if (pollThread.joinable()) pollThread.join();
}

int HallSensor::rotations() {
    return rotationCount;
}

void HallSensor::reset() {
    rotationCount = 0;
}

void HallSensor::threadMain() {
    bool triggerdFlag = false;
    bool state = 0;
    while (running) {
        state = digitalRead(hallSensorPin);
        if (!triggerdFlag && state) {
            revelationCount++;
            triggerdFlag = true;
        } else if (!state && triggerdFlag) {
            triggerdFlag = false;
        }
        std::this_thread::sleep_for(pollTime);
    }
}
