/**
 * \file      file-factory.cc
 * \brief     Library for getting information out of a file
 * \author    Tim IJntema
 * \copyright Copyright (c) 2017, The R2D2 Team
 * \license   See LICENSE
 */


#include "file-factory.hh"

#include <iostream>

FileFactory::FileFactory(const std::string & fileName) {
    changeFile(fileName);
}

FileFactory::~FileFactory() {
    file.close();
}

void FileFactory::changeFile(const std::string & fileName) {
    if (file.is_open()) {
        file.close();
    }
    
    file.open(fileName);
    
    if (!file.is_open()) {
        throw((const std::string)"Failed to open file");
    }
    
}

void FileFactory::incorrectLineCheck(const bool & toCheck, const int & line) {
    if (toCheck) {
        throw((const std::string)"Incorrect input at line: " + std::to_string(line));
    }
}

void FileFactory::loadDatabaseSettings(std::string & ip, std::string & username, std::string & password) {
    if (!file.is_open()) {
        throw ((const std::string)"File is not open");
    }
    
    file >> input;   
    incorrectLineCheck(input != "IP:", __LINE__);
    file >> ip;
    incorrectLineCheck(ip == "", __LINE__);
    file >> input;
    incorrectLineCheck(input != "USERNAME:", __LINE__);
    file >> username;
    incorrectLineCheck(username == "", __LINE__);
    file >> input;
    incorrectLineCheck(input != "PASSWORD:", __LINE__);
    file >> password;
    incorrectLineCheck(password == "", __LINE__);
}
