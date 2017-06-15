//===========================================================//
//             Copyright Mike Hilhorst 2016.                 //
// Distributed under the Boost Software License, Version 1.0.//
//    (See accompanying file LICENSE_1_0.txt or copy at      //
//          http://www.boost.org/LICENSE_1_0.txt)            //
//===========================================================//
 
#ifndef MAX7219_HPP
#define MAX7219_HPP

#include "wrap-hwlib.hh"
#include "string.h"
#include "command.hh"
#include "mbin_to_mhex.hh"
#include "clean.hh"
#include "dummy.hh"
#include "rotate.hh"
///This is a storage for: 
//
///This class holds all supported charactres, test modes, render, setiings and the sting to dislpay tekst switch. \n
///The characters are all 8x8 (uint8_t)matrices. \n
///Test mode is a mode to test the matrix, it will display every currunt supported charchter. rotated and sometimes inverded. \n
///Render makes a copy of the orignal 8x8 (uint8_t)matrix, sends that to mbin_to_mhex. mbin_to_mhex will process that in a 8x2 (uint8_t)matrix. \n
///Render will take that 8x2 (uint8_t)martix and put it in a ?x8x2 (uint8_t)matrix. When all charachters are put in the ?x8x2 (uint8_t)matrix \n
///render will send it to command().
///Settings is a ?x2 matrix of settings.
///The switch take a input string and with every supported it will call render with the there to belonning character.
class MAX7219
{
private:
    //========spi========//
    hwlib::spi_bus & bus; 
    hwlib::pin_out & cs;
    //===================//
    
    //========varibles========//
    
    //===ints==//
    int count;
    int mode;
    int time;
    int rotation;
    int number_of_matrices;
    int letter_counter=0;
    
    //===uint8_t matrices===//
    uint8_t matrix_data[8][2];
    uint8_t matrix_rotate[8][8];
    uint8_t matrix_output[8][8];
    uint8_t matrix_dummy[8][8];            
    uint8_t array_data[1000][8][2];
    
    //========================//

