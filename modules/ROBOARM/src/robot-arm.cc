#include "robot-arm.hh"

RobotArmController::RobotArmController(Stepper &x_axis, Stepper &y_axis, Stepper &z_axis, KY101 & ky101) :
        x_axis(x_axis),
        y_axis(y_axis),
        z_axis(z_axis),
        ky101(ky101)
{}


void RobotArmController::reset() {

}

void RobotArmController::rotateAxis(RobotAxis axis, int degrees, bool clockwise) {

    //This isn't the degrees the robot will turn at the moment.
    //TODO Make the steps based on the gears inside of the robot
    int steps = (int) (degrees / STEP_SIZE);
    switch (axis) {
        case RobotAxis::X:
            x_axis.step(steps, clockwise);
            break;
        case RobotAxis::Y:
            y_axis.step(steps, clockwise);
            break;
        case RobotAxis::Z:
            z_axis.step(steps, clockwise);
            break;

    }
}

void RobotArmController::startup(){
    while(!ky101.get()) {
        rotateAxis(RobotAxis::Z, 1, 1);
    }
    while(!())
};