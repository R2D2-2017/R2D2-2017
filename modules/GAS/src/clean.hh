//===========================================================//
//             Copyright Mike Hilhorst 2016.                 //
// Distributed under the Boost Software License, Version 1.0.//
//    (See accompanying file LICENSE_1_0.txt or copy at      //
//          http://www.boost.org/LICENSE_1_0.txt)            //
//===========================================================//
 
#ifndef CLEAN_HPP
#define CLEAN_HPP
/// Clean contains a cleaner funcion
//
/// Cleaner is a function that sets all leds from the matrices "off". Puts every register on 0x00. \n
/// The way this is done is a counter from 0 to count. \n
/// So this is only reuseable when registers are numberd from 0 to count. \n

#include "wrap-hwlib.hh"
class clean
{
private:
    hwlib::spi_bus & bus; 
    hwlib::pin_out & cs;
    uint8_t walk[1000];    
    int number_of_matrices;
    int count;
public:
   
    clean(hwlib::spi_bus & bus, hwlib::pin_out & cs, int number_of_matrices, int count):
    bus(bus), cs(cs), number_of_matrices(number_of_matrices), count(count)
    {};
        
        ///-number_of_matrices: number of martices you want to clean. \n
        ///-count: number of rows you want to clean on all the matrices. \n
        void cleaner()  
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
};

#endif // CLEAN_HPP
