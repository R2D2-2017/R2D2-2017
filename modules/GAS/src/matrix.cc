//
// Created by MuscioCraft on 16-6-2017.
//

#include "matrix.hh"


void Matrixz::render(uint8_t (*render_input)[8]) {
    command Aether(bus, cs, array_data, time, number_of_matrices, count, string_lenght);
    mbin_to_mhex Aeolus(render_input, matrix_data);

    Aeolus.coverter();
    static int j = 0;
    for (int i = 0; i < count; i++) {
        array_data[j][i][1] = matrix_data[i][1];
    }
    j++;
    if (j == string_lenght) {
        Aether.commander();
    }
}