/**
 * \file
 * \author    Other author names missing due to previously missing file header
 * \author    Chris Smeele
 * \copyright Copyright (c) 2017, The R2D2 Team
 * \license   See LICENSE
 */
#include "ky101.hh"
#include "parser.hh"
#include "robot-arm.hh"
#include "stepper.hh"
#include "wrap-hwlib.hh"
#include "I2C.hh"


int main() {
    hwlib::cout << "hallo\r\n";
    WDT->WDT_MR = WDT_MR_WDDIS;

    auto sclPin = hwlib::target::pin_oc(hwlib::target::pins::d21);
    auto sdaPin = hwlib::target::pin_oc(hwlib::target::pins::d20);
    hwlib::i2c_bus_bit_banged_scl_sda i2c_bus(sclPin,sdaPin);

    auto ky101Pin = hwlib::target::pin_in(hwlib::target::pins::d14);

    auto ENX = hwlib::target::pin_out(2, 6); //d38
    auto stepX = hwlib::target::pin_out(hwlib::target::pins::a0);
    auto dirX = hwlib::target::pin_out(hwlib::target::pins::a1);
    auto ENY = hwlib::target::pin_out(hwlib::target::pins::a2);
    auto stepY = hwlib::target::pin_out(hwlib::target::pins::a6);
    auto dirY = hwlib::target::pin_out(hwlib::target::pins::a7);

    auto ENZ = hwlib::target::pin_out(hwlib::target::pins::a8);
    auto stepZ = hwlib::target::pin_out(hwlib::target::pins::d46);
    auto dirZ = hwlib::target::pin_out(hwlib::target::pins::d48);

    auto xLimitSwitch = hwlib::target::pin_in(hwlib::target::pins::d3);
    auto yLimitSwitch = hwlib::target::pin_in(hwlib::target::pins::d2);

    Ky101 ky101(ky101Pin);
    Stepper x(dirX, stepX, ENX);
    Stepper y(dirY, stepY, ENY);
    Stepper z(dirZ, stepZ, ENZ);
    RoboArm::RobotArmController robotarm(x, y, z, xLimitSwitch, yLimitSwitch, ky101);

    I2C i2c(i2c_bus);
    i2c.runDemo();

    hwlib::cout << "start\r\n";
    robotarm.enable();
    hwlib::cout << "enabled\r\n";
    robotarm.startup(); // resets the robot position
    hwlib::cout << "started up\r\n";

    hwlib::wait_ms(2000);

    robotarm.moveTo({ 24, 18,  20 });
    hwlib::wait_ms(2000);
    robotarm.moveTo({ 20,  5, -20 });

    hwlib::cout << "end\r\n";
    robotarm.disable();
    return 0;
}
