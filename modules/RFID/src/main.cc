 /**
 * \file      main.cc
 * \brief     Program for giving an indication when a rfid card has been detected, a database connection has been made and a string has been encrypted
 * \author    Tim IJntema, Stefan de Beer, Arco Gelderblom, Rik Honcoop, Koen de Groot
 * \copyright Copyright (c) 2017, The R2D2 Team
 * \license   See LICENSE
 */
 
#include "mysql.hh"
#include "mfrc522.hh"
#include "encryption.hh"
#include "led-controller.hh"
#include "matrix-keypad.hh"

#include <wiringPi.h>
#include <wiringPiSPI.h>
 
#include <iostream>

int main(int argc, char **argv) {
    MySql connection;

    if (!connection.connectTo("192.168.2.50", "R2D2", "BB8")) {
        std::cerr << "Can not connect\n";
        exit(0);
    }
    
    if (!connection.selectDatabase("R2D2")) {
        std::cerr << "Database unknown\n";
        exit(0);
    }
    std::cout << "Made connection to the database\n";
    wiringPiSetup();
    wiringPiSPISetup(0, 10000000);//max speed for mfrc522 is 10Mhz
    Mfrc522 rfid;
    rfid.init();

    //Keypad pinSetup
    const int keypadRow[] = {24, 25, 22, 31};
    const int keypadColumn[] = {26, 27, 28, 29};

    //Keypad objects
    MatrixKeypad keypad(keypadRow, keypadColumn, 4);
    char c;

    Encryption encryption(65341);

    LedController led;

    while (true) {
        std::cout << "\n\nWaiting for rfid tag: \n";

        while (!rfid.isTagPresent()) {}
        
        std::cout << "Hello tag\n";
        std::cout << "Waiting for key press\n";
        while ((c = keypad.getKey()) == 'h') {
            delay(100);
        }
        std::cout << "A key has been pressed\n";

        if (!connection.executeQuery("SELECT * FROM RFID")) {
            std::cout << "Can not execute query\n";
            exit(EXIT_FAILURE);
        }
        
        std::cout << "Database information: "
                  << connection.getPreviousResponseColumn("CARD_ID")
                  << '\n';
        
        std::cout << "String before encryption: R2D2 project\n";
        std::cout << "String after encryption: "
                  << encryption.Encrypt("R2D2 project")
                  << '\n';

        led.blinkLed(0, 5000);
	}    
    return 0;
}
