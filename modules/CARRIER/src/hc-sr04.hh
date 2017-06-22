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
    /// Pin used to trigger the sonar sensor
    int triggerPin;

    /// Pin used to determine the echo time
    int echoPin;

public:
    /**
     * \brief Constructor for the HcSr04 class
     *
     * \param[in]  triggerPin  the pin used to trigger the sonar sensor
     * \param[in]  echoPin     the pin used to determine the echo time
     */
    HcSr04(int triggerPin, int echoPin);

    /**
     * \brief Gets the distance in centimeters
     *
     * \return The measured distance in centimeters
     */
    int  getDistance();
};
