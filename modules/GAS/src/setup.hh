//===========================================================//
//             Copyright Mike Hilhorst 2016.                 //
// Distributed under the Boost Software License, Version 1.0.//
//    (See accompanying file LICENSE_1_0.txt or copy at      //
//          http://www.boost.org/LICENSE_1_0.txt)            //
//===========================================================//

#pragma once

#include "wrap-hwlib.hh"
#include "command.hh"
#include "mbin_to_mhex.hh"
#include "clean.hh"
#include "matrix.hh"

class Setup
{
private:

    hwlib::spi_bus & bus;
    hwlib::pin_out & cs;
    int number_of_matrices;
    int count;
    int time;

    uint8_t char_space[8][8] = {{0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0}};
    uint8_t char_one[8][8] = {{0,0,0,0,0,0,0,0},{0,0,1,1,1,0,0,0},{0,1,1,1,1,0,0,0},{0,0,0,1,1,0,0,0},{0,0,0,1,1,0,0,0},{0,0,0,1,1,0,0,0},{0,1,1,1,1,1,1,0},{0,0,0,0,0,0,0,0}};
    uint8_t char_two[8][8] = {{0,0,0,0,0,0,0,0},{0,1,1,1,1,1,0,0},{0,0,0,0,0,1,1,0},{0,0,0,0,0,1,1,0},{0,0,0,0,1,1,0,0},{0,0,0,1,1,0,0,0},{0,1,1,1,1,1,1,0},{0,0,0,0,0,0,0,0}};
    uint8_t char_three[8][8] = {{0,0,0,0,0,0,0,0},{0,1,1,1,1,1,0,0},{0,0,0,0,0,1,1,0},{0,0,0,1,1,1,1,0},{0,0,0,1,1,1,1,0},{0,0,0,0,0,1,1,0},{0,1,1,1,1,1,0,0},{0,0,0,0,0,0,0,0}};
    uint8_t char_four[8][8] = {{0,0,0,0,0,0,0,0},{0,0,0,0,0,1,0,0},{0,0,0,0,1,1,0,0},{0,0,0,1,0,1,0,0},{0,0,1,0,0,1,0,0},{0,1,1,1,1,1,1,0},{0,0,0,0,0,1,0,0},{0,0,0,0,0,0,0,0}};
    uint8_t char_five[8][8] = {{0,0,0,0,0,0,0,0},{0,1,1,1,1,1,1,0},{0,1,0,0,0,0,0,0},{0,1,1,1,1,1,0,0},{0,0,0,0,0,0,1,0},{0,0,0,0,0,0,1,0},{0,1,1,1,1,1,0,0},{0,0,0,0,0,0,0,0}};
    uint8_t char_six[8][8] = {{0,0,0,0,0,0,0,0},{0,0,1,1,1,1,1,0},{0,1,0,0,0,0,0,0},{0,1,1,1,1,1,0,0},{0,1,0,0,0,0,1,0},{0,1,0,0,0,0,1,0},{0,0,1,1,1,1,0,0},{0,0,0,0,0,0,0,0}};
    uint8_t char_seven[8][8] = {{0,0,0,0,0,0,0,0},{0,1,1,1,1,1,1,0},{0,0,0,0,0,1,1,0},{0,0,0,0,1,1,0,0},{0,0,0,1,1,0,0,0},{0,0,1,1,0,0,0,0},{0,1,1,0,0,0,0,0},{0,0,0,0,0,0,0,0}};
    uint8_t char_eight[8][8] = {{0,0,0,0,0,0,0,0},{0,0,1,1,1,1,0,0},{0,1,0,0,0,0,1,0},{0,0,1,1,1,1,0,0},{0,1,0,0,0,0,1,0},{0,1,0,0,0,0,1,0},{0,0,1,1,1,1,0,0},{0,0,0,0,0,0,0,0}};
    uint8_t char_nine[8][8] = {{0,0,0,0,0,0,0,0},{0,0,1,1,1,1,0,0},{0,1,0,0,0,0,1,0},{0,0,1,1,1,1,1,0},{0,0,0,0,0,0,1,0},{0,0,0,0,0,0,1,0},{0,0,1,1,1,1,0,0},{0,0,0,0,0,0,0,0}};
    uint8_t char_ten[8][8] = {{0,0,0,0,0,0,0,0},{0,0,1,1,1,1,0,0},{0,1,0,0,0,0,1,0},{0,1,0,0,0,0,1,0},{0,1,0,0,0,0,1,0},{0,1,0,0,0,0,1,0},{0,0,1,1,1,1,0,0},{0,0,0,0,0,0,0,0}};
    uint8_t char_minus[8][8] = {{0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0},{0,1,1,1,1,1,1,0},{0,1,1,1,1,1,1,0},{0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0}};
    uint8_t char_plus[8][8] = {{0,0,0,0,0,0,0,0},{0,0,0,1,1,0,0,0},{0,0,0,1,1,0,0,0},{0,1,1,1,1,1,1,0},{0,1,1,1,1,1,1,0},{0,0,0,1,1,0,0,0},{0,0,0,1,1,0,0,0},{0,0,0,0,0,0,0,0}};

public:
    Setup(hwlib::spi_bus & bus, hwlib::pin_out & cs, int number_of_matrices, int count, int time):
            bus(bus), cs(cs), number_of_matrices(number_of_matrices), count(count), time(time)
    {

        //The time in ms that the characters will be displayed on the screen
        char input_string[] = {"1234567890-+"};
        int string_lenght = sizeof(input_string)/sizeof(input_string[0]) + number_of_matrices*2 - 1;


        uint8_t data[][2] ={{ 0x09, 0x00 }, { 0x0c, 0x01 }, { 0x0f, 0x00 }, { 0x0A, 0x01 }, { 0x0B, 0x07 }};

        command_settings(data, number_of_matrices, 5);

        Matrixz display(bus, cs, time, number_of_matrices, count, string_lenght);

        for(int i =0; i < number_of_matrices; i++)
        {
            display.render(char_space);
        }
        for(char c : input_string)
        {
            switch(c)
            {
                case '1' : display.render(char_one);    break;
                case '2' : display.render(char_two);    break;
                case '3' : display.render(char_three);  break;
                case '4' : display.render(char_four);   break;
                case '5' : display.render(char_five);   break;
                case '6' : display.render(char_six);    break;
                case '7' : display.render(char_seven);  break;
                case '8' : display.render(char_eight);  break;
                case '9' : display.render(char_nine);   break;
                case '0' : display.render(char_ten);    break;
                case '+' : display.render(char_plus);   break;
                case '-' : display.render(char_minus);  break;
            }
        }
        for(int i =0; i < number_of_matrices; i++)
        {
            display.render(char_space);
        }
        clean(bus, cs, number_of_matrices, count);
    }

    void command_settings(const uint8_t data[][2], int number_of_matrices , int count)
    {
        uint8_t temp[1000];
        for(int i = 0; i < count ;i++)
        {
            int l = 0;
            for(int k = 0; k < number_of_matrices; k++)
            {
                temp[l] = {data[i][0]};
                l++;
                temp[l] = {data[i][1]};
                l++;
            }
            bus.write_and_read(cs, 2*number_of_matrices, temp , nullptr);    //data is send over SPI to MAX7219. Only write, read is voided
        }
    }
};

