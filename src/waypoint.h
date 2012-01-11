//
// pedsim - A microscopic pedestrian simulation system. 
// Copyright (c) 2003 - 2004 by Christian Gloor
//                              
// You can redistribute and/or modify this program under the terms of
// the GNU General Public License.  See copying.txt for details.
// 

#ifndef _waypoint_h_
#define _waypoint_h_ 1

//#include <QApplication>
#include <QGraphicsItem>
#include <QQueue>

#include <iostream>
//#include <vector>

#include "vector.h"


using namespace std;

// ----------------------------------------------------
// Name: Twaypoint
//!Description: Class that descripts an waypoint object
//!Introduced: chgloor Jan 07, 2012
// ----------------------------------------------------
class Twaypoint {
 private:
  int id;                                           ///< waypoint number
  double x;                                         ///< position of the waypoint 
  double y;                                         ///< position of the waypoint 
  double r;                                         ///< position of the waypoint 
  int type;                                         
  QGraphicsScene *scene;
  QGraphicsEllipseItem *ellipse;
  QGraphicsLineItem *norm;
  QGraphicsLineItem *path;

 public:
  Twaypoint();
  Twaypoint(double x, double y, double r, QGraphicsScene *scene);
  void setType(int t) {type = t; };                 ///< sets the waypoint type
  int getid() { return id; };                       ///< returns the waypoints id
  int gettype() { return type; };                   ///< returns the waypoints type
  double getx() { return x; };                      ///< returns the waypoints x position
  double gety() { return y; };                      ///< returns the waypoints y position
  double getr() { return r; };                      ///< returns the waypoints x position
  void setx(double px) { x = px; };                      ///< sets the waypoints x position
  void sety(double py) { y = py; };                      ///< sets the waypoints y position
  void setr(double pr) { r = pr; };                      ///< sets the waypoints x position
  void settype(int t) { type = t; };                       
  Tvector getForce(double myx, double myy, double fromx, double fromy, bool *reached); ///< returns the force into the direction of the waypoint
  bool hasReached(double myx, double myy); ///< returns true if the agent has reached the waypoint
};

/// A container for the waypoints. Defined here because some methods inside the Twaypoint class iterate over this container
#define WaypointContainer vector<Twaypoint>

/// A container iterator for the waypoints. Defined here because some methods inside the Twaypoint class iterate over this container
#define WaypointIterator vector<Twaypoint>::iterator


#endif
