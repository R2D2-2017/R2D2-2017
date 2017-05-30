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
    MySql connection;

    if(!connection.connectTo("192.168.2.50", "R2D2", "BB8")){
        std::cout << "Can not connect\n";
        exit(0);
    }
    
    if(!connection.selectDatabase("R2D2")){
        std::cout << "Database unknown\n";
        exit(0);
    }
    
    if(!connection.executeQuery("SELECT * FROM RFID")){
        std::cout << "Can not execute query\n";
        exit(0);
    }
    
    sql::ResultSet * result = connection.getFullResult();
    while(result->next()){
        std::cout << "Card ID: " << result->getString(2) << '\n';
    }

    return 0;
}
