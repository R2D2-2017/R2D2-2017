/**
 * \file
 * \brief     Hall sensor header file
 * \author    Luke Roovers, Jan Halsema
 * \copyright Copyright (c) 2017, The R2D2 Team
 * \license   See LICENSE
 */

#pragma once

#include <atomic>
#include <chrono>
#include <mutex>
#include <thread>

#include <wiringPi.h>

using namespace std::literals;

class HallSensor {
private:
    const int hallSensorPin;

    const std::chrono::nanoseconds pollTime;

    std::atomic_uint rotationCount{ 0 };

    std::thread pollThread;
    bool running = true;
    void threadMain();

public:
    HallSensor(const int hallSensorPin, const std::chrono::nanoseconds pollTime = 2s);
    ~HallSensor();

    int  rotations();
    void reset();
};
