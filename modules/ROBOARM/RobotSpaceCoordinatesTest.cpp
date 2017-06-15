
// @AUTOR Anas Shehata
//
//***** testing what is mentioned in line 5 and 6 *****//
//determine the joint’s parameters for desired position end effector 
//determine end effectors position from joint params 
//*****--------------------------------------*****//
#include <iostream>
#include <cstddef>      
#include <math.h>     
#include <valarray>  

// Use the  Moving robot arm in 3d space coordinates research 
// report as a refference. specceficly the picture on page 5



int main()
{ 

 

  // Inverse kinematics
  double L1 = 18.0; // L1 robots branch from bottom degrees of freedom to second degrees of freedom equals 18cm measured
  double l2 = 21.0; // L2 robots branch from top degrees of freedom to end effector equals 21 cm measured
  double efctorDesiredPosition [2] = {10.0,20.0}; // desired end effector coordinates
  	
  double D = std::sqrt(efctorDesiredPosition[0]**2 + efctorDesiredPosition[1]**2) // hand to base desired coordinates
  double H = atan(efctorDesiredPosition[1] / efctorDesiredPosition[0])  // relative to ground slope coordinates
  double dof1 = acos((L1**2 + D**2 - l2**2) / (2 * L1 * D)) + H //  result of bottom degrees of freedom rotation in degrees
  double dof2 = dof1 - pi + acos((L1**2 + l2**2 - D**2) / ( 2 * L1 * l2 )) //result of top degrees of freedom rotation in degrees

  //forward kinematics
  dofFk2 = (A1 * cos(dof1), A1 * sin(dof1)) // degrees of freedom joint 2 coordinates
  fKenEffectorCoord= (J2[0] + A2 * cos(dof2), J2[1] + A2 * sin(dof2)) // end effector coordinates

  std::cout << "dof1 coordinates" << dof1 >> "\n";
  std::cout << "dof1 coordinates" << dof2 >> "\n";
  std::cout << "dofFk2 coordinates" << dofFk2 >> "\n";
  std::cout << "fKenEffectorCoord coordinates" << fKenEffectorCoord >> "\n";

}