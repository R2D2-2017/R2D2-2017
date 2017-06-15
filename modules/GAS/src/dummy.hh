//===========================================================//
//             Copyright Mike Hilhorst 2016.                 //
// Distributed under the Boost Software License, Version 1.0.//
//    (See accompanying file LICENSE_1_0.txt or copy at      //
//          http://www.boost.org/LICENSE_1_0.txt)            //
//===========================================================//
 
#ifndef DUMMY_HPP
#define DUMMY_HPP
///Dummy contains a copy function
//
///Copier is a function that creates a non const matrix(matrix_dummy) from data(data_input). \n
///The advantage of this is that your orginal data won't be altert. \n
///Example: You want to render Hello, but you want it rotated 90\370. if you send you orginal matrix, it will be rotated. \n
///Then displayed, but then rotated again and then displayed. Copy would be send, rotated, displayed. \n 
///The a other copy will be made and  send, rotated, displayed
class dummy
{
private:
uint8_t (*data_input)[8];
uint8_t (*matrix_dummy)[8];
int count;

public:
    dummy(uint8_t (*data_input)[8], uint8_t (*matrix_dummy)[8], int count):
    data_input(data_input), matrix_dummy(matrix_dummy), count(count)
    {};
    
       
        ///-data_input is the data that will be copyed. \n
        ///-matrix_data is the copy. \n
        ///-count: Size of matrix in pixels. \n
        void copier()
        {
            for(int i=0; i<count; i++)
            {
                for(int j=0; j < count; j++)
                {
                    matrix_dummy[i][j]=data_input[i][j];
                }
            }
        }
};

#endif // DUMMY_HPP
