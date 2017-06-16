/**
 * \file
 * \brief     Usage example
 * \author    Bob Thomas, David Driessen
 * \copyright Copyright (c) 2017, The R2D2 Team
 * \license   See LICENSE
 */
#include "ky101.hh"
#include "parser.hh"
#include "robot-arm.hh"
#include "stepper.hh"
#include "wifi.hh"
#include "wrap-hwlib.hh"
#include "RobotArmTester.hh"
#include "I2C.hh"

int main() {
    WDT->WDT_MR = WDT_MR_WDDIS;

    auto sclPin = hwlib::target::pin_oc(hwlib::target::pins::d21);
    auto sdaPin = hwlib::target::pin_oc(hwlib::target::pins::d20);
    hwlib::i2c_bus_bit_banged_scl_sda i2c_bus(sclPin, sdaPin);

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

    auto wifiRx = hwlib::target::pin_in(hwlib::target::pins::d19);
    auto wifiTx = hwlib::target::pin_out(hwlib::target::pins::d18);

    auto w = Wifi(wifiRx, wifiTx);

    Ky101 ky101(ky101Pin);
    Stepper x(dirX, stepX, ENX);
    Stepper y(dirY, stepY, ENY);
    Stepper z(dirZ, stepZ, ENZ);
    RoboArm::RobotArmController r(x, y, z, xLimitSwitch, yLimitSwitch, ky101);

    w.setupAccessPoint("ROBOARM", "123454321");
    w.startServer();

    using namespace RoboArm::Parser;
    for (int i = 0; i < 600; i++) {
        hwlib::string<16> command = w.receiveData();

        if (command == "ping") {
            w.send("pong\n");
            continue;
        }

        Status result = parseCommand(command, r);

        switch (result) {
            case Status::SyntaxError:
                w.send("Syntax error\n");
                break;
            case Status::Successful:
                w.send("Done\n");
                break;
        }
    }

//    I2C i2c(i2c_bus);
//    i2c.runDemo();
//
//    RobotArmTester tester(r);
//
//    tester.run();

    return 0;
}