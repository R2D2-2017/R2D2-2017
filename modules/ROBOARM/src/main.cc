#include "ky101.hh"
#include "parser.hh"
#include "robot-arm.hh"
#include "stepper.hh"
#include "wrap-hwlib.hh"
#include <sam3x8e.h>

int main() {
    WDT->WDT_MR = WDT_MR_WDDIS;

    auto ky101Pin = hwlib::target::pin_in(hwlib::target::pins::d7);

    auto stepX = hwlib::target::pin_out(hwlib::target::pins::d20);
    auto dirX  = hwlib::target::pin_out(hwlib::target::pins::d21);
    auto stepY = hwlib::target::pin_out(hwlib::target::pins::d5);
    auto dirY  = hwlib::target::pin_out(hwlib::target::pins::d4);
    auto stepZ = hwlib::target::pin_out(hwlib::target::pins::d3);
    auto dirZ  = hwlib::target::pin_out(hwlib::target::pins::d2);

    auto xLimitSwitch = hwlib::target::pin_in(hwlib::target::pins::d31);
    auto yLimitSwitch = hwlib::target::pin_in(hwlib::target::pins::d33);

    Ky101 ky101(ky101Pin);

    // TODO parser requires this hwlib fix - https://github.com/wovo/hwlib/pull/6
    hwlib::string<12> commandList[] = {
        // Z axis test
        "WAIT_S 2", "Z 90", "WAIT_S 2", "Z -90", "WAIT_S 2", "Z 180", "WAIT_S 2", "Z -180", "WAIT_S 2",

        // Y axis test
        "Y 90", "WAIT_S 2", "Y -90", "WAIT_S 2", "Y 180", "WAIT_S 2", "Y -180", "WAIT_S 2",

        // X axis test
        "X 90", "WAIT_S 2", "X -90", "WAIT_S 2", "X 180", "WAIT_S 2", "X -240",

        // Reset
        "RESET"
    };

    Stepper            x(dirX, stepX);
    Stepper            y(dirY, stepY);
    Stepper            z(dirZ, stepZ);
    RobotArmController r(x, y, z, xLimitSwitch, yLimitSwitch, ky101);

    hwlib::cout << "START SEQUENCE" << '\n';

    r.startup(); // resets the robot position
    hwlib::cout << "Position has been reset" << '\n';

    for (auto command : commandList) {
        Status result = parseCommand(command, r);

        switch (result) {
        case Status::SyntaxError:
            hwlib::cout << "Syntax error" << '\n';
            break;
        case Status::Succesful:
            break;
        case Status::Limit:
            break;
        }
    }

    hwlib::cout << "END SEQUENCE" << '\n';

    return 0;
}
