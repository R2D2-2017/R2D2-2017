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
#include <thread>
#include <wiringPi.h>

using namespace std::literals; // for the std::chrono literals

/**
 * \brief Counts amount of hall sensor activations since the last resest
 */
class HallSensor {
private:
    /// The hall sensor pin
    const int hallSensorPin;

    /// The time in nanoseconds to poll the sensor
    const std::chrono::nanoseconds pollTime;

    /// The number of rotations since the last reset
    std::atomic_uint rotationCount{ 0 };

    /// The thread that polls the sensor
    std::thread pollThread;

    /// Flag to indicate running status
    bool running = true;

    /// Main function for the thread to run
    void threadMain();

public:
    /**
     * \brief Constructor for the HallSensor class
     *
     * \param  hallSensorPin[in]  pin the hallsensor is connected to
     * \param  pollTime[in]       how often the thread polls the sensor
     */
    HallSensor(const int hallSensorPin, const std::chrono::nanoseconds pollTime = 2s);

    /**
     * \brief Deconstructor of the HallSensor class
     */
    ~HallSensor();

    /**
     * \brief Returns the number of rotations since the last reset
     */
    int  rotations();

    /**
     * \brief Resets the rotation count
     */
    void reset();
};
