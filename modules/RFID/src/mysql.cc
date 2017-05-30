/**
 * \file      mysql.cc
 * \brief     Mysql library with error checking that uses the mysqlcppconn library
 * \author    Tim IJntema
 * \copyright Copyright (c) 2017, The R2D2 Team
 * \license   See LICENSE
 */

#include "mysql.hh"

MySql::MySql(){
    driver = get_driver_instance();
}

MySql::~MySql(){
    delete result;
    delete statement;
    delete connection;
}

template <typename T>
bool MySql::errorCheck(T function){
    try{
        function();
    } catch (sql::SQLException & error) {
        std::cerr << "MySQL error code: " << error.getErrorCode()
                  << ", SQLState: " << error.getSQLState() << '\n';
        return false;
    }
    return true;
}

bool MySql::connectTo(std::string url, std::string username, std::string password){
    return errorCheck([&](){
        connection = driver->connect(url.c_str(), username.c_str(), password.c_str());
        statement = connection->createStatement();
    });
}

bool MySql::selectDatabase(std::string databaseName){
    return errorCheck([&](){
        connection->setSchema(databaseName.c_str());
    });   
}

bool MySql::executeQuery(std::string query){
    return errorCheck([&](){
        result = statement->executeQuery(query.c_str());
    });
}

bool MySql::executeQueryNoResult(std::string query){
    return errorCheck([&](){
        statement->execute(query.c_str());
    });
}

std::string MySql::getPreviousResponseColumn(unsigned int columnNumber){
    std::string columnInformation = "";
    bool hasWorked = errorCheck([&](){
        if(result->next()){
            columnInformation = result->getString(columnNumber);
        }
    });
    
    if(!hasWorked){
        result->previous();
    }
    return columnInformation;
}

std::string MySql::getPreviousResponseColumn(std::string columnName){
    std::string columnInformation = "";
    bool hasWorked = errorCheck([&](){
        if(result->next()){
            columnInformation = result->getString(columnName);
        }
    });
    
    if(!hasWorked){
        result->previous();
    }
    return columnInformation;
}

sql::ResultSet * MySql::getFullResult(){
    return result;
}
