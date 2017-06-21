/**
 * \file
 * \brief     Library for executing query on a rfid database
 * \author    Jeremy Ruizenaar
 * \copyright Copyright (c) 2017, The R2D2 Team
 * \license   See LICENSE
 */
#include "database-manager.hh"

void DatabaseManager::connectTo(const std::string &ip, const std::string &username,
                                const std::string &password) {
    connection.connectTo(ip, username, password);
}

void DatabaseManager::selectDatabase(const std::string &database) {
    connection.selectDatabase(database);
}

std::string DatabaseManager::getAllCardIdFromDatabase() {
    connection.executeQuery("SELECT CARD_ID FROM RFID");
    std::string res;
    while (connection.getFullResult()->next()) {
        res.append(connection.getFullResult()->getString("CARD_ID"));
        res += '\n';
    }
    return res;
}

bool DatabaseManager::getCardAuthorisationFromDatabase(const std::string &cardId) {

    // format the sql query string
    std::string query;
    query += "SELECT AUTHORIZED FROM RFID WHERE CARD_ID = '";
    query += cardId + "\\";

    connection.executeQuery(query);
    std::string result = connection.getPreviousResponseColumn("AUTHORIZED");
    // if result was 1 return false
    return !result.compare("1");
}

void DatabaseManager::setCardAuthorisationInDatabase(const bool &status,
                                                     const std::string &cardId) {
    // format the sql query string
    std::string query;
    query += "UPDATE RFID SET AUTHORIZED = '";

    if (status) {
        query += '1';
    } else {
        query += '0';
    }

    query += "' WHERE RFID.CARD_ID = '";
    query += cardId + "\\";

    connection.executeQueryNoResult(query);
}

bool DatabaseManager::addCardToDatabase(const std::string &cardId) {

    // check if card id is already in the database
    if (!isCardInDatabase(cardId)) {
        return false;
    }
    // format the sql query string
    std::string query;
    query += "INSERT INTO RFID (CARD_ID, AUTHORIZED) VALUES (\'";
    query += cardId;
    query += "\', 0)";

    connection.executeQueryNoResult(query);
    return true;
}

bool DatabaseManager::isCardInDatabase(const std::string &cardId) {

    // format the sql query string
    std::string query;
    query += "SELECT CARD_ID FROM RFID WHERE EXISTS ( SELECT CARD_ID FROM RFID "
        "WHERE CARD_ID =\'";
    query += cardId;
    query += "\')";

    connection.executeQuery(query);

    // if there is a result the card is already in the database
    return !connection.getFullResult()->next();
}

void DatabaseManager::executeQueryNoResult(const std::string &query) {
    connection.executeQueryNoResult(query);
}

void DatabaseManager::executeQuery(const std::string &query) {
    connection.executeQuery(query);
}

std::unique_ptr<sql::ResultSet> &DatabaseManager::getFullResultSet() {
    return connection.getFullResult();
}
