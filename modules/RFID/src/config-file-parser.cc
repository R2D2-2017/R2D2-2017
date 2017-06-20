/**
 * \file      config-file-parser.cc
 * \brief     Library for getting information out of a config file
 * \author    Tim IJntema, Jeremy Ruizenaar, Ricardo Bouwman
 * \copyright Copyright (c) 2017, The R2D2 Team
 * \license   See LICENSE
 */


#include "config-file-parser.hh"

#include <iostream>


ConfigFileParser::ConfigFileParser(const std::string & databaseFile):
    databaseFile( databaseFile )
{}


void ConfigFileParser::incorrectLineCheck(const bool & toCheck, const std::string & fileName, int line) {
    if (toCheck) {
    	// Casted to string to prevent error involving const char array + std::string not same type
        throw std::runtime_error((std::string)"Incorrect input"
                + "\nFunction call in file: " + fileName + " line: " + std::to_string(line));
    }
}

/**
 * \brief Reducing the amount of arguments needed to call incorrectLineCheck
 */
#define incorrectLineCheck(toCheck) incorrectLineCheck(toCheck, __FILE__, __LINE__)

void ConfigFileParser::loadDatabaseSettings(std::string & ip, std::string & username, std::string & password) {

    //open databasefile if not opened throw error
    std::ifstream file;
    file.open(databaseFile);
    if(!file.is_open()){
        throw std::runtime_error("File not opened ");
    }

    // the string for reading input
    std::string input;

    file >> input;
    incorrectLineCheck(input != "IP:");
    file >> ip;
    incorrectLineCheck(ip == "\n");

    file >> input;
    incorrectLineCheck(input != "USERNAME:");
    file >> username;
    incorrectLineCheck(username == "\n");

    file >> input;
    incorrectLineCheck(input != "PASSWORD:");
    file >> password;
    incorrectLineCheck(password == "\n" || file.eof());

    // throw error if reading went wrong
    if (ip.empty() || username.empty() || password.empty()) {
        throw std::runtime_error("Missing input after reading file: ");
    }
    file.close();
}
