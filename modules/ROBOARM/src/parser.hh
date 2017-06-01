#include "wrap-hwlib.hh"

enum class Status : uint8_t {
    Succesful   = 0,
    SyntaxError,
    Limit,
};

/**
 * \brief Parses a string and drives the servo motor
 *
 * @param[in]  command  how the servo should be moving as a string eg: "x 42"
 * @return              returns an error code so you can check if the execution was done succefully
 */
Status parseCommand(hwlib::string<0> command);
