/*
* File:   matrixKeypad.cpp
* Author: Tim IJntema
*
* Created on 27 may 2016, 14:36
*/

#include "matrixKeypad.hh"

matrixKeypad::matrixKeypad( 
        const int * row, 
        const int * column, 
        int colSize 
        ):
	column(column),
	row(row),
	colSize(colSize)
{}

char matrixKeypad::getKey(){
		for (int i = 0; i < colSize; ++i){
                    pinMode(column[i], OUTPUT);
                    pullUpDnControl(column[i], PUD_OFF);
		}
		
                for(int i = 0; i < rowSize; ++i){
                    pinMode(row[i], INPUT);
                }
		
		keypadRow = -1;
		for (int i = 0; i < rowSize; ++i){
                    if(digitalRead(row[i]) == 1){
                        keypadRow = i;
                    }
		}
		
		for (int i = 0; i < colSize; ++i){
                    pinMode(column[i], INPUT);
		}
		
                pinMode(row[keypadRow], OUTPUT);
                pullUpDnControl(row[keypadRow], PUD_OFF);
		
		keypadColumn = -1;
		for (int i = 0; i <  colSize; i++){
                    if(digitalRead(column[i]) == 1){
                        keypadColumn = i;
                    }
		}
		
		if ((keypadRow != -1) && (keypadColumn != -1)){
			return keypad[keypadRow][keypadColumn];
		}
		return 'h';
}

int matrixKeypad::getString(char * charArray, int lenCharArray){
	char pressedKey;
	int i = 0;
	
	while((pressedKey = getKey()) != '#' && i < (lenCharArray-1)){
		if (keypadColumn != -1 && pressedKey != 'h'){
			charArray[i] = pressedKey;
			++i;
			 //std::cout << pressedKey; //for debugging
                        while(digitalRead(column[keypadColumn]) == 1){}
		}
	}
	charArray[i] = '\0';
	return i;
}