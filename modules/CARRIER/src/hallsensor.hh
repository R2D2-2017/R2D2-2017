/**
 * \file
 * \brief     Sonar Sensor header file
 * \author    Luke Roovers
 * \copyright Copyright (c) 2017, The R2D2 Team
 * \license   See LICENSE
 */

#pragma once
#include <wiringPi.h>

class HallSensor {
private:
    int     hallSensorPin;
    bool    Value = 0;
public:
    HallSensor(int & hallSensorPin);
    /**
     * \brief Function to get the value of the hall sensor
     *
     * \return bool - 1 is on, 0 is off. Sad funtion is sad.
     */
    bool get();
};
