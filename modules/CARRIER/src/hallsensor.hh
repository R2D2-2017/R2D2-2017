/**
 * \file
 * \brief     Hall sensor header file
 * \author    Luke Roovers, Jan Halsema
 * \copyright Copyright (c) 2017, The R2D2 Team
 * \license   See LICENSE
 */

#pragma once

#include "wiringPi.h"
#include <atomic>
#include <chrono>
#include <mutex>
#include <thread>

class HallSensor {
private:
    const int hallSensorPin;

    const std::chrono::nanoseconds pollTime;

    std::atomic_uint revelationCount = 0;
    std::atomic_bool running;

    std::thread poller([&]() {
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
    });

public:
    HallSensor(const int hallSensorPin, const std::chrono::nanoseconds pollTime = 2s);
    ~HallSensor();

    int  revelations();
    void reset();
};
