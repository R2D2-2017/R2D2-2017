#include "wrap-hwlib.hh"

#pragma once

enum class Status : uint8_t {
    Succesful   = 0,
    SyntaxError,
    Limit,
};

/**
 * \brief Parses a string and drives the servo motor
 *
 * \param[in]  command   how the servo should be moving as a string eg: "x 42"
 * \param[in]  executor  an interface that provides ways of moving a servo, or anything for that matter
 *
 * \return               returns an error code so you can check if the execution was done succefully
 */
template <typename T>
Status parseCommand(const hwlib::string<0> &command, const T executor) {
    uint8_t space = 0; // the place of the space

    for (; command[space] != ' ' && space < command.length(); space++) // find space
        ;
    if (space == command.length() - 1) return Status::SyntaxError; // cry if no space is found

    const auto start = command.begin();
    const auto end   = command.end();
    hwlib::string<8> action = command.range(start, start + space - 1);
    hwlib::string<4> amount = command.range(start + space + 1, end);

    int16_t intAmount = 0;
    { // string to int routine because no stdlib and not present in hwlib :(
        bool negFlag = 0;
        for (uint8_t i = 0; i < amount.length(); i++) {
            char t = amount[i];

            if (!i) { // only do this the first time
                if (t == '-') {
                    negFlag = true;
                    continue;
                }
            }

            if (!(t >= '0' && t <= '9')) return Status::SyntaxError;

            intAmount *= 10;
            intAmount += t - '0';
        }
        if (negFlag) intAmount *= -1;
    }

    hwlib::cout << action << ' ' << amount << '\n';

    if (action == "X") {
        // servoX(intAmount);
        return Status::Succesful;
    }

    if (action == "Y") {
        // servoY(intAmount);
        return Status::Succesful;
    }

    if (action == "Z") {
        // servoZ(intAmount);
        return Status::Succesful;
    }

    if (action == "WAIT_S") {
        hwlib::wait_ms(intAmount * 1000);
        return Status::Succesful;
    }

    if (action == "WAIT_MS") {
        hwlib::wait_ms(intAmount);
        return Status::Succesful;
    }

    return Status::SyntaxError;
}