    //==========chars==========//
    //A
    uint8_t char_A[8][8] = {{0,0,0,0,0,0,0,0},{0,0,0,1,1,0,0,0},{0,0,1,1,1,1,0,0},{0,1,1,0,0,1,1,0},{0,1,1,1,1,1,1,0},{0,1,1,0,0,1,1,0},{0,1,1,0,0,1,1,0},{0,0,0,0,0,0,0,0}};
    //B
    uint8_t char_B[8][8] = {{0,0,0,0,0,0,0,0},{0,1,1,1,1,1,0,0},{0,1,0,0,0,0,1,0},{0,1,1,1,1,1,0,0},{0,1,0,0,0,0,1,0},{0,1,0,0,0,0,1,0},{0,1,1,1,1,1,0,0},{0,0,0,0,0,0,0,0}};
    //C
    uint8_t char_C[8][8] = {{0,0,0,0,0,0,0,0},{0,0,1,1,1,1,1,0},{0,1,1,1,1,1,1,0},{0,1,1,0,0,0,0,0},{0,1,1,0,0,0,0,0},{0,1,1,1,1,1,1,0},{0,0,1,1,1,1,1,0},{0,0,0,0,0,0,0,0}};
    //D
    uint8_t char_D[8][8] = {{0,0,0,0,0,0,0,0},{0,1,1,1,1,1,0,0},{0,1,1,1,1,1,1,0},{0,1,1,0,0,1,1,0},{0,1,1,0,0,1,1,0},{0,1,1,1,1,1,1,0},{0,1,1,1,1,1,0,0},{0,0,0,0,0,0,0,0}};
    //E
    uint8_t char_E[8][8] = {{0,0,0,0,0,0,0,0},{0,1,1,1,1,1,1,0},{0,1,1,0,0,0,0,0},{0,1,1,1,1,1,0,0},{0,1,1,1,1,1,0,0},{0,1,1,0,0,0,0,0},{0,1,1,1,1,1,1,0},{0,0,0,0,0,0,0,0}};
    //F
    uint8_t char_F[8][8] = {{0,0,0,0,0,0,0,0},{0,1,1,1,1,1,1,0},{0,1,1,1,1,1,1,0},{0,1,1,0,0,0,0,0},{0,1,1,1,1,0,0,0},{0,1,1,1,1,0,0,0},{0,1,1,0,0,0,0,0},{0,0,0,0,0,0,0,0}}; 
    //G
    uint8_t char_G[8][8] = {{0,0,0,0,0,0,0,0},{0,0,1,1,1,1,1,0},{0,1,1,1,1,1,1,0},{0,1,1,0,0,0,0,0},{0,1,1,0,1,1,1,0},{0,1,1,0,0,1,1,0},{0,1,1,1,1,1,1,0},{0,0,0,0,0,0,0,0}};
    //H
    uint8_t char_H[8][8] = {{0,0,0,0,0,0,0,0},{0,1,1,0,0,1,1,0},{0,1,1,0,0,1,1,0},{0,1,1,1,1,1,1,0},{0,1,1,1,1,1,1,0},{0,1,1,0,0,1,1,0},{0,1,1,0,0,1,1,0},{0,0,0,0,0,0,0,0}};
    //I
    uint8_t char_I[8][8] = {{0,0,0,0,0,0,0,0},{0,0,1,1,1,1,0,0},{0,0,0,1,1,0,0,0},{0,0,0,1,1,0,0,0},{0,0,0,1,1,0,0,0},{0,0,0,1,1,0,0,0},{0,0,1,1,1,1,0,0},{0,0,0,0,0,0,0,0}};
    //J
    uint8_t char_J[8][8] = {{0,0,0,0,0,0,0,0},{0,0,0,0,0,1,0,0},{0,0,0,0,0,1,0,0},{0,0,0,0,0,1,0,0},{0,1,0,0,0,1,0,0},{0,1,0,0,0,1,0,0},{0,0,1,1,1,0,0,0},{0,0,0,0,0,0,0,0}};
    //K
    uint8_t char_K[8][8] = {{0,0,0,0,0,0,0,0},{0,1,1,0,0,1,1,0},{0,1,1,0,1,1,0,0},{0,1,1,1,1,0,0,0},{0,1,1,1,1,0,0,0},{0,1,1,0,1,1,0,0},{0,1,1,0,0,1,1,0},{0,0,0,0,0,0,0,0}};
    //L
    uint8_t char_L[8][8] = {{0,0,0,0,0,0,0,0},{0,1,1,0,0,0,0,0},{0,1,1,0,0,0,0,0},{0,1,1,0,0,0,0,0},{0,1,1,0,0,0,0,0},{0,1,1,1,1,1,1,0},{0,1,1,1,1,1,1,0},{0,0,0,0,0,0,0,0}};
    //M
    uint8_t char_M[8][8] = {{0,0,0,0,0,0,0,0},{0,1,1,0,0,1,1,0},{0,1,1,1,1,1,1,0},{0,1,0,1,1,0,1,0},{0,1,0,0,0,0,1,0},{0,1,0,0,0,0,1,0},{0,1,0,0,0,0,1,0},{0,0,0,0,0,0,0,0}};
    //N
    uint8_t char_N[8][8] = {{0,0,0,0,0,0,0,0},{0,0,1,1,1,1,0,0},{0,1,1,1,1,1,1,0},{0,1,1,0,0,1,1,0},{0,1,1,0,0,1,1,0},{0,1,1,0,0,1,1,0},{0,1,1,0,0,1,1,0},{0,0,0,0,0,0,0,0}};
    //O
    uint8_t char_O[8][8] = {{0,0,0,0,0,0,0,0},{0,0,1,1,1,1,0,0},{0,1,1,1,1,1,1,0},{0,1,1,0,0,1,1,0},{0,1,1,0,0,1,1,0},{0,1,1,1,1,1,1,0},{0,0,1,1,1,1,0,0},{0,0,0,0,0,0,0,0}};
    //P
    uint8_t char_P[8][8] = {{0,0,0,0,0,0,0,0},{0,1,1,1,1,1,1,0},{0,1,1,0,0,1,1,0},{0,1,1,0,0,1,1,0},{0,1,1,1,1,1,1,0},{0,1,1,0,0,0,0,0},{0,1,1,0,0,0,0,0},{0,0,0,0,0,0,0,0}};
    //Q
    uint8_t char_Q[8][8] = {{0,0,0,0,0,0,0,0},{0,0,1,1,1,1,0,0},{0,1,1,1,1,1,1,0},{0,1,1,0,0,1,1,0},{0,1,1,0,1,1,1,0},{0,1,1,1,1,1,1,0},{0,0,1,1,1,1,1,1},{0,0,0,0,0,0,1,1}};
    //R
    uint8_t char_R[8][8] = {{0,0,0,0,0,0,0,0},{0,1,1,1,1,1,0,0},{0,1,0,0,0,0,1,0},{0,1,1,1,1,1,0,0},{0,1,0,1,1,0,0,0},{0,1,0,0,1,1,0,0},{0,1,0,0,0,1,1,0},{0,0,0,0,0,0,0,0}};
    //S
    uint8_t char_S[8][8] = {{0,0,0,0,0,0,0,0},{0,0,1,1,1,1,1,0},{0,1,0,0,0,0,0,0},{0,0,1,1,1,1,0,0},{0,0,0,0,0,0,1,0},{0,0,0,0,0,0,1,0},{0,1,1,1,1,1,0,0},{0,0,0,0,0,0,0,0}};
    //T
    uint8_t char_T[8][8] = {{0,0,0,0,0,0,0,0},{0,1,1,1,1,1,1,0},{0,1,1,1,1,1,1,0},{0,0,0,1,1,0,0,0},{0,0,0,1,1,0,0,0},{0,0,0,1,1,0,0,0},{0,0,0,1,1,0,0,0},{0,0,0,0,0,0,0,0}};
    //U
    uint8_t char_U[8][8] = {{0,0,0,0,0,0,0,0},{0,1,1,0,0,1,1,0},{0,1,1,0,0,1,1,0},{0,1,1,0,0,1,1,0},{0,1,1,0,0,1,1,0},{0,1,1,0,0,1,1,0},{0,0,1,1,1,1,0,0},{0,0,0,0,0,0,0,0}};
    //V
    uint8_t char_V[8][8] = {{0,0,0,0,0,0,0,0},{0,1,1,0,0,1,1,0},{0,1,1,0,0,1,1,0},{0,1,1,0,0,1,1,0},{0,1,1,0,0,1,1,0},{0,0,1,1,1,1,0,0},{0,0,1,1,1,1,0,0},{0,0,0,0,0,0,0,0}};
    //W
    uint8_t char_W[8][8] = {{0,0,0,0,0,0,0,0},{0,1,0,0,0,0,1,0},{0,1,0,0,0,0,1,0},{0,1,0,0,0,0,1,0},{0,1,0,0,0,0,1,0},{0,1,0,1,1,0,1,0},{0,0,1,0,0,1,0,0},{0,0,0,0,0,0,0,0}};
    //X
    uint8_t char_X[8][8] = {{0,0,0,0,0,0,0,0},{0,1,0,0,0,0,1,0},{0,0,1,0,0,1,0,0},{0,0,0,1,1,0,0,0},{0,0,0,1,1,0,0,0},{0,0,1,0,0,1,0,0},{0,1,0,0,0,0,1,0},{0,0,0,0,0,0,0,0}};
    //Y
    uint8_t char_Y[8][8] = {{0,0,0,0,0,0,0,0},{0,1,0,0,0,0,1,0},{0,1,1,0,0,1,1,0},{0,0,1,1,1,1,0,0},{0,0,0,1,1,0,0,0},{0,0,0,1,1,0,0,0},{0,0,0,1,1,0,0,0},{0,0,0,0,0,0,0,0}};
    //Z
    uint8_t char_Z[8][8] = {{0,0,0,0,0,0,0,0},{0,1,1,1,1,1,1,0},{0,0,0,0,0,1,1,0},{0,0,0,0,1,1,0,0},{0,0,0,1,1,0,0,0},{0,0,1,1,0,0,0,0},{0,1,1,1,1,1,1,0},{0,0,0,0,0,0,0,0}};
    //space
    uint8_t char_space[8][8] = {{0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0}};
    //!
    uint8_t char_uit[8][8] = {{0,0,0,0,0,0,0,0},{0,0,0,1,1,0,0,0},{0,0,0,1,1,0,0,0},{0,0,0,1,1,0,0,0},{0,0,0,1,1,0,0,0},{0,0,0,0,0,0,0,0},{0,0,0,1,1,0,0,0},{0,0,0,0,0,0,0,0}};
    //random
    uint8_t char_random[8][8];
    //underscore
    uint8_t char_underscore[8][8] = {{0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0},{1,1,1,1,1,1,1,1}};
    //?
    uint8_t char_question[8][8] = {{0,0,0,0,0,0,0,0},{0,0,1,1,1,1,0,0},{0,0,0,0,0,0,1,0},{0,0,0,0,0,0,1,0},{0,0,0,1,1,1,0,0},{0,0,0,0,0,0,0,0},{0,0,0,1,0,0,0,0},{0,0,0,0,0,0,0,0}};
    //point
    uint8_t char_point[8][8] = {{0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0},{0,0,0,1,1,0,0,0},{0,0,0,1,1,0,0,0},{0,0,0,0,0,0,0,0}};
    //comma
    uint8_t char_comma[8][8] = {{0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0},{0,0,0,1,1,0,0,0},{0,0,0,1,1,0,0,0},{0,0,0,0,0,1,0,0}};
    //square_L
    uint8_t char_square_L[8][8] = {{0,0,0,0,0,0,0,0},{0,0,1,1,1,1,0,0},{0,0,1,0,0,0,0,0},{0,0,1,0,0,0,0,0},{0,0,1,0,0,0,0,0},{0,0,1,0,0,0,0,0},{0,0,1,1,1,1,0,0},{0,0,0,0,0,0,0,0}};
    //square_R
    uint8_t char_square_R[8][8] = {{0,0,0,0,0,0,0,0},{0,0,1,1,1,1,0,0},{0,0,0,0,0,1,0,0},{0,0,0,0,0,1,0,0},{0,0,0,0,0,1,0,0},{0,0,0,0,0,1,0,0},{0,0,1,1,1,1,0,0},{0,0,0,0,0,0,0,0}};
    //1,
    uint8_t char_one[8][8] = {{0,0,0,0,0,0,0,0},{0,0,1,1,1,0,0,0},{0,1,1,1,1,0,0,0},{0,0,0,1,1,0,0,0},{0,0,0,1,1,0,0,0},{0,0,0,1,1,0,0,0},{0,1,1,1,1,1,1,0},{0,0,0,0,0,0,0,0}};
    //2
    uint8_t char_two[8][8] = {{0,0,0,0,0,0,0,0},{0,1,1,1,1,1,0,0},{0,0,0,0,0,1,1,0},{0,0,0,0,0,1,1,0},{0,0,0,0,1,1,0,0},{0,0,0,1,1,0,0,0},{0,1,1,1,1,1,1,0},{0,0,0,0,0,0,0,0}};
    //3
    uint8_t char_three[8][8] = {{0,0,0,0,0,0,0,0},{0,1,1,1,1,1,0,0},{0,0,0,0,0,1,1,0},{0,0,0,1,1,1,1,0},{0,0,0,1,1,1,1,0},{0,0,0,0,0,1,1,0},{0,1,1,1,1,1,0,0},{0,0,0,0,0,0,0,0}};
    //4,
    uint8_t char_four[8][8] = {{0,0,0,0,0,0,0,0},{0,0,0,0,0,1,0,0},{0,0,0,0,1,1,0,0},{0,0,0,1,0,1,0,0},{0,0,1,0,0,1,0,0},{0,1,1,1,1,1,1,0},{0,0,0,0,0,1,0,0},{0,0,0,0,0,0,0,0}};
    //5
    uint8_t char_five[8][8] = {{0,0,0,0,0,0,0,0},{0,1,1,1,1,1,1,0},{0,1,0,0,0,0,0,0},{0,1,1,1,1,1,0,0},{0,0,0,0,0,0,1,0},{0,0,0,0,0,0,1,0},{0,1,1,1,1,1,0,0},{0,0,0,0,0,0,0,0}};
    //6
    uint8_t char_six[8][8] = {{0,0,0,0,0,0,0,0},{0,0,1,1,1,1,1,0},{0,1,0,0,0,0,0,0},{0,1,1,1,1,1,0,0},{0,1,0,0,0,0,1,0},{0,1,0,0,0,0,1,0},{0,0,1,1,1,1,0,0},{0,0,0,0,0,0,0,0}};
    //7
    uint8_t char_seven[8][8] = {{0,0,0,0,0,0,0,0},{0,1,1,1,1,1,1,0},{0,0,0,0,0,1,1,0},{0,0,0,0,1,1,0,0},{0,0,0,1,1,0,0,0},{0,0,1,1,0,0,0,0},{0,1,1,0,0,0,0,0},{0,0,0,0,0,0,0,0}};
    //8
    uint8_t char_eight[8][8] = {{0,0,0,0,0,0,0,0},{0,0,1,1,1,1,0,0},{0,1,0,0,0,0,1,0},{0,0,1,1,1,1,0,0},{0,1,0,0,0,0,1,0},{0,1,0,0,0,0,1,0},{0,0,1,1,1,1,0,0},{0,0,0,0,0,0,0,0}};
    //9
    uint8_t char_nine[8][8] = {{0,0,0,0,0,0,0,0},{0,0,1,1,1,1,0,0},{0,1,0,0,0,0,1,0},{0,0,1,1,1,1,1,0},{0,0,0,0,0,0,1,0},{0,0,0,0,0,0,1,0},{0,0,1,1,1,1,0,0},{0,0,0,0,0,0,0,0}};
    //0,
    uint8_t char_ten[8][8] = {{0,0,0,0,0,0,0,0},{0,0,1,1,1,1,0,0},{0,1,0,0,0,0,1,0},{0,1,0,0,0,0,1,0},{0,1,0,0,0,0,1,0},{0,1,0,0,0,0,1,0},{0,0,1,1,1,1,0,0},{0,0,0,0,0,0,0,0}};
    //-
    uint8_t char_minus[8][8] = {{0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0},{0,1,1,1,1,1,1,0},{0,1,1,1,1,1,1,0},{0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0}};
    //+
    uint8_t char_plus[8][8] = {{0,0,0,0,0,0,0,0},{0,0,0,1,1,0,0,0},{0,0,0,1,1,0,0,0},{0,1,1,1,1,1,1,0},{0,1,1,1,1,1,1,0},{0,0,0,1,1,0,0,0},{0,0,0,1,1,0,0,0},{0,0,0,0,0,0,0,0}};
    //*
    uint8_t char_multiply[8][8] = {{0,0,0,0,0,0,0,0},{0,1,0,1,1,0,1,0},{0,0,1,1,1,1,0,0},{0,1,1,1,1,1,1,0},{0,1,1,1,1,1,1,0},{0,0,1,1,1,1,0,0},{0,1,0,1,1,0,1,0},{0,0,0,0,0,0,0,0}};
    ///
    uint8_t char_divide[8][8] = {{0,0,0,0,0,0,0,0},{0,0,0,0,0,1,1,0},{0,0,0,0,1,1,0,0},{0,0,0,1,1,0,0,0},{0,0,1,1,0,0,0,0},{0,1,1,0,0,0,0,0},{0,1,0,0,0,0,0,0},{0,0,0,0,0,0,0,0}};
    //=
    uint8_t char_equal[8][8] = {{0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0},{0,1,1,1,1,1,1,0},{0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0},{0,1,1,1,1,1,1,0},{0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0}};
    //;
    uint8_t char_semicolom[8][8] = {{0,0,0,0,0,0,0,0},{0,0,0,1,1,0,0,0},{0,0,0,1,1,0,0,0},{0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0},{0,0,0,1,1,0,0,0},{0,0,0,1,1,0,0,0},{0,0,0,0,1,0,0,0}};
    //=========================//
    
public:
    MAX7219(hwlib::spi_bus & bus, hwlib::pin_out & cs):
    bus(bus), cs(cs)
    {
        hwlib::wait_ms(1000);       // Hammertime
        hwlib::cout << "=== BEGINING ===\n";
        
        char input_string[] = {"Hello Dave!"};            // input string
        hwlib::cout << "String lenght :" << strlen(input_string);   //lenght of string
        
        number_of_matrices = 4;                                     //Amount of matrices where you want to display on.
        count = 8;                                                  //Amount of pixels on the matrix.
        rotation =  0;                                              //rotation 1=90, 2=180, 3=270, 4=360 etc.
        time = 500;                                                 //The time in ms that the characters will be displayed on the screen
                                                //If inverded 0 = off, !0= on/
        mode = 2;                                                   //The mode the characters will be displayed in
                                                                    // ============================================ //
                                                                    //  1. flashing                                 //
                                                                    //  2. shifting from left to right              //
                                                                    //  3. shifting from right to left              //
                                                                    // ============================================ //
                    
                    
        int string_lenght = strlen(input_string)+number_of_matrices*2;
        
        uint8_t data[][2] ={{ 0x09, 0x00 },    //
                         { 0x0c, 0x01 },    //
                         { 0x0f, 0x00 },    // Test modes : off
                         { 0x0A, 0x0f },    // Intestety :  ~30% 
                         { 0x0B, 0x07 }};   //
        command_settings(data, number_of_matrices, 5);
        
        hwlib::wait_ms(1000);       // Hammertime
        
        //========== Settings display on console ===========//
                
        hwlib::cout << "\nMode:               " << mode;
        if(mode == 1){ hwlib::cout << " - flashing";}
        if(mode == 2){ hwlib::cout << " - shifting from left to right";} 
        if(mode == 3){ hwlib::cout << " - shifting from right to left";} 

        hwlib::cout << "\nTime:               " << time <<"ms";
        hwlib::cout << "\nRotation:           " << rotation*90 << "\370";
        hwlib::cout << "\nNumber of pixels:   " << count*count*number_of_matrices;
        hwlib::cout << "\nNumber of matrices: " << number_of_matrices;
        hwlib::cout << '\n';
        
        
        //==================================================//
  
        //=========== Output display on console ============//
       // while(true){
            hwlib::cout << "\nDisplayed text: ";
            for(int i =0; i < number_of_matrices; i++)
            {
                    render(char_space,       time, mode, rotation, number_of_matrices, count, string_lenght);
            }
            for(char c : input_string)              //This will go thru every element of input_string
            {
                switch(c) 
                {
                    case '1' : render(char_one,         time, mode, rotation, number_of_matrices, count, string_lenght);          hwlib::cout << '1';         break;
                    case '2' : render(char_two,         time, mode, rotation, number_of_matrices, count, string_lenght);          hwlib::cout << '2';         break;
                    case '3' : render(char_three,       time, mode, rotation, number_of_matrices, count, string_lenght);          hwlib::cout << '3';         break;
                    case '4' : render(char_four,        time, mode, rotation, number_of_matrices, count, string_lenght);          hwlib::cout << '4';         break;
                    case '5' : render(char_five,        time, mode, rotation, number_of_matrices, count, string_lenght);          hwlib::cout << '5';         break;
                    case '6' : render(char_six,         time, mode, rotation, number_of_matrices, count, string_lenght);          hwlib::cout << '6';         break;
                    case '7' : render(char_seven,       time, mode, rotation, number_of_matrices, count, string_lenght);          hwlib::cout << '7';         break;
                    case '8' : render(char_eight,       time, mode, rotation, number_of_matrices, count, string_lenght);          hwlib::cout << '8';         break;
                    case '9' : render(char_nine,        time, mode, rotation, number_of_matrices, count, string_lenght);          hwlib::cout << '9';         break;
                    case '0' : render(char_ten,         time, mode, rotation, number_of_matrices, count, string_lenght);          hwlib::cout << '0';         break;
                    case '+' : render(char_plus,        time, mode, rotation, number_of_matrices, count, string_lenght);          hwlib::cout << '+';         break;
                    case '-' : render(char_minus,       time, mode, rotation, number_of_matrices, count, string_lenght);          hwlib::cout << '-';         break;
            }
            }
            for(int i =0; i < number_of_matrices; i++)
            {
                    render(char_space,       time, mode, rotation, number_of_matrices, count, string_lenght);
            }
            
        
        //==================================================//

        clean(bus, cs, number_of_matrices, count);
         
        hwlib::cout << "\n\n====== END ======\n";
    }
    
