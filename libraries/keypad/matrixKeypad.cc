/*
* File:   matrixKeypad.cpp
* Author: Tim IJntema
*
* Created on 27 may 2016, 14:36
*/

#include "matrixKeypad.hh"

matrixKeypad::matrixKeypad( 
		hwlib::pin_in_out & p0,
		hwlib::pin_in_out & p1,
		hwlib::pin_in_out & p2,
		hwlib::pin_in_out & p3,
		hwlib::pin_in_out & p4,
		hwlib::pin_in_out & p5,
		hwlib::pin_in_out & p6,
		int colSize
	):
	pinColumn{&p4, &p5, &p6},
	pinRow{&p0, &p1, &p2, &p3},
	colSize(colSize)
{}

char matrixKeypad::getKey(){
		for (int i = 0; i < colSize; i++){
			pinColumn[i]->direction_set_output();
			pinColumn[i]->set(0);
		}
		
		for (auto & pin : pinRow){ 
			pin->direction_set_input(); 
		}
		keypadRow = -1;
		for (int i = 0; i < rowSize; i++){
			if (pinRow[i]->get() == 0){
				keypadRow = i;
			}
		}
		
		for (int i = 0; i < colSize; i++){
			pinColumn[i]->direction_set_input();
		}
		
		pinRow[keypadRow]->direction_set_output();
		pinRow[keypadRow]->set(0);
		
		keypadColumn = -1;
		for (int i = 0; i <  colSize; i++){
			if (pinColumn[i]->get() == 0){
				keypadColumn = i;
			}
		}
		
		if ((keypadRow != -1) && (keypadColumn != -1)){
			return keypad[keypadRow][keypadColumn];
		}
		return 'h';
}

int matrixKeypad::getString(char * chararray, int lenCharArray){
	char pressedKey;
	int i = 0;
	
	while((pressedKey = getKey()) != '#' && i < (lenCharArray-1)){
		if (keypadColumn != -1 && pressedKey != 'h'){
			chararray[i] = pressedKey;
			i++;
			 hwlib::cout << pressedKey; //for debugging
			while (pinColumn[keypadColumn]->get() == 0){}
		}
	}
	chararray[i] = '\0';
	return i;
}