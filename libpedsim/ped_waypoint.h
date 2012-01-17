//
// pedsim - A microscopic pedestrian simulation system. 
// Copyright (c) 2003 - 2004 by Christian Gloor
//                              

#ifndef _ped_waypoint_h_
#define _ped_waypoint_h_ 1

#include "ped_vector.h"

#include <iostream>


using namespace std;

/// The waypint classs
/// \author  chgloor
/// \date    2012-01-07
class Twaypoint {
 private:
  int id;                                           ///< waypoint number
  double x;                                         ///< position of the waypoint 
  double y;                                         ///< position of the waypoint 
  double r;                                         ///< position of the waypoint 
  int type;                                         

 public:
  Twaypoint();
  Twaypoint(double x, double y, double r);
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
  Tvector normalpoint(double p1, double p2, double oc11, double oc12, double oc21, double oc22);

};

/// A container for the waypoints. Defined here because some methods inside the Twaypoint class iterate over this container
#define WaypointContainer vector<Twaypoint*>

/// A container iterator for the waypoints. Defined here because some methods inside the Twaypoint class iterate over this container
#define WaypointIterator vector<Twaypoint*>::iterator


#endif
