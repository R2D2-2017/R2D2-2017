/**
 * \file
 * \author    Anas Shehata
 * \copyright Copyright (c) 2017, The R2D2 Team
 * \license   See LICENSE
 */

#include "Kenimetics.hh" 
#include <iostream>
#include <cstddef>      
#include <math.h>     

 /**
 * \brief Inverse kenimatic fuction. determines degrees of freedom
 *        angles to get the desired
 *        end effectors position
 *
 * \param[in]     efctorDesiredXPosition  Desired end effectors X position
 * \param[in]     efctorDesiredYPosition  Desired end effectors Y position
 * \param[in]     length1   robots branch1 l1 check wiki picture for refference
 * \param[in]     length2   robots branch2 l2 check wiki picture for refference
 * \param[in]     eofDistance   robot end effectors distance
 * \param[in]     eofDistToGround   end effectors distance to ground
 * \param[out]    dof1Rotation    required degrees of freedom 1 rotation in 
 *                 radian to get desired eof position
 * \param[out]     dof2Rotation    required degrees of freedom 2 rotation in 
 *                 radian to get desired eof position
 *
 * \return returns a pair, first index of pair is the lowest end effector 
 *         from base (end effector 1 take wikipage for refference). 
 *         Second index returns the highest end effector from base 
 *         (end effector 2 take wiki page for refference) angles are in radian
 *
 */
std::pair <double,double>  Kenimetics::inverse(
	const double efctorDesiredXPosition,
	const double efctorDesiredYPosition){
 	double length1 = 18;
 	double length2 = 20;
 	double eofDistance = sqrt(pow(efctorDesiredXPosition,2) 
 	    + pow(efctorDesiredYPosition,2)); // hand to base desired coordinates
 	double eofDistToGround  = atan(efctorDesiredYPosition 
 	    / efctorDesiredXPosition);  // relative to ground slope coordinates

 	double dof1Rotation = acos((pow(length1,2) + pow(eofDistance,2) 
 	    - pow(length2,2)) / (2 * length1 * eofDistance)) 
 	    + eofDistToGround ;
 	    //  result of bottom degrees of freedom rotation in degrees
  	double dof2Rotation = dof1Rotation - M_PI + acos((pow(length1,2) 
  	+ pow(length2,2) - pow(eofDistance,2)) 
  	/ ( 2 * length1 * length2 )); 
  	//result of top degrees of freedom rotation in degrees
  	
  	//static double dof1Dof2Rotation [2] = {dof1Rotation,dof2Rotation};
  	std::pair <double,double> dof1Dof2Rotation (dof1Rotation,dof2Rotation);
 
	return dof1Dof2Rotation;
	
}

/**
 * \brief forward kenimatic fuction. calculates end effectors 
 *        position from degrees of freedom
 *        parameters end effectors position
 *
 * \param[in]     dof1Rotation  end effectors 1 angle in radian. Value out of 
 *                bound will result in returning NaN
 * \param[in]     dof2Rotation  end effectors 2 angle in radian. Value out of 
 *                bound will result in returning NaN
 * \param[in]     length1   robots branch1 l1 check wiki picture for refference
 * \param[in]     length2   robots branch2 l2 check wiki picture for refference
 * \param[in,out]     dofFk2   degrees of freedom 2 position
 *
 * \return returns a pair, first index of pair returns end effectors x position 
 *         Second index of pair returns end effectors y position  
 *
 */
std::pair <double,double>  Kenimetics::forward(const double dof1Rotation
	, const double dof2Rotation ){
	double length1 = 18;
 	double length2 = 20;

 	double dofFk2 [2]= {length1 * cos(dof1Rotation), 
 	    length1 * sin(dof1Rotation)}; // degrees of freedom joint 2 position
    
 	std::pair <double,double> fKenEffectorCoord (dofFk2[0] + length2 
 	    * cos(dof2Rotation),dofFk2[1] + length2 
 	    * sin(dof2Rotation)); // end effector coordinates
 

    return fKenEffectorCoord;
}
