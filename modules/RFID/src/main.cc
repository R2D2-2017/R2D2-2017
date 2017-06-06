/**
 * \file
 * \brief     Using the MySql library to make a database connection and get a echo.
 * \author    Tim IJntema
 * \copyright Copyright (c) 2017, The R2D2 Team
 * \license   See LICENSE
 */
 
#include "mysql.hh"
#include "config-file-parser.hh"
 
#include <iostream>

int main(int argc, char **argv) {
    try {
        std::string ip;
        std::string username;
        std::string password;
        
        ConfigFileParser factory("database-config.txt");
        
        factory.loadDatabaseSettings(ip, username, password);
        
        MySql connection;

        connection.connectTo(ip, username, password);
        connection.selectDatabase("R2D2");
        connection.executeQuery("SELECT * FROM RFID");
        
        auto & result = connection.getFullResult();
        while (result->next()) {
            std::cout << "Card ID: " << result->getString(2) << '\n';
        }
    } catch(const std::string & error) {
        std::cerr << error << '\n';
        exit(EXIT_FAILURE);
    } catch(...) {
        std::cerr << "something went wrong\n";
        exit(EXIT_FAILURE);
    }

    return 0;
}

