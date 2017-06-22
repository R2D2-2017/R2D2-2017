/**
 * \file
 * \brief   testclass for inverse and forward kenimetics.
 *          inverse and forward methods are being used with 
 *          different values. test gets aproved if expected values are returned
 *
 * \author    Anas Shehata
 * \copyright Copyright (c) 2017, The R2D2 Team
 * \license   See LICENSE
 */

#include <iostream>
#include <ios>
#include "Kenimetics.hh"
#include <vector>

  /**
 * \brief using inverse kenimetics method to determine dof rotation. 
 *        The returned rotations are afterwards given to the forward kenimetics
 *        method.
 *        forward kenimetics should give end effectors xy coordinates.
 * 		  the result of end effectors coordinates received from 
 *        forward kenimetics will be printed out to screen
 *
 * \param[in]     desiredDestinationTestX  Desired end effectors X position
 * \param[in]     desiredDestinationTestY  Desired end effectors Y position
 * \param[in]     inverseTest  fetches robot dof rotations in radian
 * \param[in]     forwardTest  fetches eof positon
 *
 *
 */
void forwardInverseTest(const double desiredDestinationTestX,
	const double desiredDestinationTestY){
	std::pair <double,double> inverseTest (Kenimetics::inverse(
		desiredDestinationTestX, desiredDestinationTestY).first
	    , Kenimetics::inverse(desiredDestinationTestX,
	    desiredDestinationTestY).second );
	std::pair <double,double> forwardTest (
		Kenimetics::forward(inverseTest.first, inverseTest.second));

	std::cout << "result: " << forwardTest.first << ", " 
	    << forwardTest.second << std::endl;
}


  /**
 *
 * \brief Monkey testing forward and inverse kenimetics methods
 *        values out of bound will be expected to return NaN
 *
 */
