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

