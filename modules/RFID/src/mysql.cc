//===-- mysql.cc - MySql class definition -------*- C++ -*-===//
//
//                     The R2D2 Compiler Infrastructure
//
// This file is distributed under the R2D2 Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
///
/// \file
/// This file contains the definition of the MySql class. It handles all mysql
///  database connectivity.
///
//===----------------------------------------------------------------------===//

#include "mysql.hh"

MySql::MySql(){
    driver = get_driver_instance();
}

MySql::~MySql(){
    delete res;
    delete stmt;
    delete con;
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
        con = driver->connect(url.c_str(), username.c_str(), password.c_str());
        stmt = con->createStatement();
    });
}

bool MySql::selectDatabase(std::string databaseName){
    return errorCheck([&](){
        con->setSchema(databaseName.c_str());
    });   
}

bool MySql::executeQuery(std::string query){
    return errorCheck([&](){
        res = stmt->executeQuery(query.c_str());
    });
}

bool MySql::executeQueryNoResult(std::string query){
    return errorCheck([&](){
        stmt->execute(query.c_str());
    });
}

std::string MySql::getPreviousResponseColumn(unsigned int columnNumber){
    std::string columnInformation = "";
    bool has_worked = errorCheck([&](){
        if(res->next()){
            columnInformation = res->getString(columnNumber);
        }
    });
    
    if(!has_worked){
        res->previous();
    }
    return columnInformation;
}

std::string MySql::getPreviousResponseColumn(std::string columnName){
    std::string columnInformation = "";
    bool has_worked = errorCheck([&](){
        if(res->next()){
            columnInformation = res->getString(columnName);
        }
    });
    
    if(!has_worked){
        res->previous();
    }
    return columnInformation;
}

sql::ResultSet * MySql::getFullResult(){
    return res;
}