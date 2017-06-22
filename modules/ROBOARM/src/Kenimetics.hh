/**
 * \file
 * \brief   Forward and inverse kenimatics methods to virtualy calculate the 
 *          robots end effector position from degrees of freedom parameters. 
 *          And to determine the joint’s angles to get the desired
 *          position of the robot’s end effector
 *
 * \author    Anas Shehata
 * \copyright Copyright (c) 2017, The R2D2 Team
 * \license   See LICENSE
 */

#include <iostream>
#include <vector>

class Kenimetics{
public :
  
  /**
 * \brief Inverse kenimatic fuction. determines degrees 
 *        of freedom angles to get the desired
 *        end effectors position
 *
 * \param[in]     efctorDesiredXPosition  Desired end effectors X position. Value out of 
 *                bound will return NaN
 * \param[in]     efctorDesiredYPosition  Desired end effectors Y position. Value out of 
 *                bound will return NaN
 *
 * \return returns a pair, first index of pair is the lowest end effector 
 *         from base (end effector 1 take wikipage for refference). 
 *         Second index returns the highest end effector from base 
 *         (end effector 2 take wiki page for refference) angles are in radian
 *
 */
  static std::pair <double,double> inverse(
  	    const double efctorDesiredXPosition,const double efctorDesiredYPosition);

/**
 * \brief forward kenimatic fuction. calculates end effectors 
 *        position from degrees of freedom
 *        parameters end effectors position
 *
 * \param[in]     dof1Rotation  end effectors 1 angle in radian. Value out of 
 *                bound will return NaN
 * \param[in]     dof2Rotation  end effectors 2 angle in radian. Value out of 
 *                bound will return NaN
 *
 * \return returns a pair, first index of pair returns end effectors x position 
 *         Second index of pair returns end effectors y position  
 *
 */
  static std::pair <double,double>  forward(
  	    const double dof1Rotation, const double dof2Rotation);

};
