#include "wrap-hwlib.hh"

enum class Error : uint8_t {
    Succesful = 0,
    Syntax,
    Limit,
};

/**
 * \brief Parses a string and drives the servo motor
 *
 * @param  command    how the servo should be moving as a string eg: "x 42"
 * @return            returns an error code so you can check if the execution was done succefully
 */
Error parseCommand(hwlib::string<12> command);
