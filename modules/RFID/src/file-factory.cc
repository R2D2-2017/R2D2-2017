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

void FileFactory::incorrectLineCheck(const bool & toCheck, const std::string & fileName, const int & line) {
    if (toCheck) {
        throw((const std::string)"Incorrect input"
                + "\nFunction call in file: " + fileName + " line: " + std::to_string(line)
                + "\nWhile reading from: " + nameCurrentFile + " line: " + std::to_string(lineCurrentFile));
    }
}

/**
 * \brief Reducing the amount of arguments needed to call incorrectLineCheck
 */
#define incorrectLineCheck(toCheck) incorrectLineCheck(toCheck, __FILE__, __LINE__)

void FileFactory::fileOpenCheck(){
    if (!file.is_open()) {
        throw ((const std::string)"File is not open");
    }
}

void FileFactory::changeFile(const std::string & fileName) {
    if (file.is_open()) {
        file.close();
    }
    
    file.open(fileName);
    
    if (!file.is_open()) {
        throw((const std::string)"Failed to open file with name: " + fileName);
    }
    nameCurrentFile = fileName;
    lineCurrentFile = 1;
    
}

void FileFactory::loadDatabaseSettings(std::string & ip, std::string & username, std::string & password) {
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
    incorrectLineCheck(password == "\n");
    ++lineCurrentFile;
    
    if (ip.empty() || username.empty() || password.empty()) {
        throw("Missing input after reading file: " + nameCurrentFile);
    }
}

void FileFactory::loadEncryptionSettings(int & encryptionKey){
    fileOpenCheck();
    
    file >> input;
    incorrectLineCheck(input != "KEY:");
    file >> encryptionKey;
    incorrectLineCheck(encryptionKey == (int)"\n");
    ++lineCurrentFile;
    
    if (!encryptionKey) {
        throw("Missing input after reading file: " + nameCurrentFile);
    }
}