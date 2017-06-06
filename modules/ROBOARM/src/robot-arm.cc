/**
 * \file
 * \author    Bob Thomas
 * \author    Remco Ruttenberg
 * \copyright Copyright (c) 2017, The R2D2 Team
 * \license   See LICENSE
 */

#include "robot-arm.hh"
using namespace RoboArm;

RoboArm::RobotArmController::RobotArmController(
        Stepper &xAxis, Stepper &yAxis,
        Stepper &zAxis, hwlib::target::pin_in &xLimitSwitch,
        hwlib::target::pin_in &yLimitSwitch, Ky101 &ky101)
        :
        xAxis(xAxis), yAxis(yAxis), zAxis(zAxis), xLimitSwitch(xLimitSwitch),
        yLimitSwitch(yLimitSwitch), ky101(ky101) { }

void RoboArm::RobotArmController::rotateAxis(RobotAxis axis, int degrees, bool clockwise) {
    int selectedMicroSteps = (axis == RobotAxis::Z) ? microStepsBase : microStepsArms;
    int selectedRatio = (int) ((axis == RobotAxis::Z) ? baseStepRatio : armStepRatio);
    int requiredSteps = (int) (selectedMicroSteps * (degrees * selectedRatio) / stepSize);

    for (int stepsTaken = 0; stepsTaken < requiredSteps; stepsTaken++) {
        RobotLimitSwitch switchEnabled = checkLimitations();

        switch (axis) {
            case RobotAxis::X:
                if (!clockwise && (switchEnabled == RobotLimitSwitch::BOTH ||
                     switchEnabled == RobotLimitSwitch::X)) {

                    break;
                }
                xAxis.step(clockwise);
                break;
            case RobotAxis::Y:
                if (!clockwise && (switchEnabled == RobotLimitSwitch::BOTH ||
                     switchEnabled == RobotLimitSwitch::Y)) {
                    break;
                }
                yAxis.step(clockwise);
                break;
            case RobotAxis::Z:
                zAxis.step(clockwise);
                break;
        }
    }
}

RobotLimitSwitch RoboArm::RobotArmController::checkLimitations() {
    if (!xLimitSwitch.get() && !yLimitSwitch.get()) {
        return RobotLimitSwitch::BOTH;
    } else if (!xLimitSwitch.get()) {
        return RobotLimitSwitch::X;
    } else if (!yLimitSwitch.get()) {
        return RobotLimitSwitch::Y;
    } else {
        return RobotLimitSwitch::NONE;
    }
}

// The amounts of steps in rotateAxis functions is yet to be determined through testing.
// TODO test variables
void RoboArm::RobotArmController::startup() {
    //TODO add new chip to the robot current one is damaged
//    while (!ky101.get()) {
//        rotateAxis(RobotAxis::Z, 1, true);
//    }
    while (!xLimitSwitch.get()) {
        rotateAxis(RobotAxis::X, 1, true);
    }
    while (!yLimitSwitch.get()) {
        rotateAxis(RobotAxis::Y, 1, false);
    }
}
