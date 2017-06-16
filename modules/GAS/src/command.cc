//
// Created by MuscioCraft on 16-6-2017.
//

#include "command.hh"

void command::commander()
{
    int tmp = number_of_matrices;
    uint8_t temp[1000];
    for(int i = 0; i < string_lenght-tmp;i++)
    {
        for(int m = 0; m < count ;m++)
        {
            for(int j =0; j <= count; j++)
            {
                int l = 0;
                for(int k = 0; k < number_of_matrices; k++)
                {
                    temp[l] = {(uint8_t)j};
                    l++;
                    temp[l] = {data[i+k][j-1][1]};
                    l++;
                }
                bus.write_and_read(cs, 2*number_of_matrices, temp , nullptr);
            }
            hwlib::wait_ms(time/7);
        }
        //hwlib::wait_ms(time);
        cleaner();
    }
}

void command::command_settings(const uint8_t (*data)[2])
{
    uint8_t temp[1000];
    for(int i = 0; i < 5 ;i++) // 5 number of commands
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


void command::cleaner()
{
    for(int i = 1; i <= count; i++)
    {
        int n =0;
        for(int j = number_of_matrices; j > 0; j--)
        {
            walk[n]= (uint8_t)i ;
            n++;
            walk[n]= 0x00 ;
            n++;
        }
        bus.write_and_read(cs, 2*number_of_matrices, walk, nullptr);
    }
}

void command::coverter(uint8_t (*matrix_temp)[8], uint8_t (*matrix_data)[2])
{
    for(int i = 0; i < 8; i++)                                  // Row 0-7;
    {
        uint8_t tmp = 0;                                           // An temp uint8_t, in to this uint8_t data will be shifted to make from an matrix row, 1 uint8_t.
        int counter = 0;                                        // Counter column 7-0;
        for(int j = 8; j >= 0; j--)                             // J is an shifter, matrix(_tmp) will be shifted J places in tmp.
        {
            tmp = tmp | matrix_temp[i][counter-1] << (j);        // and then shifed J times.
            counter++;                                      // Next column!
        }                                                       //matrix_data is and 8x2 marix, it will be filled with:
        matrix_data[i][0] = i+1;                                //Row number. i+1 is because the rows start from 1 and NOT 0.
        matrix_data[i][1] = tmp;                                //Column data.
    }

}

void command::render(uint8_t (*render_input)[8]) {
    command Aether(bus, cs, array_data, time, number_of_matrices, count, string_lenght);


    Aether.coverter(render_input, matrix_data);
    static int j = 0;
    for (int i = 0; i < count; i++) {
        array_data[j][i][1] = matrix_data[i][1];
    }
    j++;
    if (j == string_lenght) {
        Aether.commander();
    }
}