        void command_settings(const uint8_t data[][2], int number_of_matrices , int count)
        ///Executing function, data[][2]: is the filled with hex codes that coronspond to registers of MAX7219. \n\n
        ///Count: is number off row that will be dysplayed. This is over thought choise. This gives more options. \n
        ///The function will send its data via SPI(write_and_read) to the MAX7219. \n
        {   
            uint8_t temp[1000];                                                                         
            for(int i = 0; i < count ;i++)                                           
            {
                int l = 0;
                for(int k = 0; k < number_of_matrices; k++)
                {
                    temp[l] = {data[i][0]};               
                    l++;
                    temp[l] = {data[i][1]};     
                    l++;
                }
                if(data[i][0]!=0x0B){                                                // checks if Scan limit isn't spoken to.
                    bus.write_and_read(cs, 2*number_of_matrices, temp , nullptr);    //data is send over SPI to MAX7219. Only write, read is voided
                }else{
                    bus.write_and_read(cs, 2*number_of_matrices, temp, temp);        //data is send over SPI to MAX7219. Write and read, scan limit is fetched
                    hwlib::cout << "\nScan_limit passed: " << (int)temp << "\n";     // and put in the consol.
                }            
            }
        }
       
        
        ///Render is a function that puts the to be displayed string, in to a format that command understands. \n
        ///Array_data is where the data is stored in. Array_data[number of chars][count][2]. \n\n
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
        void render(uint8_t render_input[8][8], int time, int mode, int rotation, int number_of_matrices, int count, int string_lenght)
        {   
            command Aether (bus, cs, array_data, mode, time, number_of_matrices, count, string_lenght);
            mbin_to_mhex Aeolus (matrix_dummy, matrix_data);
            rotate Ares (matrix_dummy, rotation, count);
            dummy Aristaeus (render_input, matrix_dummy, count);
            
            Aristaeus.copier();
            Ares.rotate_matrix();
            Aeolus.coverter();
            static int j=0;
                for(int i = 0; i<count; i++)
                {
                    array_data[j][i][1] = matrix_data[i][1];                       
                }
            j++;
            if(j==string_lenght)
            {
                
                Aether.commander();
                
            }
        }
        
        ///Tester s a function that tests the matrix. \n
        ///It will display every suported character. In different time, inverd and rotation.\n\n
        ///-mode is the modes the matrix will be dysplayed in. \n
        ///-number_of_matrices the number of matrices where you want to display on. \n
        ///-count number of size of martix in pixels. \n
        ///-string_lenght the lenght of the string you want to display. \n
        /// \n
        /// Modes:
        /// 1. flashing
        /// 2. shifting right to left
        /// 3. shifting left to right

    };

#endif // MAX7219_HPP