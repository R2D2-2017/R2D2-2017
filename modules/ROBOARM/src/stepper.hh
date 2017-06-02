/**
 * \file
 * \brief     Stepper motor interface (dvr8225)
 * \author    Bob Thomas
 * \author    Remco Ruttenberg
 * \copyright Copyright (c) 2017, The R2D2 Team
 * \license   See LICENSE
 */
#pragma once

#include "wrap-hwlib.hh"

//\brief Simple interface to control a stepper motor
class Stepper {
private:
    //Pin that is used for the clockwise or counterclockwise direction
    hwlib::target::pin_out &dir_pin;
    //Pin that is used to control the step of the stepper motor
    hwlib::target::pin_out &stp_pin;

    // The minimum pulse width in microseconds
    long minPulseWidth;

    // Last step time in microseconds
    unsigned long lastStepTime;

    // The current position in steps
    // Positive for clockwise, negative for counterclockwise
    int currentPosition;

    // Target position
    // Positive for clockwise, negative for counterclockwise
    long targetPosition;

    // Interval between steps in microseconds
    unsigned long stepIntervalTime;

    // The current direction
    bool clockwise;

    
    // The current speed in steps per second
    float speed;

    // The maximum speed in steps per second
    float maxSpeed;

    // The acceleration in steps per second
    float acceleration;

    // Used in calculating the speed:
    // The number of steps taken
    long stepsTaken;
    // First step time in microseconds
    float firstStepTime;
    // Previous step time in microseconds
    float prevStepTime;
    // Minimal step time based on the maximum speed
    float minStepTime;

    void calculateSpeed();

public:
    //Constructor for the stepper motor
    //\param dir_pin pin that is used for the clockwise or counterclockwise direction
    //\param stp_pin pin that is used to control the step of the stepper motor
    Stepper(hwlib::target::pin_out &dir_pin, hwlib::target::pin_out &stp_pin);

    // Sets the target to move to
    // \param amount the number of steps to take
    // \param clockwise the direction to move to
    void setTarget(int amount, bool clockwise);
    
    // Let the motor take a single step
    void step();

    // Takes a single step when the motor should move
    void run();

    // Resets the position to zero
    void resetPosition();

    // The remaining distance to go
    // \return the remaining distance in steps
    long remainingDistance();

    // Indicates if the motor is in motion
    // \return true if in motion, otherwise false
    bool inMotion();

    // Sets the acceleration
    // \param acceleration the acceleration in steps per second
    void setAcceleration(float acceleration);

    // Sets the maximum speed
    // \param speed the maximum speed in steps per second
    void setMaxSpeed(float speed);
};
