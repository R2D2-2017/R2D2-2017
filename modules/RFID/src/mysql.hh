/**
 * \file      mysql.hh
 * \brief     Mysql library with error checking that uses the mysqlcppconn library
 * \author    Tim IJntema
 * \copyright Copyright (c) 2017, The R2D2 Team
 * \license   See LICENSE
 */

#pragma once

#include <mysql_connection.h>

#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>

#include <memory>
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
class MySql {
private:
    /*
     * \brief Can not be a smart pointer
     *
     * This variable can not be a smart pointer due to the smart pointers needing
     *  a destructor to call. The destructor of sql::Driver is protected and therefore
     *  cannot be reached.
     */
    sql::Driver * driver;
    std::unique_ptr<sql::Connection> connection;
    std::unique_ptr<sql::Statement> statement;
    std::unique_ptr<sql::ResultSet> result;
    
    
    /**
     * \brief Checks for errors when executing function of template type T.
     *
     * If an error occurs, the mysql state and error code will be printed.
     *
     * Typical usage:
     * \code
     *     errorCheck([](){
     *         //statements to execute
     *     });
     * \endcode
     *
     * \param [in] function The function to run of template type T
     *
     * \returns true on success.
     */
    template <typename T>
    void errorCheck(T function);
    
    
public:
    /**
     * \brief Constructs the mysql class
     *
     * Typical usage:
     * \code
     *     MySql connection;
     * \endcode
     */
    MySql();
    
    
    /**
     *  \brief Destructs the mysql class
     */
    ~MySql();
    
    
    /**
     * \brief Connects to a mysql server
     *
     *
     * Typical usage:
     * \code
     *     connectTo("tcp://someip:3306", "username", "password");
     * \endcode
     *
     * \param [in] url The url of the server
     * \param [in] username The username used to log in
     * \param [in] password The password used to log in
     *
     * \returns true on success.
     */
    void connectTo(const std::string & url, const std::string & username, const std::string & password);
    
    
    /**
     * \brief Selects a database
     *
     * Typical usage:
     * \code
     *     selectDatabase("database");
     * \endcode
     *
     * \param [in] databaseName The database to select
     *
     * \returns true on success.
     */
    void selectDatabase(const std::string & databaseName);
    
    
    /**
     * \brief Executes a query and stores the results in a variable
     *
     * Typical usage:
     * \code
     *     executeQuery("SELECT * FROM sometable");
     * \endcode
     *
     * \param [in] query The query to execute
     *
     * \returns true on success.
     */
    void executeQuery(const std::string & query);
    
    
    /**
     * \brief Executes a query where there is no data to be received
     *
     * Typical usage:
     * \code
     *     executeQueryNoResult( "INSERT INTO sometable (column1, column2, column3) VALUES ('set', 'of', 'values')" );
     * \endcode
     *
     * \param [in] query The query to execute
     *
     * \returns true on success.
     */
    void executeQueryNoResult(const std::string & query);
    
    
    /**
     * \brief Can be used to grab the result of a previous query by column number
     *
     * Does not return the result if there is no result left. In that case it
     *  returns an empty string.
     *
     * Typical usage:
     * \code
     *     getPreviousResponseColumn(2);
     * \endcode
     *
     * \param [in] columnNumber The number of the column to get
     *
     * \returns The result from the database
     */
    std::string getPreviousResponseColumn(const unsigned int & columnNumber);
    
    
    /**
     * \brief Can be used to grab the result of a previous query by column name
     *
     * Does not return the result if there is no result left. In that case it
     *  returns an empty string.
     *
     * Typical usage:
     * \code
     *     getPreviousResponseColumn("CARD_ID");
     * \endcode
     *
     * \param [in] columnName The name of the requested column 
     *
     * \returns The result from the database
     */
    std::string getPreviousResponseColumn(const std::string & columnName);
    
    
    /**
     * \brief Get the full result from the previous sql query
     *
     * Typical usage:
     * \code
     *     getFullResult();
     * \endcode
     *
     * \returns The full result with all columns and rows
     */
    std::unique_ptr<sql::ResultSet> & getFullResult();
};
