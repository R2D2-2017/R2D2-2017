/**
 * \file
 * \brief     I2C controller class file
 * \author    Matthijs Vos
 * \copyright Copyright (c) 2017, The R2D2 Team
 * \license   See LICENSE
 */
#pragma once

#include "wrap-hwlib.hh"

/**
 * \brief The i2c class to control a pcA9685 chip
 */
class I2C {
    hwlib::i2c_bus &i2cBus;

    /**
     * \brief Sends command tot the pcA9685 chip
     * \param[in] address The address of the target register
     * \param[in] values The value to send to the register
     */
    void sendCommand(uint8_t address, uint8_t value);
public:
    I2C(hwlib::i2c_bus &i2cBus)
        : i2cBus(i2cBus)
    { }

    /**
     * \brief Resets the pcA9685 chip
     */
    void reset(void);

    /**
     * \brief Set PWM duty cycle
     * \param[in] freq The frequency to set the PWM outputs to. value 40-25000000
     */
    void setPWMFreq(int freq);

    /**
     * \brief Set PWM duty cycle
     * \param[in] led Led channel (1-16) to set PWM value for
     * \param[in] onValue The on count of the duty cycle for the PWM. value 0-4095
     * \param[in] offValue The off count of the duty cycle for the PWM. value 0-4095
     */
    void setPWM(uint8_t led, int onValue, int offValue);

    /**
     * \brief Set PWM duty cycle
     * \param[in] led Led channel (1-16) to set PWM value for
     * \param[in] value The percentage of the duty cycle for the PWM. value 0-100
     */
    void setPWM(uint8_t led, int value);

    /**
     * \brief Set PWM duty cycle for a servo moto
     * \param[in] servo Servo channel (1-16) to set PWM value for
     * \param[in] degrees The degrees to tern the servo motor to. value 0-180
     */
    void moveServoTo(uint8_t servo, int degrees);
};
