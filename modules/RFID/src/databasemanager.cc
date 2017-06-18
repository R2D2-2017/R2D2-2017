//
// Created by jeremy on 17-6-17.
//



#include "databasemanager.hh"
#include <iostream>



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

std::string databasemanager::getCardAuthorisationFromDatabase(std::string cardId) {

    std::string query;
    query += "SELECT AUTHORIZED FROM RFID WHERE CARD_ID = '";
    query += cardId += '\'';

    std::cout<< query << '\n';

    connection.executeQuery(query);
    return connection.getPreviousResponseColumn("AUTHORIZED");
}

void databasemanager::setCardAuthorisationInDatabase(bool status, std::string cardId) {

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

void databasemanager::executeQueryNoResult(std::string query) {
    connection.executeQueryNoResult(query);
}

void  databasemanager::executequery(std::string query) {
    connection.executeQuery(query);

}
std::unique_ptr<sql::ResultSet> &  databasemanager::getFullResultSet(){
    return connection.getFullResult();
}

bool databasemanager::addCardToDatabase(std::string cardId) {

    if(!isCardInDatabase(cardId)){ return false; }

    std::string query;
    query += "INSERT INTO RFID (CARD_ID, AUTHORIZED) VALUES (\'";
    query += cardId;
    query += "\', 0)";

    std::cout << query << '\n';
    connection.executeQueryNoResult(query);
    return true;

}

bool databasemanager::isCardInDatabase(std::string cardId) {

    std::string query;
    query += "SELECT CARD_ID FROM RFID WHERE EXISTS ( SELECT CARD_ID FROM RFID WHERE CARD_ID =\'";
    query += cardId;
    query += "\')";
    std::cout <<query << "\n";
    connection.executeQuery(query);

    if(connection.getFullResult()->next()){
        return false;
    }
    else{
        return true;
    }
}
