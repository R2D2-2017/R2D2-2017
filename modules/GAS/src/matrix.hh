//
// Created by MuscioCraft on 16-6-2017.
//

#pragma once

#include "wrap-hwlib.hh"
#include "command.hh"
#include "mbin_to_mhex.hh"


class Matrixz {

private:
    hwlib::spi_bus & bus;
    hwlib::pin_out & cs;
    int time;
    int number_of_matrices;
    int count;
    int string_lenght;
    uint8_t matrix_data[8][2];
    uint8_t matrix_output[8][8];
    uint8_t array_data[1000][8][2];


public:

    Matrixz(hwlib::spi_bus & bus, hwlib::pin_out & cs, int time, int number_of_matrices, int count, int string_lenght):
            bus(bus), cs(cs), time(time), number_of_matrices(number_of_matrices), count(count), string_lenght(string_lenght){};

    void render(uint8_t (*render_input)[8]);

};



