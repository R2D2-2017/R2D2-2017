//
// Created by MuscioCraft on 16-6-2017.
//

#include "command.hh"

void command::commander(uint8_t (*commands)[8][2])
{
    for(int j =0; j <= numberOfRows; j++)
    {
        int l = 0;
        for(int k = 0; k < numberOfMatrices; k++)
        {
            processedCommands[l] = {(uint8_t)j};
            l++;
            processedCommands[l] = {commands[k][j-1][1]};
            l++;
        }
        spiBus.write_and_read(chipSelect, 2*numberOfMatrices, processedCommands , nullptr);
    }
}

void command::settings(const uint8_t (*settingsList)[2])
{
    int numberOfCommands = 5;
    for(int i = 0; i < numberOfCommands ;i++)
    {
        int l = 0;
        for(int k = 0; k < numberOfMatrices; k++)
        {
            processedCommands[l] = {settingsList[i][0]};
            l++;
            processedCommands[l] = {settingsList[i][1]};
            l++;
        }
        spiBus.write_and_read(chipSelect, 2*numberOfMatrices, processedCommands , nullptr);    //data is send over SPI to MAX7219. Only write, read is voided
    }
}

void command::converter(uint8_t (*renderInput)[8], uint8_t (*converterOutput)[2])

{
    for(int i = 0; i < 8; i++)                                  // Row 0-7;
    {
        uint8_t shiftVariable = 0;                                           // An temp uint8_t, in to this uint8_t data will be shifted to make from an matrix row, 1 uint8_t.
        int rowCounter = 0;                                        // Counter column 7-0;
        for(int j = 8; j >= 0; j--)                             // J is an shifter, matrix(_tmp) will be shifted J places in tmp.
        {
            shiftVariable |= renderInput[i][rowCounter-1] << (j);        // and then shifed J times.
            rowCounter++;                                      // Next column!
        }                                                       //matrix_data is and 8x2 marix, it will be filled with:
        converterOutput[i][0] = i+1;                                //Row number. i+1 is because the rows start from 1 and NOT 0.
        converterOutput[i][1] = shiftVariable;                                //Column data.
    }

}

void command::render(uint8_t (*renderInput)[8]) {

    converter(renderInput, converterOutput);
    for (int i = 0; i < numberOfRows; i++) {
        commands[numberOfWrites][i][1] = converterOutput[i][1];
    }
    numberOfWrites++;
    if (numberOfWrites == stringLength) {
        numberOfWrites = 0;
        commander(commands);
    }
}

