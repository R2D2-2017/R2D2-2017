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

using namespace std::literals; // for the std::chrono literals

/**
 * Hallsensor Class, counts how often the sensor has been activated since the last reset
 */
class HallSensor {
private:
    const int hallSensorPin;

    const std::chrono::nanoseconds pollTime;

    std::atomic_uint rotationCount{ 0 };

    std::thread pollThread;
    bool running = true;
    void threadMain();

public:
    /**
     * Constructor
     * \param  hallSensorPin[in]  pin the hallsensor is connected to
     * \param  pollTime[in]       how often the thread polls the sensor
     */
    HallSensor(const int hallSensorPin, const std::chrono::nanoseconds pollTime = 2s);
    ~HallSensor();

    /**
     * Returns rotations since last reset
     */
    int  rotations();
    /**
     * Resets the rotation count
     */
    void reset();
};
