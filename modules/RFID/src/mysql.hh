//===-- mysql.hh - MySql class declaration -------*- C++ -*-===//
//
//                     The R2D2 Compiler Infrastructure
//
// This file is distributed under the R2D2 Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
///
/// \file
/// This file contains the declaration of the MySql class. It handles all mysql
///  database connectivity.
///
//===----------------------------------------------------------------------===//

#pragma once

#include "mysql_connection.h"

#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>

#include <string>
#include <functional>

class MySql{
private:
    sql::Driver * driver;
    sql::Connection * con;
    sql::Statement * stmt;
    sql::ResultSet * res;
    
    
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
    /// \param [in] function of template type T
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
    /// \param [in] The url of the server
    /// \param [in] The username used to log in
    /// \param [in] The password used to log in
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
    /// \param [in] The database to select
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
    /// \param [in] The query to execute
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
    /// \param [in] The query to execute
    ///
    /// \returns true on success.
    bool executeQueryNoResult(std::string query);
    
    
    
    
    
    /*
     Maybe test what hapens when you do not call res->next();
     */
    
    
    
    
    /// Returns the result of a previous run query
    ///
    /// Does not return the result if there is no result left. In that case it
    ///  returns an empty string.
    ///
    /// Typical usage:
    /// \code
    ///     getPreviousResponseColumn(2);
    /// \endcode
    ///
    /// \param [in] The number of the column to get
    ///
    /// \returns The result from the database
    std::string getPreviousResponseColumn(int columnNumber);
    
    
    /// Does foo and bar.
    ///
    /// Does not do foo the usual way if \p Baz is true.
    ///
    /// Typical usage:
    /// \code
    ///   fooBar(false, "quux", Res);
    /// \endcode
    ///
    /// \param Quux kind of foo to do.
    /// \param [out] Result filled with bar sequence on foo success.
    ///
    /// \returns true on success.
    std::string getPreviousResponseColumn(std::string columnName);
    
    
    /// Does foo and bar.
    ///
    /// Does not do foo the usual way if \p Baz is true.
    ///
    /// Typical usage:
    /// \code
    ///   fooBar(false, "quux", Res);
    /// \endcode
    ///
    /// \param Quux kind of foo to do.
    /// \param [out] Result filled with bar sequence on foo success.
    ///
    /// \returns true on success.
    sql::ResultSet * getFullResult();
};
