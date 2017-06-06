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

    while(true) {
        //Rotate the X axis 90 degrees clockwise
        hwlib::wait_ms(500);
        r.rotateAxis(RobotAxis::X, 90, true);

        //Rotate the X axis 90 degrees counter clockwise
        hwlib::wait_ms(500);
        r.rotateAxis(RobotAxis::X, 90, false);

        //Starting blocking test
        hwlib::wait_ms(1000);
        r.rotateAxis(RobotAxis::Z, 720, true);

    }
    return 0;
}
