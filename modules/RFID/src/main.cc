/**
* \file      main.cc
* \brief     Program for giving an indication when a RFID card has been
* detected, a database connection has been made and a string has been encrypted
* \author    Tim IJntema, Stefan de Beer, Arco Gelderblom, Rik Honcoop, Koen de
* Groot, Ricardo Bouwman, Philippe Zwietering, Luuk Steeman, Leo Jenneskens,
* Jeremy Ruijzenaars
* \copyright Copyright (c) 2017, The R2D2 Team
* \license   See LICENSE
*/

#include "config-file-parser.hh"
#include "database-manager.hh"
#include "led-controller.hh"
#include "matrix-keypad.hh"
#include "mfrc522.hh"

#include <wiringPiSPI.h>

#include <iomanip>
#include <string>

// Keypad pinSetup
const int keypadRow[] = {15, 16, 1, 4};
const int keypadColumn[] = {8, 9, 7, 2};

// Magic number declarations
const int redLedPin = 0;
const int greenLedPin = 11;
const int maxSpeedWiringSPI = 10000000; // max speed for mfrc522 is 10Mhz
const int keypadColumnSize = 4;
const int blockSizeWithCrc = 18;
const int blockSize = 16;
const int zeroAscii = 47;
const int nineAscii = 58;
const int blinkTime = 3000;

int main(int argc, char **argv) {

    if(argc != 2 || (std::string(argv[1]) != "pin" && std::string(argv[1]) != "no-pin")) {
        std::cerr << "Please only put in 'pin' or 'no-pin' as parameter, nothing else." << std::endl
                  << "Your function will then either look like './rfid pin' or './rfid no-pin'" << std::endl;
    }

    // Keypad objects
    MatrixKeypad keypad(keypadRow, keypadColumn, keypadColumnSize);

    LedController redLed(redLedPin);
    LedController greenLed(greenLedPin);

    std::string ip;
    std::string username;
    std::string password;

    ConfigFileParser factory("database-config.txt");
    factory.loadDatabaseSettings(ip, username, password);
    DatabaseManager information;
    information.connectTo(ip, username, password);
    information.selectDatabase("R2D2");

    std::cout << "Made connection to the database\n";
    wiringPiSetup();
    wiringPiSPISetup(0, maxSpeedWiringSPI);

    MFRC522 rfid;
    rfid.PCD_Init();

    while (true) {
        delay(1000);
        std::cout << "\n\nWaiting for RFID tag: \n";

        if (!rfid.PICC_IsNewCardPresent())
            continue;

        if (!rfid.PICC_ReadCardSerial())
            continue;

        std::string id;
        for (byte i = 0; i < rfid.uid.size; ++i) {
            std::stringstream ss;
            ss << std::hex << (int) rfid.uid.uidByte[i];
            id += ss.str();
            if (i != rfid.uid.size - 1) {
                id += ' ';
            }
        }

        bool inDatabase;
        std::cout << id << " is the presented ID\n";
        if (!information.isCardInDatabase(id)) {
            std::cout << "This ID is in the database\n";
            inDatabase = 1;
        } else {
            std::cout << "This ID is NOT in the database\n";
            inDatabase = 0;
        }

        if(std::string(argv[1]) == "pin") {
            MFRC522::MIFARE_Key key = {{0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF}};
            if (rfid.PCD_Authenticate(MFRC522::PICC_CMD_MF_AUTH_KEY_A,
                                      (byte) 0x05, &key, &rfid.uid) != 1)
                continue;

            // read pin code
            byte bufferSize = (byte) blockSizeWithCrc;
            byte readArray[blockSizeWithCrc] = {};
            rfid.MIFARE_Read((byte) 0x05, readArray, &bufferSize);
            std::cout << "Read array contains: \n";
            for (int i = 0; i < blockSizeWithCrc; i++) {
                std::cout << (int) readArray[i] << ' ';
            }

            // enter pin code
            std::cout << "\nInput PIN and finish with #\n";
            std::string value = keypad.getString();

            // write pin code
            byte writeArray[blockSize] = {};
            int index = 0;
            for (const auto c : value) {
                if (c > zeroAscii && c < nineAscii) {
                    int number = c - (zeroAscii+1);
                    writeArray[index++] = (byte) number;
                }
            }
            rfid.MIFARE_Write((byte) 0x05, writeArray, (byte) blockSize);
            std::cout << "Write array contains: \n";
            for (int i = 0; i < blockSize; i++) {
                std::cout << (int) writeArray[i] << ' ';
            }
        }

        rfid.PCD_StopCrypto1();
        if (inDatabase) {
            greenLed.blinkLed(blinkTime);
        } else {
            redLed.blinkLed(blinkTime);
        }
    }
}
