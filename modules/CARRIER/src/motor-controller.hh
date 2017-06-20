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
 * \brief Serial communication with wiring pi for the Qik2s12v10
 *
 * Class that lets user control motors connected through Qik2s12v10 and
 * Raspberry Pi serial port
 */
enum MovementControls : char {
    forwardMotorOne = 0x08,
    forwardMotorTwo = 0x0C,
    backwardMotorOne = 0X0A,
    backwardMotorTwo = 0x0E
};

/**
 * \brief class to control the rosbee motors
 * 
 * This class controls the motor class by sending specific rosbee motor control commands
 */
class MotorController {
private:
    /// left Motor on controller
    Motor leftMotor;
    /// right Motor on controller
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
