/**
 * \file      main.cc
 * \brief     Using the keypad library
 * \author    Tim IJntema, René de Kluis
 * \copyright Copyright (c) 2017, The R2D2 Team
 * \license   See LICENSE
 */


#include <wiringPi.h>
#include <iostream>

#include "matrix-keypad.hh"

int main(int argc, char** argv){
    wiringPiSetupGpio();
    
    //Keypad pinSetup
    const int keypadRow[] = {29, 28, 27, 26};
    const int keypadColumn[] = {31, 11, 10, 6};

    //Keypad objects
    MatrixKeypad keypad(keypadRow, keypadColumn, 4);
    char c;

    while(1){
        if( (c = keypad.getKey()) != 'h' ){
            std::cout << "A key has been pressed\n" << c << '\n';
        }
        delay(100);
    }
    return 0;
}
