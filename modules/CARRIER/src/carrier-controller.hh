/**
 * \file
 * \brief     Controls (non-)autonomous actions
 * \author    Remco Ruttenberg
 * \copyright Copyright (c) 2017, The R2D2 Team
 * \license   See LICENSE
 */

#pragma once
#include "motor-controller.hh"
#include "hc-sr04.hh"
#include <chrono>
#include <cmath>
#include <cstdint>

namespace Carrier {

/**
 * \brief The robot's various possible states
 */
enum class CarrierState
{
    Idle,    ///< The robot is idle
    Driving, ///< The robot is driving (forward or backward)
    Turning, ///< The robot is turning (left or right)
    Sensing  ///< The robot is sensing the environment
};

/**
 * \brief Controls (non-)autonomous actions
 * 
 * A statemachine that controls its various states (and transitions)
 */
class CarrierController {
public:
    /**
     * \brief Constructor of CarrierController
     * 
     * \param[in]  motorController  class that can control the carrier motors
     * \param[in]  sonarController  class that can control the sonar sensor
     * \param[in]  distThreshold    the threshold for distance to objects
     * \param[in]  speed            the speed in ???-units
     */
    CarrierController(MotorController &motorController, HcSr04 &sonarSensor,
                      float distThreshold = 0.5f, int speed = 0.1f);

    /**
     * \brief Deconstructor of CarrierController
     * 
     * Stops the motors during destruction of the object
     */
    ~CarrierController();

    /**
     * \brief Moves forward
     * 
     * Moves the robot forward for the given distance
     * \param[in]  distance  the distance in meters
     */
    void forward(float distance);

    /**
     * \brief Moves backward
     * 
     * Moves the robot backward for the given distance
     * \param[in]  distance  the distance in meters
     */
    void backward(float distance);

    /**
     * \brief Rotates left (counter-clockwise)
     * 
     * Rotates the robot left (counter-clockwise) for the given degrees
     * \param[in]  degrees  the degrees to turn
     */
    void left(float degrees);

    /**
     * \brief Rotates right (clockwise)
     * 
     * Rotates the robot right (clockwise) for the given degrees
     * \param[in]  degrees  the degrees to turn
     */
    void right(float degrees);

    /**
     * \brief Sets the speed
     * 
     * \param[in]  speed  the speed in (TODO: figure out which units to use)
     */
    void setSpeed(float speed);

    /**
     * \brief Update tick for the controller
     * 
     * Allows the controller to perform the actions for the current state,
     * during which the controller may change state
     */
    void update();

    /**
     * \brief Stops the robot
     *
     * Stops the robot
     */
    void stop();

    /**
     * \brief Returns the current state the carrier is in
     */
    CarrierState currentState();

    // Distance tracking (using only time)

    /**
     * \brief Calculates time based on distance
     * 
     * Calculates the time needed to travel the given distance
     * NOTE: This simple calculation does not (yet) use acceleration
     * \param dist the distance in meters
     * \returns The time to travel in nanoseconds
     */
    std::chrono::nanoseconds timeUntilDestination(float dist);

    /**
     * \brief Calculates distance based on elapsed time
     * 
     * Calculates the distance traveled during the given elapsed time
     * NOTE: This simple calculation does not (yet) use acceleration
     * \param elapsedTime the elapsed time during travel
     * \returns The distance traveled in meters
     */
    float distanceTraveled(std::chrono::steady_clock::time_point elapsedTime);

private:
    MotorController &motorController;
    HcSr04& sonarSensor;

    /// The distance threshold in meters
    float distThreshold;
    
    /// The speed in ???-units
    int speed;

    /// The current state
    CarrierState state;

    // Distance tracking (using only time)
    /// Start time for measuring and other uses
    std::chrono::steady_clock::time_point startTime;
    /// Target time for driving a fixed distance
    std::chrono::steady_clock::time_point targetTime;
};
} // namespace Carrier
