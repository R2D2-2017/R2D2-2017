/**
* \file      main.cc
* \brief     Program for giving an indication when a rfid card has been
* detected, a database connection has been made and a string has been encrypted
* \author    Tim IJntema, Stefan de Beer, Arco Gelderblom, Rik Honcoop, Koen de
* Groot, Ricardo Bouwman, Philippe Zwietering, Luuk Steeman, Leo Jenneskens,
* Jeremy Ruijzenaars
* \copyright Copyright (c) 2017, The R2D2 Team
* \license   See LICENSE
*/

#include "config-file-parser.hh"
#include "databasemanager.hh"
#include "led-controller.hh"
#include "matrix-keypad.hh"
#include "mfrc522.hh"
#include "mysql.hh"

#include <wiringPiSPI.h>

#include <iomanip>

int main(int argc, char **argv) {
#define USING_PIN // Comment out this rule if not using a pincode on your
                  // application
    try {

        std::string ip;
        std::string username;
        std::string password;

        ConfigFileParser factory("database-config.txt");
        factory.loadDatabaseSettings(ip, username, password);

        MySql connection;

        std::cout << "Made connection to the database\n";
        wiringPiSetup();
        wiringPiSPISetup(0, 10000000); // max speed for mfrc522 is 10Mhz
        MFRC522 rfid;
        rfid.PCD_Init();

        // Keypad pinSetup
        const int keypadRow[] = {15, 16, 1, 4};
        const int keypadColumn[] = {8, 9, 7, 2};

        // Keypad objects
        MatrixKeypad keypad(keypadRow, keypadColumn, 4);

        LedController led(0);
        DatabaseManager information;
        information.connectTo(ip, username, password);
        information.selectDatabase("R2D2");
        while (true) {
            delay(1000);
            std::cout << "\n\nWaiting for rfid tag: \n";

            if (!rfid.PICC_IsNewCardPresent())
                continue;

            if (!rfid.PICC_ReadCardSerial())
                continue;

            std::string id;
            for (byte i = 0; i < rfid.uid.size; ++i) {
                std::stringstream ss;
                ss << std::hex << (int)rfid.uid.uidByte[i];
                std::string res(ss.str());
                id += res;
                if (i != rfid.uid.size - 1) {
                    id += ' ';
                }
            }
            std::cout << id << " is the presented ID\n";
            if (!information.isCardInDatabase(id)) {
                std::cout << "This ID is in the database\n";
            } else {
                std::cout << "This ID is NOT in the database\n";
            }

#ifdef USING_PIN
            MFRC522::MIFARE_Key key = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};
            if (1 !=
                rfid.PCD_Authenticate(MFRC522::PICC_CMD_MF_AUTH_KEY_A,
                                      (byte)0x05, &key, &rfid.uid))
                continue;

            // read pincode
            byte bufferSize = (byte)18;
            byte readArray[18] = {0, 0, 0, 0, 0, 0, 0, 0, 0,
                                  0, 0, 0, 0, 0, 0, 0, 0, 0};
            rfid.MIFARE_Read((byte)0x05, readArray, &bufferSize);
            std::cout << "Readarray contains: \n";
            for (int i = 0; i < 18; i++) {
                std::cout << (int)readArray[i] << ' ';
            }

            // enter pincode
            std::cout << "\nInput PIN and finish with #\n";
            std::string value = keypad.getString();

            // write pincode
            byte writeArray[16] = {0, 0, 0, 0, 0, 0, 0, 0,
                                   0, 0, 0, 0, 0, 0, 0, 0};
            int index = 0;
            for (auto c : value) {
                if (c > 47 && c < 58) {
                    int number = c - 48;
                    writeArray[index++] = (byte)number;
                }
            }
            rfid.MIFARE_Write((byte)0x05, writeArray, (byte)16);
            std::cout << "Writearray contains: \n";
            for (int i = 0; i < 16; i++) {
                std::cout << (int)writeArray[i] << ' ';
            }

#endif

            rfid.PCD_StopCrypto1();
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
