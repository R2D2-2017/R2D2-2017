/**
 * \file
 * \author    Matthijs Vos
 * \copyright Copyright (c) 2017, The R2D2 Team
 * \license   See LICENSE
 */

#pragma once

#include "wrap-hwlib.hh"

#define MODE1 0x00            //Mode  register  1
#define MODE2 0x01            //Mode  register  2
#define SUBADR1 0x02          //I2C-bus subaddress 1
#define SUBADR2 0x03          //I2C-bus subaddress 2
#define SUBADR3 0x04          //I2C-bus subaddress 3
#define ALLCALLADR 0x05       //LED All Call I2C-bus address
#define LED0 0x6              //LED0 start register
#define LED0_ON_L 0x6         //LED0 output and brightness control byte 0
#define LED0_ON_H 0x7         //LED0 output and brightness control byte 1
#define LED0_OFF_L 0x8        //LED0 output and brightness control byte 2
#define LED0_OFF_H 0x9        //LED0 output and brightness control byte 3
#define LED_MULTIPLYER 4      // For the other 15 channels
#define ALLLED_ON_L 0xFA      //load all the LEDn_ON registers, byte 0 (turn 0-7 channels on)
#define ALLLED_ON_H 0xFB      //load all the LEDn_ON registers, byte 1 (turn 8-15 channels on)
#define ALLLED_OFF_L 0xFC     //load all the LEDn_OFF registers, byte 0 (turn 0-7 channels off)
#define ALLLED_OFF_H 0xFD     //load all the LEDn_OFF registers, byte 1 (turn 8-15 channels off)
#define PRE_SCALE 0xFE        //prescaler for output frequency
#define CLOCK_FREQ 25000000.0 //25MHz default osc clock

/**
 * \brief The i2c class to control a pcA9685 chip
 */
class I2C {
    hwlib::i2c_bus &i2c_bus;

    /**
     * \brief Sends command tot the pcA9685 chip
     * \param[in]  registerAdress  The address of the target register
     * \param[in]  registerValues  The value to send to the register
     */
    void sendCommand(uint8_t address, uint8_t value);
public:
    I2C(hwlib::i2c_bus &i2c_bus);

    /**
     * \brief Resets the pcA9685 chip
     */
    void reset(void);

    /*!
     * \brief  Set PWM duty cycle
     * \param[in] The frequency to set the PWM outputs to. value 40-25000000
     */
    void setPWMFreq(int);

    /*!
     * \brief  Set PWM duty cycle
     * \param[in] led channel (1-16) to set PWM value for
     * \param[in] The on count of the duty cycle for the PWM. value 0-4095
     * \param[in] The off count of the duty cycle for the PWM. value 0-4095
     */
    void setPWM(uint8_t, int, int);

    /*!
     * \brief  Set PWM duty cycle
     * \param[in] led channel (1-16) to set PWM value for
     * \param[in] The percentage of the duty cycle for the PWM. value 0-100
     */
    void setPWM(uint8_t, int);

    /*!
     * \brief  Set PWM duty cycle for a servo moto
     * \param[in] Servo channel (1-16) to set PWM value for
     * \param[in] The degrees to tern the servo motor to. value 0-180
     */
    void moveServoTo(uint8_t servo, int degrees);
};
