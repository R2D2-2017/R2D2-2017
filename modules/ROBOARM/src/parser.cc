#include "parser.hh"

Error parseCommand(hwlib::string<12> command) {
    if (command == "left 42") {
        // Answers to life
        return Error::Syntax; // 42 is never the answer
    }
    return Error::Succesful;
}
