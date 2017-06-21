/**
 * \file      config-file-parser.cc
 * \brief     Class for getting information out of a config file
 * \author    Tim IJntema, Jeremy Ruizenaar, Ricardo Bouwman, Luuk Steeman
 * \copyright Copyright (c) 2017, The R2D2 Team
 * \license   See LICENSE
 */

#include "config-file-parser.hh"

#include <iostream>
#include <string>

using namespace std::literals;

ConfigFileParser::ConfigFileParser(const std::string &databaseFile)
    : databaseFile(databaseFile) {}

void ConfigFileParser::incorrectLineCheck(
                                          const std::string &fileName,
                                          int line) {

    // Casted to string to prevent error involving const char array +
    // std::string not same type
    throw std::runtime_error( "Incorrect input"s +
                             "\nFunction call in file: "s + fileName +
                             " line: "s + std::to_string(line));
}

void ConfigFileParser::loadDatabaseSettings(std::string &ip,
                                            std::string &username,
                                            std::string &password) {

    // open database file if not opened throw error
    std::ifstream file;
    file.open(databaseFile);
    if (!file.is_open()) {
        throw std::runtime_error("File not opened ");
    }

    // the string for reading input
    std::string input;

    file >> input;
    if (input != "IP:")
        incorrectLineCheck(__FILE__, __LINE__);
    file >> ip;
    if (ip == "\n")
        incorrectLineCheck(__FILE__, __LINE__);

    file >> input;
    if (input != "USERNAME:")
        incorrectLineCheck(__FILE__, __LINE__);
    file >> username;
    if (username == "\n")
        incorrectLineCheck(__FILE__, __LINE__);

    file >> input;
    if (input!= "PASSWORD:")
        incorrectLineCheck(__FILE__, __LINE__);
    file >> password;
    if (password == "\n" || file.eof())
        incorrectLineCheck(__FILE__, __LINE__);

    // throw error if reading went wrong
    if (ip.empty() || username.empty() || password.empty()) {
        throw std::runtime_error("Missing input after reading file: ");
    }
    file.close();
}
