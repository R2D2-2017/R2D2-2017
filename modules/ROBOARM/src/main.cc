#include <sam3x8e.h>
#include "wrap-hwlib.hh"
#include "stepper.hh"
#include "robot-arm.hh"

int main() {
    WDT->WDT_MR = WDT_MR_WDDIS;

    auto stepX = hwlib::target::pin_out(hwlib::target::pins::d4);
    auto dirX = hwlib::target::pin_out(hwlib::target::pins::d5);

    auto stepY = hwlib::target::pin_out(hwlib::target::pins::d20);
    auto dirY = hwlib::target::pin_out(hwlib::target::pins::d21);

    auto stepZ = hwlib::target::pin_out(hwlib::target::pins::d3);
    auto dirZ = hwlib::target::pin_out(hwlib::target::pins::d2);


    Stepper x(dirX, stepX);
    Stepper y(dirY, stepY);
    Stepper z(dirZ, stepZ);
    RobotArmController r(x, y, z);
    //Rotate the X axis 90 degrees clockwise
    while(1) {
        hwlib::wait_ms(500);
        r.rotateAxis(RobotAxis::X, 80, true);
        hwlib::wait_ms(500);
        r.rotateAxis(RobotAxis::Y, 80, true);
        hwlib::wait_ms(500);
        r.rotateAxis(RobotAxis::X, 80, false);
        hwlib::wait_ms(500);
        r.rotateAxis(RobotAxis::Y, 80, false);

    }
    return 0;
}
