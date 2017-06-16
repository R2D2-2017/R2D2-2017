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

    char variableName[20];
    int variableValue = 0;
    char highNoteString[] = "highNote";
    char lowNoteString[] = "lowNote";
    char warningThresholdString[] = "warningThreshold";
    char dangerThresholdString[] = "dangerThreshold";
    char mq5BaseValueString[] = "mq5BaseValue";
    char measureFrequencyString[] = "measureFrequency";
    int i, j;

    //read input values
    //example:      @highNote:880
    for(i = 0; input[i] != '\0'; ++i) {
        hwlib::cout << "x------------x" << "\r\n";
        if(input[i] == '@') {
            variableValue = 0;
            i++;
            for(j = 0; input[i] != ':'; ++i, ++j) {
                variableName[j] = input[i];
            }
            variableName[j] = '\0';
            hwlib::cout << "variableName: " << variableName << "\r\n";
            i++;

            for(j = 0; input[i] != '\n'; ++i, ++j) {
                if(variableValue != 0) {
                    variableValue *= 10;
                }
                variableValue += input[i] - '0';
            }
            hwlib::cout << "variableValue: " << variableValue << "\r\n";

            if(ifContainsString(variableName, highNoteString)) {
                //alarm.setHighNote(variableValue);
                hwlib::cout << "alarm.setHighNote(" << variableValue << ")" << "\r\n";
            }
            else if(ifContainsString(variableName, lowNoteString)) {
                //alarm.setLowNote(variableValue);
                hwlib::cout << "alarm.setLowNote(" << variableValue << ")" << "\r\n";
            }
            else if(ifContainsString(variableName, warningThresholdString)) {
                //alarm.setWarningThreshold(variableValue);
                hwlib::cout << "alarm.setWarningThreshold(" << variableValue << ")" << "\r\n";
            }
            else if(ifContainsString(variableName, dangerThresholdString)) {
                //alarm.setDangerThreshold(variableValue);
                hwlib::cout << "alarm.setDangerThreshold(" << variableValue << ")" << "\r\n";
            }
            else if(ifContainsString(variableName, mq5BaseValueString)) {
                //mq5.setMq5BaseValue(variableValue);
                hwlib::cout << "mq5.setMq5BaseValue(" << variableValue << ")" << "\r\n";
            }
            else if(ifContainsString(variableName, measureFrequencyString)) {
                //???.setMeasureFrequency(variableValue);
                hwlib::cout << "???.setMeasureFrequency(" << variableValue << ")" << "\r\n";
            }
            hwlib::cout << "\r\n";
        }
    }
}