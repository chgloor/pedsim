//
// pedsim - A microscopic pedestrian simulation system. 
// Copyright (c) 2003 - 2004 by Christian Gloor
//                              
// You can redistribute and/or modify this program under the terms of
// the GNU General Public License.  See copying.txt for details.
// 

#ifndef _obstacle_h_
#define _obstacle_h_ 1

//#include <QApplication>
#include <QGraphicsItem>
#include <QQueue>

#include <iostream>
//#include <vector>

#include "vector.h"


using namespace std;

// ----------------------------------------------------
// Name: Tobstacle
//!Description: Class that descripts an obstacle object
//!Introduced: chgloor Jan 07, 2012
// ----------------------------------------------------
class Tobstacle {
 private:
  int id;                                           ///< obstacle number
  double ax;                                         ///< position of the obstacle 
  double ay;                                         ///< position of the obstacle 
  double bx;                                         ///< position of the obstacle 
  double by;                                         ///< position of the obstacle 
  int type;                                         
  
 public:
  Tobstacle();
  Tobstacle(double ax, double ay, double bx, double by, QGraphicsLineItem *l);
  void setPosition(double ax, double ay, double bx, double by); ///< set the obstacles position
  void setType(int t) {type = t; };                 ///< sets the obstacle type
  int getid() { return id; };                       ///< returns the obstacles id
  int gettype() { return type; };                   ///< returns the obstacles type
  double getax() { return ax; };                      ///< returns the obstacles x position
  double getay() { return ay; };                      ///< returns the obstacles y position
  double getbx() { return bx; };                      ///< returns the obstacles x position
  double getby() { return by; };                      ///< returns the obstacles y position
  //  void print() {cout << "obstacle " << id << ": " << x << "/" << y << "/" << z << endl; }; ///< prints the obstacles state (simple) to stdout
  QGraphicsLineItem *line;

};

/// A container for the obstacles. Defined here because some methods inside the Tobstacle class iterate over this container
#define ObstacleContainer vector<Tobstacle>

/// A container iterator for the obstacles. Defined here because some methods inside the Tobstacle class iterate over this container
#define ObstacleIterator vector<Tobstacle>::iterator


#endif
