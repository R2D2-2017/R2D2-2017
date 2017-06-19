/**
 * \file
 * \author    Bob Thomas
 * \author    Remco Ruttenberg
 * \author    Chris Smeele
 * \copyright Copyright (c) 2017, The R2D2 Team
 * \license   See LICENSE
 */

#include "robot-arm.hh"
#include <cmath>

using namespace RoboArm;

RobotArmController::RobotArmController(
    Stepper &xAxis,
    Stepper &yAxis,
    Stepper &zAxis,
    hwlib::target::pin_in &xLimitSwitch,
    hwlib::target::pin_in &yLimitSwitch,
    Ky101 &ky101)
    : xAxis(xAxis),
      yAxis(yAxis),
      zAxis(zAxis),
      xLimitSwitch(xLimitSwitch),
      yLimitSwitch(yLimitSwitch),
      ky101(ky101)
{ }

void RobotArmController::rotateAxis(RobotAxis axis,
                                    int degrees,
                                    bool clockwise) {

    int selectedMicroSteps = (axis == RobotAxis::Z) ? microStepsBase
                                                    : microStepsArms;
    int selectedRatio = (int) ((axis == RobotAxis::Z) ? baseStepRatio
                                                      : armStepRatio);
    int requiredSteps = (int) (selectedMicroSteps
                               * (degrees * selectedRatio) / stepSize);

    hwlib::cout << "required: " << requiredSteps << "\r\n";


    for (int stepsTaken = 0; stepsTaken < requiredSteps; stepsTaken++) {
        RobotLimitSwitch switchEnabled = checkLimitations();
        hwlib::cout << "\r" << stepsTaken;

        if ((axis == RobotAxis::X && !clockwise
             && (   switchEnabled == RobotLimitSwitch::BOTH
                 || switchEnabled == RobotLimitSwitch::X))
            || (axis == RobotAxis::Y && !clockwise &&
                (   switchEnabled == RobotLimitSwitch::BOTH
                 || switchEnabled == RobotLimitSwitch::Y))) {

            break;
        }

        if (axis == RobotAxis::X)
            xAxis.step(clockwise);
        else if (axis == RobotAxis::Y)
            yAxis.step(clockwise);
        else if (axis == RobotAxis::Z)
            zAxis.step(clockwise);
    }
}

template<typename T>
constexpr T pow2(T v) { return v * v; }

constexpr float pi = 3.141592653589793;

constexpr float rad2deg(float rad) { return rad * (180/pi); }
constexpr float deg2rad(float deg) { return deg * (pi/180); }


std::tuple<float,float,float>
RobotArmController::positionToMotorRotations(Position pos) {

    // FIXME: Make it clear where radians/degrees are used.

    float distance = sqrt(pow2(pos.x) + pow2(pos.y));
    float slope    =  atan(pos.y / pos.x);

    float joint1Rot = acos((pow2(arm1Length) + pow2(distance) - pow2(arm2Length))
                           / (2 * arm1Length * distance)) + slope;

    float joint2Rot = joint1Rot - pi
                    + acos((pow2(arm1Length) + pow2(arm2Length) - pow2(distance))
                           / (2 * arm1Length * arm2Length));

    float yRot = deg2rad(pos.yRot);

    return std::make_tuple(joint1Rot, -joint2Rot, yRot);
}

static hwlib::ostream &operator<<(hwlib::ostream &stream, float v) {
    // Print a float with one decimal.
    stream << (int)v << "." << (int)(v * 10) % 10;
    return stream;
}

static hwlib::ostream &operator<<(hwlib::ostream &stream, Position pos) {
    stream << "(" << pos.x << ", " << pos.y << ", ∠" << pos.yRot << "r)";
    return stream;
}

bool RobotArmController::moveTo(Position pos) {
    hwlib::cout << "moving to " << pos << "\r\n";

    // TODO: Reach checking, return false if pos is out of reach.
    auto newMotorRotations = positionToMotorRotations(pos);

    hwlib::cout << "motors: "
                << rad2deg(std::get<0>(newMotorRotations)) << ", "
                << rad2deg(std::get<1>(newMotorRotations)) << ", "
                << rad2deg(std::get<2>(newMotorRotations)) << "\r\n";

    std::get<0>(newMotorRotations) = rad2deg(std::get<0>(newMotorRotations));
    std::get<1>(newMotorRotations) = rad2deg(std::get<1>(newMotorRotations));
    std::get<2>(newMotorRotations) = rad2deg(std::get<2>(newMotorRotations));

    hwlib::cout << "rotate 1 by " << (std::get<0>(newMotorRotations)
                                      - std::get<0>(motorRotations)) << "\r\n";
    rotateAxis(RobotAxis::Y,
               fabs(std::get<0>(newMotorRotations)
                    - std::get<0>(motorRotations)),
               std::get<0>(newMotorRotations)
               - std::get<0>(motorRotations) >= 0);

    hwlib::cout << "rotate 2 by " << (std::get<1>(newMotorRotations)
                                      - std::get<1>(motorRotations)) << "\r\n";
    rotateAxis(RobotAxis::X,
               fabs(std::get<1>(newMotorRotations)
                    - std::get<1>(motorRotations)),
               std::get<1>(newMotorRotations)
               - std::get<1>(motorRotations) >= 0);

    hwlib::cout << "rotate 3 by " << (std::get<2>(newMotorRotations)
                                      - std::get<2>(motorRotations)) << "\r\n";
    rotateAxis(RobotAxis::Z,
               fabs(std::get<2>(newMotorRotations)
                    - std::get<2>(motorRotations)),
               std::get<2>(newMotorRotations)
               - std::get<2>(motorRotations) >= 0);

    motorRotations = newMotorRotations;

    return true;
}

RobotLimitSwitch RobotArmController::checkLimitations() {
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
void RobotArmController::startup() {
    //TODO add new chip to the robot current one is damaged
//    while (!ky101.get()) {
//        rotateAxis(RobotAxis::Z, 1, true);
//    }
    while (xLimitSwitch.get()) {
        rotateAxis(RobotAxis::X, 1, false);
    }
    while (yLimitSwitch.get()) {
        rotateAxis(RobotAxis::Y, 1, true);
    }
}

void RobotArmController::enable() {
    xAxis.enable();
    yAxis.enable();
    zAxis.enable();
}

void RobotArmController::disable() {
    xAxis.disable();
    yAxis.disable();
    zAxis.disable();
}
