/**
 * \file
 * \author    Matthijs Vos
 * \author    David Driessen
 * \copyright Copyright (c) 2017, The R2D2 Team
 * \license   See LICENSE
 */
#include "i2c.hh"

constexpr int SERVO_MIN = 4095 / 100 * 4;
constexpr int SERVO_MAX = 4095 / 100 * 14;

constexpr auto MODE1          = 0x00;       ///< Mode register 1
constexpr auto MODE2          = 0x01;       ///< Mode register 2
constexpr auto SUBADR1        = 0x02;       ///< I2C-bus subaddress 1
constexpr auto SUBADR2        = 0x03;       ///< I2C-bus subaddress 2
constexpr auto SUBADR3        = 0x04;       ///< I2C-bus subaddress 3
constexpr auto ALLCALLADR     = 0x05;       ///< LED All Call I2C-bus address
constexpr auto LED0           = 0x06;       ///< LED0 start register
constexpr auto LED0_ON_L      = 0x06;       ///< LED0 output and brightness control byte 0
constexpr auto LED0_ON_H      = 0x07;       ///< LED0 output and brightness control byte 1
constexpr auto LED0_OFF_L     = 0x08;       ///< LED0 output and brightness control byte 2
constexpr auto LED0_OFF_H     = 0x09;       ///< LED0 output and brightness control byte 3
constexpr auto LED_MULTIPLIER =    4;       ///< For the other 15 channels
constexpr auto ALLLED_ON_L    = 0xFA;       ///< load all the LEDn_ON registers, byte 0 (turn 0-7 channels on)
constexpr auto ALLLED_ON_H    = 0xFB;       ///< load all the LEDn_ON registers, byte 1 (turn 8-15 channels on)
constexpr auto ALLLED_OFF_L   = 0xFC;       ///< load all the LEDn_OFF registers, byte 0 (turn 0-7 channels off)
constexpr auto ALLLED_OFF_H   = 0xFD;       ///< load all the LEDn_OFF registers, byte 1 (turn 8-15 channels off)
constexpr auto PRE_SCALE      = 0xFE;       ///< prescaler for output frequency
constexpr auto CLOCK_FREQ     = 25000000.0; ///< 25MHz default osc clock


void I2C::reset(void) {
    sendCommand(0x00, 0x00);//Normal mode
    sendCommand(0x01, 0x04);//Totem pole
}

void I2C::setPWMFreq(int freq) {
    uint8_t prescale_val = (CLOCK_FREQ / 4096 / freq) - 1;
    sendCommand(MODE1, 0x10);//sleep
    sendCommand(PRE_SCALE, prescale_val);//multiplyer for PWM frequency
    sendCommand(MODE1, 0x80);//restart
    sendCommand(MODE2, 0x04);//totem pole
}

void I2C::setPWM(uint8_t led, int value) {
    setPWM(led, 0, value);
}

void I2C::setPWM(uint8_t led, int onValue, int offValue) {
    sendCommand(LED0_ON_L  + LED_MULTIPLIER * (led - 1), onValue  & 0xFF);
    sendCommand(LED0_ON_H  + LED_MULTIPLIER * (led - 1), onValue  >> 8);
    sendCommand(LED0_OFF_L + LED_MULTIPLIER * (led - 1), offValue & 0xFF);
    sendCommand(LED0_OFF_H + LED_MULTIPLIER * (led - 1), offValue >> 8);
}

void I2C::moveServoTo(uint8_t servo, int degrees) {
    setPWM(servo, SERVO_MIN + ((SERVO_MAX - SERVO_MIN) / 180) * degrees);
}

void I2C::sendCommand(uint8_t adress, uint8_t value) {

    // Currently fixed value because this is the only slave at this iteration
    uint8_t slaveAdress = 0x40;

    uint8_t command[2] = {adress, value};
    // Writes the command to the slaveAdress, pointing to a certain register and sets a byte there
    i2cBus.write(slaveAdress, command, 2);
}
