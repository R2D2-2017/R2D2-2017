 /**
 * \file	matrixKeypad.hh
 * \brief     	Obtain pressed keys from a keypad.
 *
 * This is a class that can be used to obtain pressed keys from a keypad using an Arduino Due board.\n
 * The seperate keypresses can be obtained or an array of characters can be filled with pressed characters.\n
 * It uses another namespace containing classes that make it capable of using Arduino Due pins.\n 
 *
 * \author    	Tim IJntema, René de Kluis
 * \copyright 	Copyright (c) 2017, The R2D2 Team
 * \license   	See LICENSE
 * Created on 27 may 2016, 14:36
 */


#ifndef MATRIXKEYPAD_HPP
#define	MATRIXKEYPAD_HPP

#include <wiringPi.h>

class matrixKeypad{
private:
	static const int rowSize = 4;
	int colSize;
	
        int keypadRow = -1;
	int keypadColumn = -1;
	
        const int * row;
	const int * column;
        
	char keypad[4][4] = {
            {'1', '2', '3', 'A'},
            {'4', '5', '6', 'B'},
            {'7', '8', '9', 'C'},
            {'*', '0', '#', 'D'}
	};
public:
	
	/**
	* \brief Constructor
	* 
	* This constructor collects all the pins that are needed for the keypad.
        * It takes the size of the keypad and the pins on which it is attached.
	* 
        * \param[in,out] row Pins that are used as rows for the keypad.
        * \param[in,out] column Pins that are used as columns for the keypad.
        * \param[in] colSize Amount of columns on the keypad.
        * 
	*/
	matrixKeypad( const int * row, const int * column, int colSize = 3 );
	
	/**
	* \brief Obtain separate keys
	* 
	* This function obtains the separate keys from the keypad.
	* It waits for a key to be pressed and then returns the pressed key 
        * as a character.
	*  
        * \return The key that is pressed in the form of a character
        * 
	*/
	char getKey();
	
	/**
	* \brief Obtain a collection of keys.
	* This function will collect keys that are pressed on the keypad.
        * The keys will be collected until the max length of the password 
        * is reached or the '#' button is pressed.
        * When a button is pressed and is being hold the system shall see this 
        * only as one key, no matter how long you'll hold it. 
        * 
        * \param[in,out] charArray password to be collected.
        * \param[in] lenCharArray max length of the password
        * 
        * \return The amount of keys that are pressed on the keypad.
        * 
	*/
	int getString(char * charArray, int lenCharArray);
};


#endif	/* MATRIXKEYPAD_HPP */