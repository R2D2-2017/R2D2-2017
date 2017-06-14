/**
* \file
* \brief     Controls (non-)autonomous actions
* \author    Remco Ruttenberg
* \copyright Copyright (c) 2017, The R2D2 Team
* \license   See LICENSE
*/

#pragma once
//#include "motor.hh"
//#include "sonar.hh"
#include <cstdint>
#include <chrono>
#include <cmath>

namespace Carrier {

    /**
    * \brief The robot's various states
    */
    enum class CarrierState
    {
        Idle,
        Driving,
        Turning,
        Sensing
    };

    /**
    * \brief ...
    * ...
    */
    class CarrierController
    {
    public:
        /**
        * \brief ...
        * ...
        * \param[in] motor ...
        * \param[in] sonar ...
        * \param[in] distThreshold the threshold for distance to objects
        * \param[in] speed the speed in ???-units
        */
        CarrierController(/*Motor & motor, Sonar & sonar, */float distThreshold = 0.5f, float speed = 0.1f);
        /**
        * \brief Shuts down the controller
        */
        ~CarrierController();

        /**
        * \brief Moves forward
        * Moves the robot forward for the given distance
        * \param[in] distance the distance in meters
        */
        void forward(float distance);

        /**
        * \brief Moves backward
        * Moves the robot backward for the given distance
        * \param[in] distance the distance in meters
        */
        void backward(float distance);

        /**
        * \brief Rotates left (counter-clockwise)
        * Rotates the robot left (counter-clockwise) for the given degrees
        * \param[in] degrees the degrees to turn
        */
        void left(float degrees);
        
        /**
        * \brief Rotates right (clockwise)
        * Rotates the robot right (clockwise) for the given degrees
        * \param[in] degrees the degrees to turn
        */
        void right(float degrees);

        /**
        * \brief Sets the speed
        * \param[in] speed the speed in (TODO: figure out which units to use)
        */
        void setSpeed(float speed);

        /**
        * \brief ...
        * ...
        */
        void update();

        /**
        * \brief Stops the robot
        * Stops the robot (immediately?)
        */
        void stop();

        CarrierState currentState();

        // Distance tracking (using only time)

        /**
        * \brief ...
        * Calculates the time needed to travel the given distance
        * NOTE: This simple calculation does not (yet) use acceleration
        * \param dist the distance in meters
        * \return
        */
        std::chrono::nanoseconds timeUntilDestination(float dist);

        /**
        * \brief ...
        * Calculates the distance traveled during the given elapsed time
        * NOTE: This simple calculation does not (yet) use acceleration
        * \param elapsedTime the elapsed time during travel
        * \return ...
        */
        float distanceTraveled(std::chrono::steady_clock::time_point elapsedTime);

    private:
        //Motor & motor;
        //Sonar & sonar;
        /**
        * \brief The distance threshold in meters
        */
        float distThreshold;
        /**
        * \brief The speed in m/s
        */
        float speed;

        CarrierState state;

        // Distance tracking (using only time)
        std::chrono::steady_clock::time_point startTime;
        std::chrono::steady_clock::time_point targetTime;

        void move();
        void rotate();
    };
}
