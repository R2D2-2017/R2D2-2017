/**
 * \file
 * \brief     The definitions of the parser functionality of GAS-03.
 * \author    Wilco Louwerse
 * \author	  Nicky van Steensel van der Aa
 * \copyright Copyright (c) 2017, The R2D2 Team
 * \license   See LICENSE
 * \wiki      ...
 * \trello    https://trello.com/c/zSJnP0Rw/5-a-parser-must-be-made-that-can-read-the-conftxt-and-set-the-variables
 */

#include "parser.hh"

Parser::Parser(Alarm &alarm, Mq5 &mq5) :
        alarm(alarm),
        mq5(mq5) {}

bool Parser::ifContainsString(char array[], char string[]) {
    bool containsString = false;
    for(int i = 0; array[i] != '\0'; i++) {
        if(containsString) {break;}
        int j = 0;
        while(string[j] == array[i+j]) {
            if(string[j] == '\0') {
                containsString = true;
                break;
            }
            j++;
        }
    }
    return containsString;
}

void Parser::parseArray(char* input) {

    //for loop integers
    int i, j;

    //read input array variables
    //example of 1 variable:      @firstNote:880\n
    for(i = 0; input[i] != '\0'; ++i) {

        //start reading new variable at '@'
        if(input[i] == '@') {

            //reset variable value to 0
            variableValue = 0;

            //skip '@' character
            i++;

            //read variable name from input array
            for(j = 0; input[i] != ':'; ++i, ++j) {
                if(input[i] == '\0') {                          //prevent endless loop
                    hwlib::cout << ">>>PARSER ERROR : while reading variable name, prevent endless loop!" << "\r\n";
                    break;
                }
                variableName[j] = input[i];
            }
            variableName[j] = '\0';

            //skip ':' character
            i++;

            //read variable value from input array (always int)
            for(j = 0; input[i] != '\n'; ++i, ++j) {
                if(input[i] == '\0') {                          //prevent endless loop
                    hwlib::cout << ">>>PARSER ERROR : while reading variable value for [ " << variableName
                                << " ], prevent endless loop!" << "\r\n";
                    break;
                }
                if(variableValue != 0) {
                    variableValue *= 10;
                }
                if((input[i] < '0') || (input[i] > '9')) {      //check if variable value is an integer or not
                    hwlib::cout << ">>>PARSER ERROR : while reading variable value for [ " << variableName
                                << " ], [ " << input[i] << " ] is not an integer!" << "\r\n";
                    break;
                }
                variableValue += input[i] - '0';                //convert a single char to an integer
            }

            //set all variables
            if(ifContainsString(variableName, firstNoteString)) {
                alarm.setFirstNote(variableValue);
               // hwlib::cout << "alarm.setFirstNote(" << variableValue << ")" << "\r\n";
            }
            else if(ifContainsString(variableName, secondNoteString)) {
                alarm.setSecondNote(variableValue);
              //  hwlib::cout << "alarm.setSecondNote(" << variableValue << ")" << "\r\n";
            }
            else if(ifContainsString(variableName, warningThresholdString)) {
                alarm.setWarningThreshold(variableValue);
               // hwlib::cout << "alarm.setWarningThreshold(" << variableValue << ")" << "\r\n";
            }
            else if(ifContainsString(variableName, dangerThresholdString)) {
                alarm.setDangerThreshold(variableValue);
              //  hwlib::cout << "alarm.setDangerThreshold(" << variableValue << ")" << "\r\n";
            }
            else if(ifContainsString(variableName, mq5CalibrationValueString)) {
				if (isCalibrated) {
					mq5.setmq5CalibrationValue(variableValue);
				}
              //  hwlib::cout << "mq5.setmq5CalibrationValue(" << variableValue << ")" << "\r\n";
            }
            else if(ifContainsString(variableName, measureFrequencyString)) {
                //???.setMeasureFrequency(variableValue);
                hwlib::cout << "TODO: ???.setMeasureFrequency(" << variableValue << ")" << "\r\n";
            }
			else if (ifContainsString(variableName, isCalibratedString)) {
				isCalibrated = variableValue;
				hwlib::cout << "is calibrated = " << variableValue << "\r\n";
			}
            else {
                hwlib::cout << ">>>PARSER ERROR : [ " << variableName << " ] is not a valid/known variable!" << "\r\n";
            }
        }
    }
}