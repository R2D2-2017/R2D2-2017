/*
* File:   main.cpp
* Author: Tim IJntema
*
* Created on 8 june 2016, 8:21
*/

// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)


#include <wiringPi.h>
#include <stdio.h>
#include <iostream>

#include "matrixKeypad.hh"

//Keypad Row pinSetup
const int row1 = 6;
const int row2 = 15;
const int row3 = 16;
const int row4 = 5;

//Keypad Column pinSetup
const int column1 = 5;
const int column2 = 10;
const int column3 = 1;


using namespace std;

int main(int argc, char** argv){
	
    wiringPiSetupGpio();
    
    //Keypad variables
    const int maxLen = 10;
    char password[maxLen];
    int pwdLen;
    
    //Keypad pinSetup
    const int keypadRow[] = {row1,row2,row3,row4};
    const int keypadColumn[] = {column1, column2, column3};

    //Keypad objects
    matrixKeypad keypad(keypadRow, keypadColumn, 3);

    
    while(1){
        std::cout << "\nKeyPressed"<< keypad.getKey() << "\n";
        
        pwdLen = keypad.getString(password, maxLen);
        std::cout << "Number of keys pressed: " << pwdLen << "\n";
        
        for(int i = 0; i < pwdLen; ++i){
            std::cout << password[i];
        }
        delay(10);
    }
    return 0;
}
