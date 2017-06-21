/**
 * \file
 * \author    Matthijs Vos
 * \author    David Driessen
 * \copyright Copyright (c) 2017, The R2D2 Team
 * \license   See LICENSE
 */
#include "i2c.hh"

I2C::I2C(hwlib::i2c_bus &i2c_bus) : i2c_bus(i2c_bus) {
}

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
    sendCommand(LED0_ON_L + LED_MULTIPLYER * (led - 1), onValue & 0xFF);
    sendCommand(LED0_ON_H + LED_MULTIPLYER * (led - 1), onValue >> 8);
    sendCommand(LED0_OFF_L + LED_MULTIPLYER * (led - 1), offValue & 0xFF);
    sendCommand(LED0_OFF_H + LED_MULTIPLYER * (led - 1), offValue >> 8);


}

void I2C::moveServoTo(uint8_t servo, int degrees) {
    static const int min = 4095 / 100 * 4;
    static const int max = 4095 / 100 * 14;

    setPWM(servo, min + ((max - min) / 180) * degrees);
}

void I2C::sendCommand(uint8_t adress, uint8_t value) {

    // Currently fixed value because this is the only slave at this iteration
    uint8_t slaveAdress = 0x40;

    const uint8_t command[2] = {adress, value};
    // Writes the command to the slaveAdress, pointing to a certain register and sets a byte there
    i2c_bus.write(slaveAdress, command, 2);
}
