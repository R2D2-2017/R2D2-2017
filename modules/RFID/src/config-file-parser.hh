/**
 * \file      file-factory.hh
 * \brief     Library for getting information out of a file
 * \author    Tim IJntema
 * \copyright Copyright (c) 2017, The R2D2 Team
 * \license   See LICENSE
 */

#pragma once

#include <string>
#include <fstream>
#include <stdexcept>

/**
 * \brief Factory class for files
 *
 * This class handles file input using c++ ifstream. It can be used to read
 *  information from a file with settings. Closing files and opening them is
 *  handeled in the class.
 */
class ConfigFileParser {
private:
    std::string nameCurrentFile;
    int lineCurrentFile;
    std::ifstream file;
    std::string input;
    
    /**
     * \brief Checks for errors when executing a statement
     *
     * If an error occurs, an incorrect line error will be thrown in the form of
     *  a const std::string. The line the error occured at should be given to the
     *  function.
     *
     * Typical usage:
     * \code
     *     incorrectLinCheck(true == true, __LINE__);
     * \endcode
     *
     * \param [in] toCheck A comparrison with a boolean type as result
     * \param [in] line The line the error occured on
     */
    void incorrectLineCheck(const bool & toCheck, const std::string & fileName, int line);
    
    /**
     * \brief Checks if the file is open
     *
     * If the file is not open an error is returned using throw in the form of a
     *  const std::string. This function can be used to check if the file is open
     *  before you try to read something from it.
     *
     * Typical usage:
     * \code
     *     fileOpenCheck();
     * \endcode
     */
    void fileOpenCheck();
public:
    /**
     * \brief Constructor with filename
     * 
     * Calls the ConfigFileParser::changeFile() function to open the file.
     *
     * Typical usage:
     * \code
     *     ConfigFileParser factory("filename.txt");
     * \endcode
     *
     * \param [in] fileName The name of the file to open
     */
    ConfigFileParser(const std::string & fileName);
    
    /**
     * \brief Destructor
     *
     * Closes the file when called
     */
    ~ConfigFileParser();
    
    /**
     * \brief Change the current file
     *
     * This functions checks if a file is open. If it is it will be closed.
     * The new file will then be opened. Throws a const std::string error when
     *  something goes wrong with opening the file.
     *
     * Typical usage:
     * \code
     *     changeFile("filename.txt");
     * \endcode
     *
     * \param [in] fileName The name of the file to open
     */
    void changeFile(const std::string & fileName);
    
    /**
     * \brief Load the database ip, password and username from a file
     *
     * If an error occurs, a const std::string will be thrown with the line the
     *  error occured on.
     *
     * Typical usage:
     * \code
     *     std::string ip;
     *     std::string username;
     *     std::string password;
     *     loadDatabaseSettings(ip, username, password);
     * \endcode
     *
     * \param [out] ip The ip to be read from the file
     * \param [out] username The username to be read from the file
     * \param [out] password The password to be read from the file
     */
    void loadDatabaseSettings(std::string & ip, std::string & username, std::string & password);
    
    /**
     * \brief Load the encryption key from a file
     *
     * If an error occurs, a const std::string will be thrown with the line the
     *  error occured on.
     *
     * Typical usage:
     * \code
     *     int encryptionKey;
     *     loadDatabaseSettings(encryptionKey);
     * \endcode
     *
     * \param [out] encryptionKey The encryption key to be read from the file
     */
    void loadEncryptionSettings(int & encryptionKey);
};
