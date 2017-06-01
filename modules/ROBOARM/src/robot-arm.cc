#include "robot-arm.hh"

RobotArmController::RobotArmController(Stepper &x_axis, Stepper &y_axis, Stepper &z_axis) : x_axis(x_axis),
                                                                                            y_axis(y_axis),
                                                                                            z_axis(z_axis) {

}


void RobotArmController::reset() {

}

void RobotArmController::rotateAxis(RobotAxis axis, int degrees, bool clockwise) {

    //This isn't the degrees the robot will turn at the moment.
    //TODO Make the steps based on the gears inside of the robot
    int steps = microStepsArms * (degrees * armStepRatio) / stepSize;
    switch (axis) {
        case RobotAxis::X:
            x_axis.step(steps, clockwise);
            break;
        case RobotAxis::Y:
            y_axis.step(steps, clockwise);
            break;
        case RobotAxis::Z:
            steps = microStepsBase * (degrees * baseStepRatio) / stepSize;
            z_axis.step(steps, clockwise);
            break;

    }
}
