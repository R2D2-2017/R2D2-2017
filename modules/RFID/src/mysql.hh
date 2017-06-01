/**
<<<<<<< HEAD
 * \file      mysql.hh
=======
 * \file
>>>>>>> origin/feat-rfid-database
 * \brief     Mysql library with error checking that uses the mysqlcppconn library
 * \author    Tim IJntema
 * \copyright Copyright (c) 2017, The R2D2 Team
 * \license   See LICENSE
 */

#pragma once

#include "mysql_connection.h"

#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>

#include <string>


/**
 * \brief Sql class with error checking
 *
 * This class uses the mysqlcppconn library to connect to a mysql database.
 * This library by itself dus not have error handling, therefore that is beeing
 *  handled in this class. The class also minimizes the amount of work a 
 * programmer has to do by automatically deleting the variables after use and
 *  calling any functions that always have to be called and do not need input 
 * information. 
 */
class MySql{
private:
    sql::Driver * driver;
<<<<<<< HEAD
    sql::Connection * connection;
    sql::Statement * statement;
    sql::ResultSet * result;
=======
    sql::Connection * con;
    sql::Statement * stmt;
    sql::ResultSet * res;
>>>>>>> origin/feat-rfid-database
    
    
    /// Checks for errors when executing function of template type T.
    ///
    /// If an error occurs, the mysql state and error code will be printed.
    ///
    /// Typical usage:
    /// \code
    ///     errorCheck([](){
    ///         //statements to execute
    ///     });
    /// \endcode
    ///
    /// \param [in] function The function to run of template type T
    ///
    /// \returns true on success.
    template <typename T>
    bool errorCheck(T function);
    
public:
    /// Constructs the mysql class
    ///
    /// Typical usage:
    /// \code
    ///     MySql connection;
    /// \endcode
    MySql();
    
    
    /// Destructs the mysql class
    ~MySql();
    
    
    /// Connects to a mysql server
    ///
    ///
    /// Typical usage:
    /// \code
    ///     connectTo("tcp://192.168.2.50:3306", "R2D2", "BB8");
    /// \endcode
    ///
    /// \param [in] url The url of the server
    /// \param [in] username The username used to log in
    /// \param [in] password The password used to log in
    ///
    /// \returns true on success.
    bool connectTo(std::string url, std::string username, std::string password);
    
    
    /// Selects a database
    ///
    /// Typical usage:
    /// \code
    ///     selectDatabase("R2D2");
    /// \endcode
    ///
    /// \param [in] databaseName The database to select
    ///
    /// \returns true on success.
    bool selectDatabase(std::string databaseName);
    
    
    /// Executes a query and stores the results in a variable
    ///
    /// Typical usage:
    /// \code
    ///     executeQuery("SELECT * FROM RFID");
    /// \endcode
    ///
    /// \param [in] query The query to execute
    ///
    /// \returns true on success.
    bool executeQuery(std::string query);
    
    
    /// Executes a query where there is no data to be received
    ///
    /// Typical usage:
    /// \code
    ///     executeQueryNoResult( "INSERT INTO RFID (CARD_ID) VALUES ('[51,187,188,221,233]')" );
    /// \endcode
    ///
    /// \param [in] query The query to execute
    ///
    /// \returns true on success.
    bool executeQueryNoResult(std::string query);
    
    
    /// Can be used to grab the result of a previous query by column number
    ///
    /// Does not return the result if there is no result left. In that case it
    ///  returns an empty string.
    ///
    /// Typical usage:
    /// \code
    ///     getPreviousResponseColumn(2);
    /// \endcode
    ///
    /// \param [in] columnNumber The number of the column to get
    ///
    /// \returns The result from the database
    std::string getPreviousResponseColumn(unsigned int columnNumber);
    
    
    /// Can be used to grab the result of a previous query by column name
    ///
    /// Does not return the result if there is no result left. In that case it
    ///  returns an empty string.
    ///
    /// Typical usage:
    /// \code
    ///     getPreviousResponseColumn("CARD_ID");
    /// \endcode
    ///
    /// \param [in] columnName The name of the requested column 
    ///
    /// \returns The result from the database
    std::string getPreviousResponseColumn(std::string columnName);
    
    
    /// Get the full result from the previous sql query
    ///
    /// Typical usage:
    /// \code
    ///     getFullResult();
    /// \endcode
    ///
    /// \returns The full result with all columns and rows
    sql::ResultSet * getFullResult();
};
