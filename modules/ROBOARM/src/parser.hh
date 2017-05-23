#include "wrap-hwlib.hh"

enum Error {
    Succesful = 0,
    Syntax,
    Limit,
};

Error parseCommand(hwlib::string<12>);
