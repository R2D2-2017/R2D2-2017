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
#include "hc-sr04.hh"
#include "motor-controller.hh"
#include "serial-com.hh"
#include "./states/i-carrier-state.hh"
#include "./states/forward-state.hh"
#include "./states/backward-state.hh"
#include "./states/clockwise-state.hh"
#include "./states/counter-clockwise-state.hh"
#include "./states/idle-state.hh"
#include "./states/auto-state.hh"
#include "./states/avoidance-state.hh"

namespace Carrier {

/**
 * \brief Directions for the different distance sensors
 */
enum SonarDirection {
    North = 0,
    East,
    South,
    West,
    All
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
    
    /// Controller for serial communication
    SerialCom &serialCom;
    
    /// A vector of four sonar sensors, used for object avoidance
    std::vector<HcSr04> &sonarSensors;

    /// The speed in ???-units
    int speed;

    /// The current motor state
    std::unique_ptr<ICarrierState> state;

public:
    /**
     * \brief Constructor of CarrierController
     *
     * The sonar vector must be filled as follows: North, East, South, West.
     *
     * \param[in]  motorController  a reference to the motro controller
     * \param[in]  serialCom        a reference to the serial com
     * \param[in]  sonarSensors     a vector containing the four sonar sensors
     * \param[in]  speed            the speed in ???-units
     */
    CarrierController(MotorController &motorController,
                      SerialCom &serialCom,
                      std::vector<HcSr04> &sonarSensors,
                      int speed = 1);

    /**
     * \brief Sets the speed
     *
     * \param[in]  speed  the speed used for the motors (number between 0-127)
     */
    void setSpeed(int speed);

    /**
     * \brief Update tick for the controller
     *
     * Allows the controller to perform the actions for the current state,
     * during which the controller may change state.
     */
    void update();

    /**
     * \brief Sets the state of the robot based on the given CarrierState
     *
     * \param[in]  state  The state the robot is going to transition to
     */
    void setState(CarrierState state);

    /**
     * \brief Returns the current state the carrier is in
     *
     * \return An enum containing the current state
     */
    CarrierState currentState();

    /**
     * \brief Returns the current speed
     *
     * \returns An integer with the current speed value
     */
    int getSpeed();

    /**
     * \brief Returns a reference of the motorController
     */
    MotorController &getMotorController();

    /**
     * \brief Returns a reference of the serialCom
     */
    SerialCom &getSerialCom();

    /**
     * \brief Returns selected sensor reading in centimeters
     *
     * Can be used to read the four sensors individually or use
     * SonarDirection::All to read out all of them at once.
     *
     * A single direction returns a vector with one element.
     * When reading all sensors, a vector of four elements is returned.
     * The vector is filled as follows: North, East, South, West.
     *
     * \param[in]  direction  selection from the enum to select what sensor to read
     * \return A vector of read sensor distance values
     */
    std::vector<int> getSonarValue(SonarDirection direction);
};
} // namespace Carrier
