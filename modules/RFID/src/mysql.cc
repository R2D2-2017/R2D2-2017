/**
 * \file      mysql.cc
 * \brief     Mysql class with error checking that uses the mysqlcppconn
 * library
 * \author    Tim IJntema
 * \copyright Copyright (c) 2017, The R2D2 Team
 * \license   See LICENSE
 */

#include "mysql.hh"

MySql::MySql() { driver = get_driver_instance(); }

MySql::~MySql() {}

template <typename T> void MySql::errorCheck(T function) {
    try {
        function();
    } catch (sql::SQLException &error) {
        std::cerr << "MySQL error code: " << error.getErrorCode()
                  << ", SQLState: " << error.getSQLState() << '\n';
        throw;
    }
}

void MySql::connectTo(const std::string &url, const std::string &username,
                      const std::string &password) {
    errorCheck([&]() {
        connection = std::unique_ptr<sql::Connection>(
            driver->connect(url.c_str(), username.c_str(), password.c_str()));
        statement =
            std::unique_ptr<sql::Statement>(connection->createStatement());
    });
}

void MySql::selectDatabase(const std::string &databaseName) {
    errorCheck([&]() { connection->setSchema(databaseName.c_str()); });
}

void MySql::executeQuery(const std::string &query) {
    errorCheck([&]() { result.reset(statement->executeQuery(query.c_str())); });
}

void MySql::executeQueryNoResult(const std::string &query) {
    errorCheck([&]() { statement->execute(query.c_str()); });
}

std::string MySql::getPreviousResponseColumn(const unsigned int &columnNumber) {
    std::string columnInformation;

    errorCheck([&]() {
        if (result->next()) {
            columnInformation = result->getString(columnNumber);
        }
    });

    return columnInformation;
}

std::string MySql::getPreviousResponseColumn(const std::string &columnName) {
    std::string columnInformation;

    errorCheck([&]() {
        if (result->next()) {
            columnInformation = result->getString(columnName);
        }
    });

    return columnInformation;
}

std::unique_ptr<sql::ResultSet> MySql::getFullResult() { return std::move(result); }
