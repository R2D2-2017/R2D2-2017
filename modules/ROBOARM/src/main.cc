#include <sam3x8e.h>
#include "wrap-hwlib.hh"
#include "stepper.hh"
#include "robot-arm.hh"
#include "parser.hh"

int main() {
    WDT->WDT_MR = WDT_MR_WDDIS;

    auto stepX = hwlib::target::pin_out(hwlib::target::pins::d20);
    auto dirX = hwlib::target::pin_out(hwlib::target::pins::d21);

    auto stepY = hwlib::target::pin_out(hwlib::target::pins::d5);
    auto dirY = hwlib::target::pin_out(hwlib::target::pins::d4);

    auto stepZ = hwlib::target::pin_out(hwlib::target::pins::d3);
    auto dirZ = hwlib::target::pin_out(hwlib::target::pins::d2);

    auto switch1 = hwlib::target::pin_in(hwlib::target::pins::d31);
    auto switch2 = hwlib::target::pin_in(hwlib::target::pins::d33);

    //TODO parser requires this hwlib fix - https://github.com/wovo/hwlib/pull/6
    hwlib::string<12> commandList[12] = {
            "WAIT_S 2", "Z 45",
            "WAIT_S 2", "Z -45",
            "WAIT_S 2", "X 45",
            "WAIT_S 2", "X -45",
            "WAIT_S 2", "Y 45",
            "WAIT_S 2", "Y -45",
    };


    Stepper x(dirX, stepX);
    Stepper y(dirY, stepY);
    Stepper z(dirZ, stepZ);
    x.setMaxSpeed(250);
    x.setAcceleration(100);
    y.setMaxSpeed(250);
    y.setAcceleration(100);
    z.setMaxSpeed(250);
    z.setAcceleration(100);

    RobotArmController r(x, y, z, switch1, switch2);
    //Rotate the X axis 90 degrees clockwise
    while (1) {
        hwlib::wait_ms(500);
        r.rotateAxis(RobotAxis::X, 80, true);
        hwlib::wait_ms(500);
        r.rotateAxis(RobotAxis::Y, 80, true);
        hwlib::wait_ms(500);
        r.rotateAxis(RobotAxis::X, 80, false);
        hwlib::wait_ms(500);
        r.rotateAxis(RobotAxis::Y, 80, false);
    }

    for (auto command: commandList) {
        Status result = parseCommand(command, r);
        switch(result) {
            case Status::SyntaxError:
                hwlib::cout << "Syntax error" << "\n";
            break;
        }
    }
    return 0;
}
