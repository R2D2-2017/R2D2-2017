/**
 * \file
 * \brief     Controller to control Qik2s12v10
 * \author    Jip Galema
 * \copyright Copyright (c) 2017, The R2D2 Team
 * \license   See LICENSE
 */

#pragma once

#include "motor.hh"

/**
 * \brief Movement commands to control the motors
 */
enum MovementControls : uint8_t {
    ForwardMotorOne = 0x08,  ///< Moves motor one forward
    ForwardMotorTwo = 0x0C,  ///< Moves motor two forward
    BackwardMotorOne = 0X0A, ///< Moves motor one backward
    BackwardMotorTwo = 0x0E  ///< Moves motor two backward
};

/**
 * \brief Controls both rosbee motors
 * 
 * Controls the rosbee motors by sending specific rosbee motor control commands
 */
class MotorController {
private:
    /// The left motor
    Motor leftMotor;

    /// The right motor
    Motor rightMotor;

public:
    /**
     * \brief Constructor for MotorController class
     * 
     * \param[in]  portName  serial path to serial connection port
     * \param[in]  baud      baudrate you want to open the serial connection on
     */
    MotorController(std::string portName, int baud);

    /**
     * \brief sends command to Qik2s12v10 to ride forward at given speed
     * 
     * \param[in]  speed  the motors will be turning this number has to be
     * between 0 and 127
     */
    void forward(int speed);

    /**
     * \brief sends command to Qik2s12v10 to ride backward at given speed
     * 
     * \param[in]  speed  the motors will be turning this number has to be
     * between 0 and 127
     */
    void backward(int speed);

    /**
     * \brief sends command to Qik2s12v10 to stop left motor and turn
     * right motor at given speed, resulting in the vehicle turning left
     * 
     * \param[in]  speed  the motors will be turning this number has to be
     * between 0 and 127
     */
    void left(int speed);

    /**
     * \brief sends command to Qik2s12v10 to stop right motor and turn
     * left motor at given speed, resulting in the vehicle turning right
     * 
     * \param[in]  speed  the motors will be turning this number has to be
     * between 0 and 127
     */
    void right(int speed);

    /**
     * \brief sends command to Qik2s12v10 to stop both motors
     */
    void stop();
};
