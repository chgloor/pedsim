//
// pedsim - A microscopic pedestrian simulation system. 
// Copyright (c) 2003 - 2012 by Christian Gloor
//                              

#ifndef _ped_obstacle_h_
#define _ped_obstacle_h_ 1

#include "ped_vector.h"

using namespace std;

/// Class that defines a Tobstacle object
/// \author  chgloor
/// \date    2012-01-17
class Tobstacle {
 private:
  int id;                                            ///< Obstacle number
  double ax;                                         ///< Position of the obstacle 
  double ay;                                         ///< Position of the obstacle 
  double bx;                                         ///< Position of the obstacle 
  double by;                                         ///< Position of the obstacle 
  int type;                                         
  
 public:
  Tobstacle();
  Tobstacle(double ax, double ay, double bx, double by);
  void setPosition(double ax, double ay, double bx, double by); ///< Set the obstacles position
  
  Tvector obstacleforce(double p1, double p2);


  void setType(int t) {type = t; };                   ///< Sets the obstacle type
  int getid() { return id; };                         ///< Returns the obstacles id
  int gettype() { return type; };                     ///< Returns the obstacles type
  double getax() { return ax; };                      ///< Returns the obstacles x position
  double getay() { return ay; };                      ///< Returns the obstacles y position
  double getbx() { return bx; };                      ///< Returns the obstacles x position
  double getby() { return by; };                      ///< Returns the obstacles y position
};



#endif
