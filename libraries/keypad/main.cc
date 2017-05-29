/*
* File:   main.cpp
* Author: Tim IJntema
*
* Created on 8 june 2016, 8:21
*/

// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)

#include "hwlib.hpp"
#include "matrixKeypad.hpp"

int main(){
	//Kill the watchdog
	WDT->WDT_MR = WDT_MR_WDDIS;
	
	//Keypad variables
	//const int maxLen = 10;
	//char PWD[maxLen][maxLen] = {"9735"};
	//int PWDLen[maxLen] = {5};
	//char password[maxLen];
	
	//Keypad rows
	auto keypad0 = hwlib::target::pin_in_out(hwlib::target::pins::d32);
	auto keypad1 = hwlib::target::pin_in_out(hwlib::target::pins::d22);
	auto keypad2 = hwlib::target::pin_in_out(hwlib::target::pins::d24);
	auto keypad3 = hwlib::target::pin_in_out(hwlib::target::pins::d28);
	
	//Keypad columns
	auto keypad4 = hwlib::target::pin_in_out(hwlib::target::pins::d30);
	auto keypad5 = hwlib::target::pin_in_out(hwlib::target::pins::d34);
	auto keypad6 = hwlib::target::pin_in_out(hwlib::target::pins::d26);
	auto keypad7 = hwlib::pin_in_out_dummy;//Had to create this pin because I'm using a buzzer
	
	//Remaining pins
	auto ledGreen = hwlib::target::pin_out(hwlib::target::pins::d3);
	auto ledRed = hwlib::target::pin_out(hwlib::target::pins::d4);
	auto buzzerPin = hwlib::target::pin_out(hwlib::target::pins::d6);
	
	//Keypad objects
	matrixKeypad keypad(keypad0, keypad1, keypad2, keypad3, keypad4, keypad5, keypad6, keypad7, 3, buzzerPin);
	
	
	while(1){
		hwlib::cout 
		<< "Pressed key: " << keypad.getKey() << "\n"
		<< "Number of keys pressed: " << keypad.getString() << "\n"
		<< "Pressed password: ";
		
		for(int i = 0; i < maxLen; i++){
			hwlib::cout << password[i];
		}
		
		hwlib::cout 
			<< "\n" 
			<< "======================" << "\n\n";
		
		hwlib::wait_ms(10);
	}
	return 0;
}