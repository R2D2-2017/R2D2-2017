/**
 * \file
 * \brief     Controls (non-)autonomous actions
 * \author    Remco Ruttenberg
 * \author    Bob Thomas
 * \copyright Copyright (c) 2017, The R2D2 Team
 * \license   See LICENSE
 */

#pragma once

#include <memory> // Used for smart pointers
#include <vector>
#include "motor-controller.hh"
#include "hc-sr04.hh"
#include "./states/i-carrier-state.hh"
#include "./states/forward-state.hh"
#include "./states/backward-state.hh"
#include "./states/clockwise-state.hh"
#include "./states/counter-clockwise-state.hh"
#include "./states/idle-state.hh"

namespace Carrier {

/**
 * \brief enum for the different distance sensors
 */
enum SonarDirections {
    North = 0,
    East,
    South,
    West,
    All,
};

/**
 * \brief Controls (non-)autonomous actions
 *
 * A statemachine that controls its various states (and transitions)
 */
class CarrierController {
private:
    /// Controller to send commands to the motors
    MotorController &motorController;

    /// Sonar sensor for object avoidance
    std::vector<HcSr04> &sonarSensors;

    /// The speed in ???-units
    int speed;

    /// The current motor state
    std::unique_ptr<ICarrierState> state;

public:
    /**
     * \brief Constructor of CarrierController
     *
     * \param[in]  motorController  class that can control the carrier motors
     * \param[in]  sonarController  class that can control the sonar sensor
     * \param[in]  distThreshold    the threshold for distance to objects
     * \param[in]  speed            the speed in ???-units
     */
    CarrierController(MotorController &motorController,
                      std::vector<HcSr04>& sonarSensors, int speed = 1);

    /**
     * \brief Sets the speed
     *
     * \param[in]  speed  the speed in (TODO: figure out which units to use)
     */
    void setSpeed(int speed);

    /**
     * \brief Update tick for the controller
     *
     * Allows the controller to perform the actions for the current state,
     * during which the controller may change state
     */
    void update();

    /**
     * \brief Sets the state of the robot based on the Given CarrierState
     * \param[in] state The state the robot is going to be set in
     */
    void setState(CarrierState state);

    /**
     * \brief Returns the current state the carrier is in
     * 
     * \return an enum containing the current state
     */
    CarrierState currentState();

    /**
     * \brief Returns the current speed
     * 
     * \returns integer with current speed value
     */
    int getSpeed();

    /**
     * \brief Returns a reference of the motorController
     */
    MotorController &getMotorController();

    /**
     * \brief Returns selected sensor reading in cm
     * 
     * \param[in] direction selection from the enum to select what sensor to read
     * Can be use to read the 4 sensor individually or use the All enum to read out all at once
     * \return Vector of read sensor values
     */
    std::vector<int> getSonarValue(SonarDirections direction);
};
} // namespace Carrier
