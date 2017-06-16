//===========================================================//
//             Copyright Mike Hilhorst 2016.                 //
// Distributed under the Boost Software License, Version 1.0.//
//    (See accompanying file LICENSE_1_0.txt or copy at      //
//          http://www.boost.org/LICENSE_1_0.txt)            //
//===========================================================//
#pragma once

#include <array>
#include "wrap-hwlib.hh"


class command
{
private:
    hwlib::spi_bus & bus; 
    hwlib::pin_out & cs;
    uint8_t (*data)[8][2];
    uint8_t walk[1000];
    int time;
    int number_of_matrices;
    int count;
    int string_lenght;
    uint8_t matrix_data[8][2];
    uint8_t matrix_output[8][8];
    uint8_t array_data[1000][8][2];

public:
    command(hwlib::spi_bus & bus, hwlib::pin_out & cs, uint8_t (*data)[8][2], int & time, int & number_of_matrices , int & count, int & string_lenght):
    bus(bus), cs(cs), data(data), time(time), number_of_matrices(number_of_matrices), count(count), string_lenght(string_lenght)
    {};

    void commander();

    void command_settings(const uint8_t (*data)[2]);

    void cleaner();

    void coverter(uint8_t (*matrix_temp)[8], uint8_t (*matrix_data)[2]);

    void render(uint8_t (*render_input)[8]);

};





