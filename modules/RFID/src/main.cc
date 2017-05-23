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
        std::cerr << "Can not connect\n";
        exit(0);
    }
    
    if(!connection.selectDatabase("R2D2")){
        std::cerr << "Database unknown\n";
        exit(0);
    }
    
    if(!connection.executeQuery("SELECT * FROM RFID")){
        std::cerr << "Can not execute query\n";
        exit(0);
    }
    
    sql::ResultSet * result = connection.getFullResult();
    while(result->next()){
        std::cerr << "Card ID: " << result->getString(2) << '\n';
        exit(0);
    }
    
    if(!connection.executeQueryNoResult("INSERT INTO RFID (CARD_ID) VALUES ('[51,187,188,221,234]')")){
        std::cerr << "Failed to insert data\n";
        exit(0);
    }

    return 0;
}
