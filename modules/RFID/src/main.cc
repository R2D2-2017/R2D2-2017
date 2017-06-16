
 /**
 * \file      main.cc
 * \brief     Program for giving an indication when a rfid card has been detected, a database connection has been made and a string has been encrypted
 * \author    Tim IJntema, Stefan de Beer, Arco Gelderblom, Rik Honcoop, Koen de Groot, Ricardo Bouwman
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
        //int encryptionKey;

        ConfigFileParser factory("database-config.txt");
        factory.loadDatabaseSettings(ip, username, password);

        MySql connection;

        connection.connectTo(ip, username, password);
        connection.selectDatabase("R2D2");

        std::cout << "Made connection to the database\n";
        wiringPiSetup();
        wiringPiSPISetup(0, 10000000);//max speed for mfrc522 is 10Mhz
        MFRC522 rfid;
        rfid.PCD_Init();

        //Keypad pinSetup
        const int keypadRow[] = {4, 1, 16, 15};
        const int keypadColumn[] = {2, 7, 9, 8};

        //Keypad objects
        MatrixKeypad keypad(keypadRow, keypadColumn, 4);
        char c;

        LedController led(0);

        while (true) {
            delay(1000);
            std::cout << "\n\nWaiting for rfid tag: \n";

            if(!rfid.PICC_IsNewCardPresent())
                continue;
            if(!rfid.PICC_ReadCardSerial())
                continue;

            MFRC522::MIFARE_Key key = {0xFF, 0xFF, 0xFF, 0xFF};

            std::cout << "Input PIN and finish with #\n";

            long value = atol(keypad.getString().c_str());

            if(!rfid.PCD_Authenticate(MFRC522::PICC_CMD_MF_AUTH_KEY_A, (byte)0x03, &key, &rfid.uid))
                continue;

            if (!rfid.MIFARE_SetValue((byte)0x03, value))
                continue;

            if (!rfid.MIFARE_GetValue((byte)0x03, &value))
                continue;

            std::cout << value << '\n';

            for(byte i = 0; i < rfid.uid.size; ++i){
                if(rfid.uid.uidByte[i] < 0x10){
                    printf(" 0");
                    printf("%X",rfid.uid.uidByte[i]);
                }
                else{
                    printf(" ");
                    printf("%X", rfid.uid.uidByte[i]);
                }
            }





//            while (!rfid.isTagPresent()) {
//            }
            // MFAuthentData x;
            // uint8_t receiveData[64];
            // int block = 0;
            // rfid.communicateWithTag(Mfrc522::mfrc522Commands::receive,
                                    // &block,
                                    // 1,
                                    // receiveData,
                                    // 64*8);
            // rfid.communicateWithTag(Mfrc522::mfrc522Commands::mfAuthent, nullptr, 0, nullptr, 0);

            // uint8_t tag[16];

//            Mfrc522::statusCodes s = rfid.receiveTagId(tag);
//            if(s == Mfrc522::statusCodes::statusOk){
//                std::cout << "Hello tag\n";
//                std::cout << "Your id = ";
//                for(size_t i = 0; i < 4; i++){
//                    std::cout << std::hex << tag[i];
//                }
//                std::cout << "\n";
//            } else if(s == Mfrc522::statusCodes::statusError){
//                std::cout << "ERROR\n";
//            } else{
//                std::cout << "Something else went wrong reading the key\n";
//            }
//
//            std::cout << "Waiting for key press\n";
//            while ((c = keypad.getKey()) == 'h') {
//                delay(100);
//            }
//
//            std::cout << c << " key has been pressed\n";
//
//            std::cout << "Enter a pincode, ending with '#'\n";
//
//            std::string pin = keypad.getString();
//            std::cout << "The pin you entered was: " << pin << "\n";
//
//            connection.executeQuery("SELECT * FROM RFID");
//
//            std::cout << "Database information: "
//                      << connection.getPreviousResponseColumn("CARD_ID")
//                      << '\n';
//
//            led.blinkLed(1000);
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

