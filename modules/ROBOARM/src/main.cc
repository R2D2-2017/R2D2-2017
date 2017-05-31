#include <sam3x8e.h>
#include "wrap-hwlib.hh"
#include "stepper.hh"
#include "robot-arm.hh"

int main() {
    WDT->WDT_MR = WDT_MR_WDDIS;

    auto step = hwlib::target::pin_out(hwlib::target::pins::d2);
    auto dir = hwlib::target::pin_out(hwlib::target::pins::d3);

    Stepper s(dir, step);
    RobotArmController r(s, s, s);
    //Rotate the X axis 90 degrees clockwise
    int degrees = 90;
    while(1) {
        hwlib::wait_ms(500);
        r.rotateAxis(RobotAxis::Z, degrees, false);
        hwlib::wait_ms(500);
        r.rotateAxis(RobotAxis::Z, degrees, true);
    }
    return 0;
}
