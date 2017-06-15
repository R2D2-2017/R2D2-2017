//===========================================================//
//             Copyright Mike Hilhorst 2016.                 //
// Distributed under the Boost Software License, Version 1.0.//
//    (See accompanying file LICENSE_1_0.txt or copy at      //
//          http://www.boost.org/LICENSE_1_0.txt)            //
//===========================================================//
 
#ifndef ROTATE_HPP
#define ROTATE_HPP

/// Rotate contains a rotator function.
//
/// Rotate is a function that rotates a matrix.
/// The size of the matrix can devined wtih count. \n
/// Count is number of rows and columns. This is because of the way the fucntion works. \n 
/// rotate_matrix() gives the to be rotated data to rotator() \n \n
/// Example: matrix is 4x4, count 4. It takes (0,0),(3,0),(3,3),(0,3). Then it will rewrite this to: (3,0),(3,3),(0,3),(0,0. \n
/// Now it is rotated.next it takes (1,0),(2,0),(3,2),(1,3). Then it will rewrite this to: (2,0),(3,2),(1,3),(1,0). \n
/// Eventually it will have rotated the whole matrix. \n \n
/// The matrix it self will be altered, so i advise you to send a copy of your matrix to it. \n

class rotate
{
private:
    uint8_t (*matrix)[8];
    int rotation;
    int count;
    uint8_t a;
    uint8_t b;
    uint8_t c;
    uint8_t d;
    
public:
    rotate(uint8_t (*matrix)[8],int rotation, int count):
    matrix(matrix), rotation(rotation), count(count)
    {};
    
        ///Rotate is a function that rotates matrices, in steps of 90 degrees. \n\n
        ///Varibles used in rotate_matrix(): \n
        ///-matrix: Input data, the matrix its self will be altered, expectation is a (uint8_t)matrix[8][8]. \n
        ///-rotation: Number of time you desire to rotate the matrix with 90 degrees. \n
        ///-count: Size of matrix, this way you can rotate parts of the matrix. \n
        void rotate_matrix()
        {
            while(rotation>0)
            {
                for(int i=0; i<count/2; i++)
                {
                    for(int j=0; j<(count+1)/2; j++)
                    {
                        rotator(matrix[i][j], matrix[count-1-j][i], matrix[count-1-i][count-1-j], matrix[j][count-1-i]);
                    }
                }
                rotation--;
            }
        }
        ///Rotator is a function that rotates teh data given by rotate. \n \n
        ///varibles used in rotator(): \n
        ///-a will become b. \n
        ///-b will become c. \n
        ///-c will become d. \n
        ///-d will become a. \n
        void rotator(uint8_t & a, uint8_t & b, uint8_t & c, uint8_t & d)
        {
            uint8_t temp = a;
            a = b;
            b = c;
            c = d;
            d = temp;
        }

};

#endif // ROTATE_HPP
