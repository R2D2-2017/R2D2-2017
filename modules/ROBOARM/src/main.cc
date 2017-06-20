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
#include "wifi.hh"
#include "wrap-hwlib.hh"
#include "robot-arm-tester.hh"
#include "I2C.hh"


int main() {
    hwlib::cout << "hallo\r\n";
    WDT->WDT_MR = WDT_MR_WDDIS;

    auto sclPin = hwlib::target::pin_oc(hwlib::target::pins::d21);
    auto sdaPin = hwlib::target::pin_oc(hwlib::target::pins::d20);
    hwlib::i2c_bus_bit_banged_scl_sda i2c_bus(sclPin, sdaPin);

    auto ky101Pin = hwlib::target::pin_in(hwlib::target::pins::d14);

    // XY motor controlling the angle of the base joint.
    auto m1Enable = hwlib::target::pin_out(hwlib::target::pins::a2);
    auto m1Step   = hwlib::target::pin_out(hwlib::target::pins::a6);
    auto m1Dir    = hwlib::target::pin_out(hwlib::target::pins::a7);

    // XY motor controlling the angle of the middle joint.
    auto m2Enable = hwlib::target::pin_out(2, 6); //d38
    auto m2Step   = hwlib::target::pin_out(hwlib::target::pins::a0);
    auto m2Dir    = hwlib::target::pin_out(hwlib::target::pins::a1);

    // Motor controlling the rotation of the Y axis. (rotates the base of the robot)
    auto m3Enable = hwlib::target::pin_out(hwlib::target::pins::a8);
    auto m3Step   = hwlib::target::pin_out(hwlib::target::pins::d46);
    auto m3Dir    = hwlib::target::pin_out(hwlib::target::pins::d48);

    auto m1LimitSwitch = hwlib::target::pin_in(hwlib::target::pins::d2);
    auto m2LimitSwitch = hwlib::target::pin_in(hwlib::target::pins::d3);
    auto m3LimitSwitch = hwlib::target::pin_in(hwlib::target::pins::d14);

    auto wifiRx = hwlib::target::pin_in(hwlib::target::pins::d19);
    auto wifiTx = hwlib::target::pin_out(hwlib::target::pins::d18);

    auto wifi = Wifi(wifiRx, wifiTx);

    Ky101 ky101(ky101Pin);

    Stepper m1Stepper(m1Dir, m1Step, m1Enable);
    Stepper m2Stepper(m2Dir, m2Step, m2Enable);
    Stepper m3Stepper(m3Dir, m3Step, m3Enable);

    RoboArm::RobotArmController robotarm(m1Stepper,
                                         m2Stepper,
                                         m3Stepper,
                                         m1LimitSwitch,
                                         m2LimitSwitch,
                                         m3LimitSwitch,
                                         ky101);

    I2C i2c(i2c_bus);
    RobotArmTester tester(robotarm, i2c);

    wifi.setupAccessPoint("ROBOARM", "123454321");
    wifi.startServer();

    hwlib::cout << "start\r\n";
    robotarm.enable();
    hwlib::cout << "enabled\r\n";
    robotarm.startup(); // resets the robot position
    hwlib::cout << "started up\r\n";

    //hwlib::wait_ms(2000);

    //robotarm.moveTo({ 12, 12,  0 });
    //hwlib::wait_ms(3000);
    //robotarm.moveTo({ 12, 12,  45 });
    //hwlib::wait_ms(3000);
    //robotarm.moveTo({ 12, 12,  0 });

    //robotarm.moveTo({ 24, 18,  20 });
    //hwlib::wait_ms(3000);
    //robotarm.moveTo({ 15, 2,   20 });
    //hwlib::wait_ms(2000);

    using namespace RoboArm::Parser;
    while (true) {
        hwlib::string<16> command = wifi.receive();

        if (command == "TEST 0") {
            tester.run(0);
            wifi.send("Done\n");
        } else if (command == "TEST 1") {
            tester.run(1);
            wifi.send("Done\n");
        } else if (command == "TEST 2") {
            tester.run(2);
            wifi.send("Done\n");
        } else if (command == "ping") {
            wifi.send("pong\n");
        } else if (command == "help") {
            wifi.send("EN\n");
            wifi.send("DIS\n");
            wifi.send("I2CDemo\n");
            wifi.send("RESET\n");
            wifi.send("X\n");
            wifi.send("Y\n");
            wifi.send("Z\n");
            wifi.send("WAIT_S\n");
            wifi.send("WAIT_MS\n");
            wifi.send("TEST\n\n");
        } else if (command == "exit") {
            break;
        } else {
            Status result = parseCommand(command, robotarm, i2c);
            switch (result) {
                case Status::SyntaxError:
                    wifi.send("Syntax error\n");
                    break;
                case Status::Successful:
                    wifi.send("Done\n");
                    break;
            }
        }
    }

    hwlib::cout << "end\r\n";
    robotarm.disable();
    return 0;
}
