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
#include "robot-arm-tester.hh"
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
    I2C i2c(i2c_bus);
    RobotArmTester tester(r, i2c);

    w.setupAccessPoint("ROBOARM", "123454321");
    w.startServer();

    using namespace RoboArm::Parser;
    while (true) {
        hwlib::string<16> command = w.receive();

        if (command == "TEST 0") {
            tester.run(0);
        }
        if (command == "TEST 1") {
            tester.run(1);
        }
        if (command == "TEST 2") {
            tester.run(2);
        }
        if (command == "ping") {
            w.send("pong\n");
            continue;
        }
        if (command == "help") {
            w.send("EN\n");
            w.send("DIS\n");
            w.send("I2CDemo\n");
            w.send("RESET\n");
            w.send("X\n");
            w.send("Y\n");
            w.send("Z\n");
            w.send("WAIT_S\n");
            w.send("WAIT_MS\n");
            w.send("TEST\n\n");
            continue;
        }
        if (command == "exit") {
            break;
        }

        Status result = parseCommand(command, r, i2c);

        switch (result) {
            case Status::SyntaxError:
                w.send("Syntax error\n");
                break;
            case Status::Successful:
                w.send("Done\n");
                break;
        }
    }

    return 0;
}