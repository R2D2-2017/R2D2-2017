/**
 * \file      config-file-parser.hh
 * \brief     Library for getting information out of a file
 * \author    Tim IJntema, Jeremy Ruizenaar, Ricardo Bouwman
 * \copyright Copyright (c) 2017, The R2D2 Team
 * \license   See LICENSE
 */

#pragma once

#include <fstream>
#include <stdexcept>
#include <string>

/**
 * \brief Factory class for files
 *
 * This class handles file input using c++ ifstream. It can be used to read
 *  information from a file with settings. Closing files and opening them is
 *  handled in the class.
 */
class ConfigFileParser {
  private:
    const std::string databaseFile;

    /**
     * \brief Checks for errors when executing a statement
     *
     * If an error occurs, an incorrect line error will be thrown in the form of
     *  a const std::string. The line the error ocurred at should be given to
     * the
     *  function.
     *
     * Typical usage:
     * \code
     *     incorrectLinCheck(true == true, __LINE__);
     * \endcode
     *
     * \param [in] toCheck A comparison with a boolean type as result
     * \param [in] line The line the error occurred on
     */
    void incorrectLineCheck(const bool &toCheck, const std::string &fileName,
                            int line);

  public:
    /**
     * \brief Constructor with file names
     *
     * constructs the configFileParser
     *
     * Typical usage:
     * \code
     *     ConfigFileParser factory("filename1.txt", "filename2.txt");
     * \endcode
     *
     * \param [in] databaseFile   The name of the file to open
     * \param [in] encryptionFile The name of the file to open
     */
    ConfigFileParser(const std::string &databaseFile);

    /**
     * \brief Load the database ip, password and username from a file
     *
     * If an error occurs, a const std::string will be thrown with the line the
     *  error occurred on.
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
    void loadDatabaseSettings(std::string &ip, std::string &username,
                              std::string &password);
};