int main ()
{	

	std::cout <<  " expected return value :Nan         --" ;
	forwardInverseTest(1,0); // expteded NaN
	std::cout <<  " expected return value :Nan         --" ;
	forwardInverseTest(0,1); // expected NaN
	std::cout <<  " expected return value :Nan         --" ;
	forwardInverseTest(1,1); // expected NaN
	std::cout <<  " expected return value :2,1         --" ;
	forwardInverseTest(2,1); // expected 2,1
	std::cout <<  " xpected 3return value :,1          --" ;
	forwardInverseTest(3,1); // expected 3,1
	std::cout <<  " expected return value :4,1         --" ;
	forwardInverseTest(4,1); // expected 4,1
	std::cout <<  " expected return value :5,1         --" ;
	forwardInverseTest(5,1); // expected 5,1
	std::cout <<  " expected return value :6,1         --" ;
	forwardInverseTest(6,1); // expected 6,1
	std::cout <<  " expected return value :7,1         --" ;
	forwardInverseTest(7,1); // expected 7,1
	std::cout <<  " expected return value :8,1         --" ;
	forwardInverseTest(8,1); // expected 8,1
	std::cout <<  " expected return value :9,1         --" ;
	forwardInverseTest(9,1); // expected 9,1
	std::cout <<  " expected return value :10,1        --" ;
	forwardInverseTest(10,1); // expected 10,1
	std::cout <<  " expected return value :11,1        --" ;
	forwardInverseTest(11,1); // expected 11,1
	std::cout <<  " expected return value :12,1        --" ;
	forwardInverseTest(12,1); // expected 12,1
	std::cout <<  " expected return value :13,1        --" ;
	forwardInverseTest(13,1); // expected 13,1
	std::cout <<  " expected return value :14,1        --" ;
	forwardInverseTest(14,1); // expected 14,1
	std::cout <<  " expected return value :15,1        --" ;
	forwardInverseTest(15,1); // expected 15,1
	std::cout <<  " expected return value :16,1        --" ;
	forwardInverseTest(16,1); // expected 16,1
	std::cout <<  " expected return value :17,1        --" ;
	forwardInverseTest(17,1); // expected 17,1
	std::cout <<  " expected return value :18,1        --" ;
	forwardInverseTest(18,1); // expected 18,1
	std::cout <<  " expected return value :19,1        --" ;
	forwardInverseTest(19,1); // expected 19,1
	std::cout <<  " expected return value :20,1        --" ;
	forwardInverseTest(20,1); // expected 20,1
	std::cout <<  " expected return value :21,1        --" ;
	forwardInverseTest(21,1); // expected 21,1
	std::cout <<  " expected return value :22,1        --" ;
	forwardInverseTest(22,1); // expected 22,1
	std::cout <<  " expected return value :23,1        --" ;
	forwardInverseTest(23,1); // expected 23,1
	std::cout <<  " expected return value :24,1        --" ;
	forwardInverseTest(24,1); // expected 24,1
	std::cout <<  " expected return value :25,1        --" ;
	forwardInverseTest(25,1); // expected 25,1
	std::cout <<  " expected return value :26,1        --" ;
	forwardInverseTest(26,1); // expected 26,1
	std::cout <<  " expected return value :27,1        --" ;
	forwardInverseTest(27,1); // expected 27,1
	std::cout <<  " expected return value :28,1        --" ;
	forwardInverseTest(28,1); // expected 28,1
	std::cout <<  " expected return value :29,1        --" ;
	forwardInverseTest(29,1); // expected 29,1
	std::cout <<  " expected return value :30,1        --" ;
	forwardInverseTest(30,1); // expected 30,1
	std::cout <<  " expected return value :31,1        --" ;
	forwardInverseTest(31,1); // expected 31,1
	std::cout <<  " expected return value :32,1        --" ;
	forwardInverseTest(32,1); // expected 32,1
	std::cout <<  " expected return value :33,1        --" ;
	forwardInverseTest(33,1); // expected 33,1
	std::cout <<  " expected return value :34,1        --" ;
	forwardInverseTest(34,1); // expected 34,1
	std::cout <<  " expected return value :35,1        --" ;
	forwardInverseTest(35,1); // expected 35,1
	std::cout <<  " expected return value :36,1        --" ;
	forwardInverseTest(36,1); // expected 36,1
	std::cout <<  " expected return value :37,1        --" ;
	forwardInverseTest(37,1); // expected 37,1
	std::cout <<  " expected return value :6,1         --" ;
	forwardInverseTest(38,1); // expected NaN

	
	std::cout <<  " expected return value :1,2         --" ;
	forwardInverseTest(1,2); // expected 1,2
	std::cout <<  " expected return value :1,3         --" ;
	forwardInverseTest(1,3); // expected 1,3
	std::cout <<  " expected return value :1,4         --" ;
	forwardInverseTest(1,4); // expected 1,4
	std::cout <<  " expected return value :1,5         --" ;
	forwardInverseTest(1,5); // expected 1,5
	std::cout <<  " expected return value :1,1         --" ;
	forwardInverseTest(1,1); // expected 1,11
	std::cout <<  " expected return value :1,7         --" ;
	forwardInverseTest(1,7); // expected 1,7
	std::cout <<  " expected return value :1,8         --" ;
	forwardInverseTest(1,8); // expected 1,8
	std::cout <<  " expected return value :1,9         --" ;
	forwardInverseTest(1,9); // expected 1,9
	std::cout <<  " expected return value :1,10        --" ;
	forwardInverseTest(1,10); // expected 1,10
	std::cout <<  " expected return value :1,11        --" ;
	forwardInverseTest(1,11); // expected 1,11
	std::cout <<  " expected return value :1,12        --" ;
	forwardInverseTest(1,12); // expected 1,12
	std::cout <<  " expected return value :1,13        --" ;
	forwardInverseTest(1,13); // expected 1,13
	std::cout <<  " expected return value :1,14        --" ;
	forwardInverseTest(1,14); // expected 1,14
	std::cout <<  " expected return value :1,15        --" ;
	forwardInverseTest(1,15); // expected 1,15
	std::cout <<  " expected return value :1,11        --" ;
	forwardInverseTest(1,11); // expected 1,11
	std::cout <<  " expected return value :1,17        --" ;
	forwardInverseTest(1,17); // expected 1,17
	std::cout <<  " expected return value :1,18        --" ;
	forwardInverseTest(1,18); // expected 1,18
	std::cout <<  " expected return value :1,19        --" ;
	forwardInverseTest(1,19); // expected 1,19
	std::cout <<  " expected return value :1,20        --" ;
	forwardInverseTest(1,20); // expected 1,20
	std::cout <<  " expected return value :1,21        --" ;
	forwardInverseTest(1,21); // expected 1,21
	std::cout <<  " expected return value :1,22        --" ;
	forwardInverseTest(1,22); // expected 1,22
	std::cout <<  " expected return value :1,23        --" ;
	forwardInverseTest(1,23); // expected 1,23
	std::cout <<  " expected return value :1,24        --" ;
	forwardInverseTest(1,24); // expected 1,24
	std::cout <<  " expected return value :1,25        --" ;
	forwardInverseTest(1,25); // expected 1,25
	std::cout <<  " expected return value :1,26        --" ;
	forwardInverseTest(1,21); // expected 1,21
	std::cout <<  " expected return value :1,27        --" ;
	forwardInverseTest(1,27); // expected 1,27
	std::cout <<  " expected return value :1,28        --" ;
	forwardInverseTest(1,28); // expected 1,28
	std::cout <<  " expected return value :1,29        --" ;
	forwardInverseTest(1,29); // expected 1,29
	std::cout <<  " expected return value :1,30        --" ;
	forwardInverseTest(1,30); // expected 1,30
	std::cout <<  " expected return value :1,31        --" ;
	forwardInverseTest(1,31); // expected 1,31
	std::cout <<  " expected return value :1,32        --" ;
	forwardInverseTest(1,32); // expected 1,32
	std::cout <<  " expected return value :1,33        --" ;
	forwardInverseTest(1,34); // expected 1,34
	std::cout <<  " expected return value :1,34        --" ;
	forwardInverseTest(1,35); // expected 1,35
	std::cout <<  " expected return value :1,35        --" ;
	forwardInverseTest(1,36); // expected 1,36
	std::cout <<  " expected return value :1,36        --" ;
	forwardInverseTest(1,37); // expected 1,37
	std::cout <<  " expected return value : NaN        --" ;
	forwardInverseTest(1,38); // expected 1,38

	

	

	

}
