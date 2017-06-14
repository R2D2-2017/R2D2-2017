/**
 * \file
 * \brief     Usage example
 * \author    Bob Thomas
 * \copyright Copyright (c) 2017, The R2D2 Team
 * \license   See LICENSE
 */
#include "ky101.hh"
#include "parser.hh"
#include "robot-arm.hh"
#include "stepper.hh"
#include "wrap-hwlib.hh"

int main() {
    WDT->WDT_MR = WDT_MR_WDDIS;

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


    // TODO parser requires this hwlib fix - https://github.com/wovo/hwlib/pull/6
    hwlib::string<12> commandList[] = {
            // Reset
            "RESET 1",

            // Z axis test
            "WAIT_S 2", "Z 90", "WAIT_S 2", "Z -90", "WAIT_S 2", "Z 180",
            "WAIT_S 2", "Z -180", "WAIT_S 2",

            // Y axis test
            "Y 90", "WAIT_S 2", "Y -90", "WAIT_S 2", "Y 180", "WAIT_S 2",
            "Y -180", "WAIT_S 2",

            // X axis test
            "X 90", "WAIT_S 2", "X -90", "WAIT_S 2", "X 180", "WAIT_S 2",
            "X -240",

            // Reset
            "RESET 1",

            //BLOCKING TEST
            "WAIT_S 2", "Z 720", "WAIT_MS 500"
    };

    using namespace RoboArm;
    using namespace RoboArm::Parser;

    Ky101 ky101(ky101Pin);
    Stepper x(dirX, stepX, ENX);
    Stepper y(dirY, stepY, ENY);
    Stepper z(dirZ, stepZ, ENZ);
    RobotArmController r(x, y, z, xLimitSwitch, yLimitSwitch, ky101);

    hwlib::cout << "START SEQUENCE" << "\r\n";
    r.enable();

    r.startup(); // resets the robot position
    hwlib::cout << "Position has been reset" << "\r\n";

    for (const auto &command : commandList) {
        Status result = parseCommand(command, r);

        switch (result) {
            case Status::SyntaxError:
                hwlib::cout << "Syntax error" << "\r\n";
                break;
            case Status::Successful:
                break;
        }
    }

    r.disable();
    hwlib::cout << "END SEQUENCE" << "\r\n";

    return 0;
}
