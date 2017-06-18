//
// Created by MuscioCraft on 16-6-2017.
//

#include "setup.hh"

void Setup::operate(char* inputString){
    int stringLength = sizeof(inputString)/ sizeof(inputString[0]) - 1 + numberOfUnusedMatrices;

    command display(spiBus, chipSelect, numberOfMatrices, numberOfRows, stringLength);
    display.settings(settings);

    for(int i = 0; i < numberOfUnusedMatrices; i++)
    {
        display.render(charSpace);
    }

    for(int i = 0; i < stringLength-numberOfUnusedMatrices; i++)
    {
        switch(inputString[i]){
            case '1' : display.render(charOne);    break;
            case '2' : display.render(charTwo);    break;
            case '3' : display.render(charThree);  break;
            case '4' : display.render(charFour);   break;
            case '5' : display.render(charFive);   break;
            case '6' : display.render(charSix);    break;
            case '7' : display.render(charSeven);  break;
            case '8' : display.render(charEight);  break;
            case '9' : display.render(charNine);   break;
            case '0' : display.render(charZero);    break;
            case '+' : display.render(charPlus);   break;
            case '-' : display.render(charMinus);  break;
        }
    }
}