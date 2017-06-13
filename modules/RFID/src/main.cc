/**
* \file      main.cc
* \brief     Program for giving an indication when a rfid card has been detected, a database connection has been made and a string has been encrypted
* \author    Tim IJntema, Stefan de Beer, Arco Gelderblom, Rik Honcoop, Koen de Groot
* \copyright Copyright (c) 2017, The R2D2 Team
* \license   See LICENSE
*/

#include "mysql.hh"
#include "mfrc522.hh"
#include "led-controller.hh"
#include "matrix-keypad.hh"
#include "config-file-parser.hh"

#include <wiringPi.h>
#include <wiringPiSPI.h>

#include <iostream>

struct MFAuthentData {
    uint8_t command_code;
    uint8_t blockAddress;
    uint8_t sectorKey[5];
    uint8_t serialNumber[4];
};

int main(int argc, char **argv) {
    try {
        std::string ip;
        std::string username;
        std::string password;
        int encryptionKey;

        ConfigFileParser factory("database-config.txt");
        factory.loadDatabaseSettings(ip, username, password);

        MySql connection;

        connection.connectTo(ip, username, password);
        connection.selectDatabase("R2D2");

        std::cout << "Made connection to the database\n";
        wiringPiSetup();
        wiringPiSPISetup(0, 10000000);//max speed for mfrc522 is 10Mhz
        Mfrc522 rfid;
        rfid.init();

        //Keypad pinSetup
        const int keypadRow[] = {4, 1, 16, 15};
        const int keypadColumn[] = {2, 7, 9, 8};

        //Keypad objects
        MatrixKeypad keypad(keypadRow, keypadColumn, 4);
        char c;

        LedController led(0);

        while (true) {
            std::cout << "\n\nWaiting for rfid tag: \n";

            while (!rfid.isTagPresent()) {
            }
            MFAuthentData x;
            uint8_t receiveData[64];
            rfid.communicateWithTag(Mfrc522::mfrc522Commands::receive,
                                    nullptr,
                                    0,
                                    receiveData,
                                    64*8);
//            rfid.communicateWithTag(Mfrc522::mfrc522Commands::mfAuthent, nullptr, 0, nullptr, 0);

            std::cout << "Hello tag\n";
            std::cout << "Your id = ";
            for(size_t i = 0; i < 4; i++){
                std::cout << std::hex << receiveData[0];
            }
            std::cout << "\n";

            std::cout << "Waiting for key press\n";
            while ((c = keypad.getKey()) == 'h') {
                delay(100);
            }

            //c = keypad.getKey();
            std::cout << c << " key has been pressed\n";

            connection.executeQuery("SELECT * FROM RFID");

            std::cout << "Database information: "
                      << connection.getPreviousResponseColumn("CARD_ID")
                      << '\n';

            std::cout << "String before encryption: R2D2 project\n";
            std::cout << "String after encryption: "
                      << '\n';

            led.blinkLed(1000);
        }
    } catch (const std::string &error) {
        std::cerr << error << '\n';
        exit(EXIT_FAILURE);
    } catch (...) {
        std::cerr << "Something went wrong\n";
        exit(EXIT_FAILURE);
    }
    return 0;
}

