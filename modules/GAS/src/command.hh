//===========================================================//
//             Copyright Mike Hilhorst 2016.                 //
// Distributed under the Boost Software License, Version 1.0.//
//    (See accompanying file LICENSE_1_0.txt or copy at      //
//          http://www.boost.org/LICENSE_1_0.txt)            //
//===========================================================//
 
#ifndef COMMAND_HPP
#define COMMAND_HPP
#include <array>
#include "wrap-hwlib.hh"
#include "clean.hh"
///Command contains a function that sends data to the MAX7219 thru SPI.
//
///Commander gets a 3d list( (*data)[8][2] ). Command uses 3 for loops to read out the list. 
///First loop is with letter out of the list will be displayed. \n
///Second loop is for getting the data per row. \n
///Final loop is for the amount of matrices. \n
///It makes it posseble to grap the last(or next) letter out of the data input.  \n
class command
{
private:
    hwlib::spi_bus & bus; 
    hwlib::pin_out & cs;
     uint8_t (*data)[8][2];
    int mode;
    int time;
    int number_of_matrices;
    int count;
    int string_lenght;
public:
    command(hwlib::spi_bus & bus, hwlib::pin_out & cs, uint8_t (*data)[8][2], int & mode, int & time, int & number_of_matrices , int & count, int & string_lenght):
    bus(bus), cs(cs), data(data), mode(mode), time(time), number_of_matrices(number_of_matrices), count(count), string_lenght(string_lenght)
    {};
        ///-bus is spi bus. \n
        ///-cs is spi cs. \n
        ///-render_input is the data that will be displayed on the matrix. \n
        ///-time is the time(in ms) that the matrix will be displayed. \n
        ///-mode is the modes the matrix will be dysplayed in. \n
        ///-inverd is whether the data is inverder or not. 0 is off, !0 is on. \n
        ///-rotation is the number of times render_input will be rotated 90 degeers. \n
        ///-number_of_matrices the number of matrices where you want to display on. \n
        ///-count number of size of martix in pixels. \n
        ///-string_lenght the lenght of the string you want to display. \n
        /// \n
        /// Modes:
        /// 1. flashing
        /// 2. shifting right to left
        /// 3. shifting left to right
        void commander()
        {
            int tmp = number_of_matrices;
            if(mode==1)
            { 
                tmp =0;
            }
            uint8_t temp[1000];
            for(int i = 0; i < string_lenght-tmp;i++)
            {
                for(int m = 0; m < count ;m++)                                          
                {  
                    for(int j =0; j <= count; j++)
                    { 
                        int l = 0;
                        if(mode==1)
                        {
                            for(int k = 0; k < number_of_matrices; k++)
                            {
                                temp[l] = {(uint8_t)j};               
                                l++;
                                temp[l] = {data[i][j-1][1]};
                                l++;
                            }
                            bus.write_and_read(cs, 2*number_of_matrices, temp , nullptr);
                        }
                        if(mode==2)
                        {
                            for(int k = 0; k < number_of_matrices; k++)
                            {
                                temp[l] = {(uint8_t)j};               
                                l++;
                                temp[l] = {data[i+k][j-1][1]};     
                                l++;
                            }
                            bus.write_and_read(cs, 2*number_of_matrices, temp , nullptr);
                        }
                        if(mode==3)
                        {
                            for(int k = 0; k < number_of_matrices; k++)
                            {
                                temp[l] = {(uint8_t)j};               
                                l++;
                                temp[l] = {data[string_lenght-number_of_matrices-i+k][j-1][1]};     
                                l++;
                            }
                            bus.write_and_read(cs, 2*number_of_matrices, temp , nullptr);
                       }
                       if(mode==4)
                       {
                           for(int k = 0; k < number_of_matrices; k++)
                           {
                               temp[l] = {(uint8_t)j};               
                               l++;
                               temp[l] = {data[i][j-1+m][1]};
                               l++;
                           }
                           bus.write_and_read(cs, 2*number_of_matrices, temp , nullptr);
                       }
                       if(mode==5)
                       {
                           for(int k = 0; k < number_of_matrices; k++)
                           {
                               temp[l] = {(uint8_t)j};               
                               l++;
                               temp[l] = {data[string_lenght-number_of_matrices-i][j-1-m][1]};
                               l++;
                           }
                           bus.write_and_read(cs, 2*number_of_matrices, temp , nullptr);
                       }
                    }
                    hwlib::wait_ms(time/7);
                }
            //hwlib::wait_ms(time);
            clean Alastor (bus, cs, number_of_matrices, count);
            Alastor.cleaner();
            }
        }

};

#endif // COMMAND_HPP
