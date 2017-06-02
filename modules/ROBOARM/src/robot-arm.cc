#include "robot-arm.hh"

RobotArmController::RobotArmController(Stepper &x_axis, Stepper &y_axis, Stepper &z_axis,
                                       hwlib::target::pin_in &xLimitSwitch,
                                       hwlib::target::pin_in &yLimitSwitch) :
        x_axis(x_axis),
        y_axis(y_axis),
        z_axis(z_axis),
        xLimitSwitch(xLimitSwitch),
        yLimitSwitch(yLimitSwitch) {

}


void RobotArmController::reset() {
    rotateAxis(RobotAxis::Y, 20, false);
}

void RobotArmController::rotateAxis(RobotAxis axis, int degrees, bool clockwise) {

    //This isn't the degrees the robot will turn at the moment.
    //TODO Make the steps based on the gears inside of the robot

    int requiredSteps = microStepsArms * (degrees * armStepRatio) / stepSize;
    if(axis == RobotAxis::Z) {
      requiredSteps = microStepsBase * (degrees * baseStepRatio) / stepSize;
    }
    //TODO add limitation check
    switch (axis) {
        case RobotAxis::X:
            x_axis.setTarget(requiredSteps, clockwise);
            break;
        case RobotAxis::Y:
            y_axis.setTarget(requiredSteps, clockwise);
            break;
        case RobotAxis::Z:
            z_axis.setTarget(requiredSteps, clockwise);
            break;
    }

    while (x_axis.inMotion() || y_axis.inMotion() || z_axis.inMotion()) {
        if(checkLimitations() > 0) {
            if(checkLimitations() == 3 || checkLimitations() == 1) {
                x_axis.resetPosition();
            }
            if(checkLimitations() == 3 || checkLimitations() == 2) {
                y_axis.resetPosition();
            }
        } else {
            x_axis.run();
            y_axis.run();
        }
        z_axis.run();
    }
}

int RobotArmController::checkLimitations() {
    if (!xLimitSwitch.get() && !yLimitSwitch.get()) {
        return 3;
    } else if (!xLimitSwitch.get()) {
        return 1;
    } else if (!yLimitSwitch.get()) {
        return 2;
    } else {
        return 0;
    }

}
