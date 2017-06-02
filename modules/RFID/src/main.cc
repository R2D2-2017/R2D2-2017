/**
 * \file
 * \brief     Using the MySql library to make a database connection and get a echo.
 * \author    Tim IJntema
 * \copyright Copyright (c) 2017, The R2D2 Team
 * \license   See LICENSE
 */
 
#include "mysql.hh"
 
#include <iostream>

int main(int argc, char **argv) {
    try {
        MySql connection;

        connection.connectTo("192.168.2.50", "R2D2", "BB8");
        connection.selectDatabase("R2D2");
        connection.executeQuery("SELECT * FROM RFID");
        
        auto & result = connection.getFullResult();
        while(result->next()){
            std::cout << "Card ID: " << result->getString(2) << '\n';
        }
    } catch(...) {
        std::cout << "something went wrong\n";
        exit(0);
    }

    return 0;
}

