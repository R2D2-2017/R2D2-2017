/**
 * \file
 * \brief     Sonar Sensor header file
 * \author    Luke Roovers
 * \copyright Copyright (c) 2017, The R2D2 Team
 * \license   See LICENSE
 */

#pragma once
#include <wiringPi.h>

class HcSr04 {
private:
    int     TriggerPin;
    int     EchoPin;
    double  distanceInCm = 0;
    volatile long endTimeUsec = 0;
    volatile long startTimeUsec = 0;
public:
    HcSr04(int & TriggerPin,int & EchoPin);
    /**
     * \brief Get distance in CM
     *
     * \return Double - Centimeters
     */
    double  getDistance();
};
