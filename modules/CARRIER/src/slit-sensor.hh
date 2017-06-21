/**
 * \file
 * \brief     Slit sensor header file
 * \author    Jan Halsema
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
 * Slitsensor Class, counts how often the sensor has been activated since the last reset
 */
class SlitSensor {
private:
    const int frontPin;
    const int backPin;

    const std::chrono::nanoseconds pollTime;

    std::atomic_uint rotationCount{ 0 };
    int NewRotations = 0 ;

    std::thread pollThread;
    bool running = true;
    void threadMain();

public:
    /**
     * Constructor
     * \param  frontPin[in]  front pin the slitsensor is connected to
     * \param  backPin[in]   back pin the slitsensor is connected to
     * \param  pollTime[in]  how often the thread polls the sensor
     */
    SlitSensor(const int frontPin, const int backPin, const std::chrono::nanoseconds pollTime = 2s);
    ~SlitSensor();

    /**
     * Returns rotations since last reset
     */
    int  rotations();
    /**
     * Resets the rotation count
     */
    void reset();
};
