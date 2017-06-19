/**
 * \file
 * \brief     Controls (non-)autonomous actions
 * \author    Remco Ruttenberg
 * \author    Bob Thomas
 * \copyright Copyright (c) 2017, The R2D2 Team
 * \license   See LICENSE
 */

#pragma once
#include "motor-controller.hh"
#include "hc-sr04.hh"
#include <chrono>
#include <cmath>
#include <cstdint>
#include "./states/i-carrier-state.hh"
#include "./states/forward-state.hh"
#include "./states/backward-state.hh"
#include "./states/clockwise-state.hh"
#include "./states/counter-clockwise-state.hh"
#include "./states/idle-state.hh"

#include <memory>

namespace Carrier {

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
    CarrierController(MotorController &motorController,
                      HcSr04 &sonarSensor, int speed = 1);

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
     */
    CarrierState currentState();

    int getSpeed();

    MotorController &getMotorController();

    HcSr04 &getSonar();

private:
    /// Controller to send commands to the motors
    MotorController &motorController;

    /// Sonar sensor for object avoidance
    HcSr04 &sonarSensor;

    /// The speed in ???-units
    int speed;

    /// The current motor state
    std::unique_ptr<ICarrierState> state;
};
} // namespace Carrier
