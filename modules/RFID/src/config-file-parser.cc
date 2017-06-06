/**
 * \file      config-file-parser.cc
 * \brief     Library for getting information out of a config file
 * \author    Tim IJntema
 * \copyright Copyright (c) 2017, The R2D2 Team
 * \license   See LICENSE
 */


#include "config-file-parser.hh"

#include <iostream>


ConfigFileParser::ConfigFileParser(const std::string & fileName) {
    changeFile(fileName);
}

ConfigFileParser::~ConfigFileParser() {
    file.close();
}

void ConfigFileParser::incorrectLineCheck(const bool & toCheck, const std::string & fileName, int line) {
    if (toCheck) {
    	// Casted to string to prevent error involving const char array + std::string not same type
        throw std::runtime_error((std::string)"Incorrect input"
                + "\nFunction call in file: " + fileName + " line: " + std::to_string(line)
                + "\nWhile reading from: " + nameCurrentFile + " line: " + std::to_string(lineCurrentFile));
    }
}

/**
 * \brief Reducing the amount of arguments needed to call incorrectLineCheck
 */
#define incorrectLineCheck(toCheck) incorrectLineCheck(toCheck, __FILE__, __LINE__)

void ConfigFileParser::fileOpenCheck(){
    if (!file.is_open()) {
        throw std::runtime_error("File is not open");
    }
}

void ConfigFileParser::changeFile(const std::string & fileName) {
    if (file.is_open()) {
        file.close();
    }
    
    file.open(fileName);
    
    if (!file.is_open()) {
        throw std::runtime_error("Failed to open file with name: " + fileName);
    }
    nameCurrentFile = fileName;
    lineCurrentFile = 1;
    
}

void ConfigFileParser::loadDatabaseSettings(std::string & ip, std::string & username, std::string & password) {
    fileOpenCheck();
    
    file >> input;
    incorrectLineCheck(input != "IP:");
    file >> ip;
    incorrectLineCheck(ip == "\n");
    ++lineCurrentFile;
    
    file >> input;
    incorrectLineCheck(input != "USERNAME:");
    file >> username;
    incorrectLineCheck(username == "\n");
    ++lineCurrentFile;
    
    file >> input;
    incorrectLineCheck(input != "PASSWORD:");
    file >> password;
    incorrectLineCheck(password == "\n" || file.eof());
    ++lineCurrentFile;
    
    if (ip.empty() || username.empty() || password.empty()) {
        throw std::runtime_error("Missing input after reading file: " + nameCurrentFile);
    }
}

void ConfigFileParser::loadEncryptionSettings(int & encryptionKey){
    fileOpenCheck();
    
    file >> input;
    incorrectLineCheck(input != "KEY:");
    file >> encryptionKey;
    incorrectLineCheck(file.eof());
    ++lineCurrentFile;
    
    if (!encryptionKey) {
        throw std::runtime_error("Missing input after reading file: " + nameCurrentFile);
    }
}