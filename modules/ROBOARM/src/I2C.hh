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
#define SUBADR1 0x02        //I2C-bus subaddress 1
#define SUBADR2 0x03        //I2C-bus subaddress 2
#define SUBADR3 0x04        //I2C-bus subaddress 3
#define ALLCALLADR 0x05     //LED All Call I2C-bus address
#define LED0 0x6            //LED0 start register
#define LED0_ON_L 0x6        //LED0 output and brightness control byte 0
#define LED0_ON_H 0x7        //LED0 output and brightness control byte 1
#define LED0_OFF_L 0x8        //LED0 output and brightness control byte 2
#define LED0_OFF_H 0x9        //LED0 output and brightness control byte 3
#define LED_MULTIPLYER 4    // For the other 15 channels
#define ALLLED_ON_L 0xFA    //load all the LEDn_ON registers, byte 0 (turn 0-7 channels on)
#define ALLLED_ON_H 0xFB    //load all the LEDn_ON registers, byte 1 (turn 8-15 channels on)
#define ALLLED_OFF_L 0xFC    //load all the LEDn_OFF registers, byte 0 (turn 0-7 channels off)
#define ALLLED_OFF_H 0xFD    //load all the LEDn_OFF registers, byte 1 (turn 8-15 channels off)
#define PRE_SCALE 0xFE        //prescaler for output frequency
#define CLOCK_FREQ 25000000.0 //25MHz default osc clock

class I2C {
public:
    I2C(hwlib::i2c_bus &i2c_bus);

    // virtual ~I2C();
    void setPWMFreq(int);

    void setPWM(uint8_t, int, int);

    void setPWM(uint8_t, int);

    void moveServoTo(uint8_t servo, int degrease);

    int getPWM(uint8_t);

    hwlib::i2c_bus &i2c_bus;
    /**
    * Size of the list that is always set to 2, commands are always 2 bytes.
    */
    static const int size = 2;

    uint8_t slaveAdress;


    void reset(void);

    /**
    * Runs a small demo to make a led blink
    */
    void runDemo();

    /**
    * sends command tothe slave
    */
    void sendCommand(uint8_t registerAdress, uint8_t registerValues);

};
