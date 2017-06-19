/**
 * \file      databasemanager.hh
 * \brief     Library for executing query on a rfid database
 * \author    Jeremy Ruizenaar
 * \copyright Copyright (c) 2017, The R2D2 Team
 * \license   See LICENSE
 */
#include "databasemanager.hh"


void databasemanager::connectTo(std::string ip, std::string username, std::string password) {
    connection.connectTo(ip, username, password);
}

void databasemanager::selectDatabase(std::string database) {
    connection.selectDatabase(database);
}

std::string databasemanager::getAllCardIdFromDatabase() {
    connection.executeQuery("SELECT CARD_ID FROM RFID");
    std::string res;
    while(connection.getFullResult()->next()){
        res.append(connection.getFullResult()->getString("CARD_ID"));
        res += '\n';
    }
    return res;
}

bool databasemanager::getCardAuthorisationFromDatabase(std::string cardId) {

    //format the sql query string
    std::string query;
    query += "SELECT AUTHORIZED FROM RFID WHERE CARD_ID = '";
    query += cardId += '\'';

    std::cout<< query << '\n';

    connection.executeQuery(query);
    std::string result = connection.getPreviousResponseColumn("AUTHORIZED");
    // if result was 1 return false
    if(result.compare("1")){
        return false;
    }
    else{
        return true;
    }

}

void databasemanager::setCardAuthorisationInDatabase(bool status, std::string cardId) {

    //format the sql query string
    std::string query;
    query += "UPDATE RFID SET AUTHORIZED = '";

    if(status){
        query += '1';
    }
    else{
        query += '0';
    }

    query += "' WHERE RFID.CARD_ID = '";
    query += cardId += '\'';

    std::cout<< query << '\n';
    connection.executeQueryNoResult(query);
}

bool databasemanager::addCardToDatabase(std::string cardId) {

    // check if card id is already in the database
    if(!isCardInDatabase(cardId)){ return false; }
    //format the sql query string
    std::string query;
    query += "INSERT INTO RFID (CARD_ID, AUTHORIZED) VALUES (\'";
    query += cardId;
    query += "\', 0)";

    std::cout << query << '\n';
    connection.executeQueryNoResult(query);
    return true;
}

bool databasemanager::isCardInDatabase(std::string cardId) {

    //format the sql query string
    std::string query;
    query += "SELECT CARD_ID FROM RFID WHERE EXISTS ( SELECT CARD_ID FROM RFID WHERE CARD_ID =\'";
    query += cardId;
    query += "\')";
    std::cout <<query << "\n";
    connection.executeQuery(query);

    // if there is a result the card is already in the database
    if(connection.getFullResult()->next()){
        return false;
    }
    else{
        return true;
    }
}

void databasemanager::executeQueryNoResult(std::string query) {
    connection.executeQueryNoResult(query);
}

void  databasemanager::executeQuery(std::string query) {
    connection.executeQuery(query);
}

std::unique_ptr<sql::ResultSet> &  databasemanager::getFullResultSet(){
    return connection.getFullResult();
}




