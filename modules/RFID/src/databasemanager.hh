//
// Created by jeremy on 17-6-17.
//

#ifndef TEMPLATE_PC_DATABASEMANAGER_HH
#define TEMPLATE_PC_DATABASEMANAGER_HH

#include "mysql.hh"

class databasemanager {
private:
    MySql  connection;

public:

    void connectTo(std::string ip, std::string username, std::string password);
    void selectDatabase(std::string database);

    std::string getAllCardIdFromDatabase();

    std::string getCardAuthorisationFromDatabase(std::string cardId);
    void setCardAuthorisationInDatabase(bool status, std::string cardId);

    bool isCardInDatabase(std::string cardId);
    bool addCardToDatabase( std::string cardId);

    void executeQueryNoResult( std::string query );
    void executequery(std::string query);
    std::unique_ptr<sql::ResultSet> & getFullResultSet();

    void addEmployeeToDatabase(std::string name, std::string function, std::string adress,
        std::string postalcode, std::string street, std::string city);


};


#endif //TEMPLATE_PC_DATABASEMANAGER_HH
