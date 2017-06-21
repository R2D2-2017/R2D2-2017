/**
 * \file
 * \author    Bob Thomas
 * \author    Remco Ruttenberg
 * \author    Chris Smeele
 * \author    Paul Ettema
 * \copyright Copyright (c) 2017, The R2D2 Team
 * \license   See LICENSE
 */

#include "robot-arm.hh"
#include <cmath>

using namespace RoboArm;

RobotArmController::RobotArmController(
        Stepper &m1Stepper,
        Stepper &m2Stepper,
        Stepper &m3Stepper,
        hwlib::target::pin_in &m1LimitSwitch,
        hwlib::target::pin_in &m2LimitSwitch,
        hwlib::target::pin_in &m3LimitSwitch,
        Ky101 &ky101)
        : m1Stepper(m1Stepper),
          m2Stepper(m2Stepper),
          m3Stepper(m3Stepper),
          m1LimitSwitch(m1LimitSwitch),
          m2LimitSwitch(m2LimitSwitch),
          m3LimitSwitch(m3LimitSwitch),
          ky101(ky101) {}

bool RobotArmController::canRotateMotor(Motor motor, int degrees) const {
    auto limits = motorLimits[motor == Motor::M1 ? 0 : motor == Motor::M2 ? 1 : 2];

    // This is annoying. 💩
    auto oldRot = (  motor == Motor::M1 ? std::get<0>(motorRotations)
                   : motor == Motor::M2 ? std::get<1>(motorRotations)
                   :                      std::get<2>(motorRotations));

    auto newRot = oldRot + degrees;

    return newRot >= limits.first && newRot <= limits.second;
}

bool RobotArmController::rotateMotor(Motor motor, int degrees) {

    if (!canRotateMotor(motor, degrees))
        return false;

    int selectedMicroSteps = (motor == Motor::M3) ? microStepsBase
                                                  : microStepsArms;
    int selectedRatio = (int) ((motor == Motor::M3) ? baseStepRatio
                                                    : armStepRatio);
    int requiredSteps = (int) (selectedMicroSteps
                               * (abs(degrees) * selectedRatio) / stepSize);

    hwlib::cout << "required: " << requiredSteps << "\r\n";

    bool clockwise = degrees < 0;

    for (int stepsTaken = 0; stepsTaken < requiredSteps; stepsTaken++) {
        RobotLimitSwitch switchEnabled = checkLimitations();
        hwlib::cout << "\r" << stepsTaken;

        if ((motor == Motor::M1 && !clockwise
             && (switchEnabled == RobotLimitSwitch::BOTH
                 || switchEnabled == RobotLimitSwitch::M1))
            || (motor == Motor::M2 && !clockwise &&
                (switchEnabled == RobotLimitSwitch::BOTH
                 || switchEnabled == RobotLimitSwitch::M2))) {

            break;
        }

        if (motor == Motor::M1)
            m1Stepper.step(!clockwise);
        else if (motor == Motor::M2)
            m2Stepper.step(clockwise);
        else if (motor == Motor::M3)
            m3Stepper.step(clockwise);
    }

    (  motor == Motor::M1 ? std::get<0>(motorRotations)
     : motor == Motor::M2 ? std::get<1>(motorRotations)
     :                      std::get<2>(motorRotations))
        += degrees;

    return true;
}

template<typename T>
constexpr T pow2(T v) { return v * v; }

constexpr float pi = 3.141592653589793;

constexpr float rad2deg(float rad) { return rad * (180 / pi); }

constexpr float deg2rad(float deg) { return deg * (pi / 180); }

std::tuple<float,float,float>
RobotArmController::positionToMotorRotations(Position pos) {

    // See https://github.com/R2D2-2017/R2D2-2017/wiki/%5BROBOARM%5D-Forward-and--Inverse-kinematics
    // for an explanation for these formulas.

    float distance  = sqrt(pow2(pos.x) + pow2(pos.y));
    float slope     = atan(pos.y / pos.x);

    float joint1Rot =
            acos((pow2(arm1Length) + pow2(distance) - pow2(arm2Length))
                 / (2 * arm1Length * distance)) + slope;

    float joint2Rot = joint1Rot - pi
                      + acos((pow2(arm1Length) + pow2(arm2Length) -
                              pow2(distance))
                             / (2 * arm1Length * arm2Length));

    return std::make_tuple(rad2deg(joint1Rot),
                           rad2deg(joint2Rot),
                           pos.yRot);
}

static hwlib::ostream &operator<<(hwlib::ostream &stream, float v) {
    // Print a float with one decimal.
    stream << (int) v << "." << (int) (v * 10) % 10;
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
                << std::get<0>(newMotorRotations) << ", "
                << std::get<1>(newMotorRotations) << ", "
                << std::get<2>(newMotorRotations) << "\r\n";

    hwlib::cout << "rotate 1 by " << (std::get<0>(newMotorRotations)
                                      - std::get<0>(motorRotations)) << "\r\n";
    rotateMotor(Motor::M1,
                std::get<0>(newMotorRotations)
                - std::get<0>(motorRotations));

    hwlib::cout << "rotate 2 by " << (std::get<1>(newMotorRotations)
                                      - std::get<1>(motorRotations)) << "\r\n";
    rotateMotor(Motor::M2,
                std::get<1>(newMotorRotations)
                - std::get<1>(motorRotations));

    hwlib::cout << "rotate 3 by " << (std::get<2>(newMotorRotations)
                                      - std::get<2>(motorRotations)) << "\r\n";
    rotateMotor(Motor::M3,
                std::get<2>(newMotorRotations)
                - std::get<2>(motorRotations));

    return true;
}

RobotLimitSwitch RobotArmController::checkLimitations() {
    if (!m1LimitSwitch.get())
        if (!m2LimitSwitch.get())
            return RobotLimitSwitch::BOTH;
        else
            return RobotLimitSwitch::M1;
    else if (!m2LimitSwitch.get())
        return RobotLimitSwitch::M2;
    else
        return RobotLimitSwitch::NONE;
}

void RobotArmController::startup() {
    auto initialRotations = motorRotations;

    while (m3LimitSwitch.get()) {
        std::get<2>(motorRotations) = motorLimits[2].first + 5;
        rotateMotor(Motor::M3, 1);
    }
    while (m2LimitSwitch.get()) {
        // Override rotation limit checks - we don't know the current rotation anyway.
        std::get<1>(motorRotations) = motorLimits[1].first + 5;
        rotateMotor(Motor::M2, 1);
    }
    while (m1LimitSwitch.get()) {
        std::get<0>(motorRotations) = motorLimits[0].first + 5;
        rotateMotor(Motor::M1, 1);
    }

    motorRotations = initialRotations;
}

void RobotArmController::enable() {
    m1Stepper.enable();
    m2Stepper.enable();
    m3Stepper.enable();
}

void RobotArmController::disable() {
    m1Stepper.disable();
    m2Stepper.disable();
    m3Stepper.disable();
}
