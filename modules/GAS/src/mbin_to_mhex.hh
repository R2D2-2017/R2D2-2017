//===========================================================//
//             Copyright Mike Hilhorst 2016.                 //
// Distributed under the Boost Software License, Version 1.0.//
//    (See accompanying file LICENSE_1_0.txt or copy at      //
//          http://www.boost.org/LICENSE_1_0.txt)            //
//===========================================================//
 
#ifndef MBIN_TO_MHEX_HPP
#define MBIN_TO_MHEX_HPP
#include <array>
#include "wrap-hwlib.hh"

class mbin_to_mhex
{
private:
uint8_t (*matrix)[8];
uint8_t (*matrix_data)[2];
int inverd;
public:
///converter this function translates an 8x8 matrix in an 8x2 matrix.
//
///Input is 8x8 uint8_t matrix. It's data is shifted in to a uint8_t per row. \n
///This way you make from 64 bits, 8 uint8_ts. This is easyer to read out. \n
///Now theres added register data, so reading this matrix out will give you, the data to write and the register to write to. \n
///The way its gets written in to the matrix is that (*matrix)[0]is the rigster adress and (*matrix)[1] is the data. \n
/// this makes it reuseble you can ignore the first adress and only use the data, then pare it ypu self to other adresses. \n
        mbin_to_mhex(uint8_t (*matrix)[8], uint8_t (*matrix_data)[2], int inverd=0):
        matrix(matrix), matrix_data(matrix_data), inverd(inverd)
        {};

        void coverter()
        
        ///-matrix input data. \n
        ///-matrix_data output data. \n
        ///-inverd, werther you want the matrix_data be filled with normal or invered data. \n
        /// \n
        ///This function uses bitwise oparations to set a row from a matrix in to a tmp. \n
        ///The first number put in to matrix_data is the row number, second value is the column data. \n
        {
            for(int i = 0; i < 8; i++)                                  // Row 0-7;
            {
                uint8_t matrix_tmp[8][8];                                  // Temp matix to store and alter data.
                uint8_t tmp = 0;                                           // An temp uint8_t, in to this uint8_t data will be shifted to make from an matrix row, 1 uint8_t.
                int counter = 0;                                        // Counter column 7-0;
                for(int j = 8; j >= 0; j--)                             // J is an shifter, matrix(_tmp) will be shifted J places in tmp.
                {
                    if(inverd != 0 )                                    // Checks if inversion is true.
                    {
                        if(matrix[i][counter-1]==0)                     // Checks if matrix is an 0
                        {
                            matrix_tmp[i][counter-1]=1;                 // If true matrix_tmp equals 1
                        }                                               // Now the value is inverded
                        else
                        {
                            matrix_tmp[i][counter-1]=0;
                        }                                               // Matrix_tmp is OR-ed with tmp, tmp is 0 so the data from matrix_tmp is put in to tmp.
                        tmp = tmp | matrix_tmp[i][counter-1] << (j);    // and then shifed J times.
                        counter++;                                      // Next column!
                    }
                    else
                    {                                                   // Matrix is ORed with tmp, tmp is 0 so the data from matrix is put in to tmp
                        tmp = tmp | matrix[i][counter-1] << (j);        // and then shifed J times.
                        counter++;                                      // Next column!
                    }
                }                                                       //matrix_data is and 8x2 marix, it will be filled with:
                matrix_data[i][0] = i+1;                                //Row number. i+1 is because the rows start from 1 and NOT 0.
                matrix_data[i][1] = tmp;                                //Column data. 
            }  

        }

    
};

#endif // MBIN_TO_MHEX_HPP
