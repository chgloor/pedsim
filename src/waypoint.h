//
// pedsim - A microscopic pedestrian simulation system. 
// Copyright (c) 2003 - 2012 by Christian Gloor
//                              

#ifndef _waypoint_h_
#define _waypoint_h_ 1

#include <QGraphicsItem>
#include <QQueue>

#include <iostream>

#include "ped_waypoint.h"
#include "ped_vector.h"

using namespace std;

// ----------------------------------------------------
// Name: Twaypoint
//!Description: Class that descripts an waypoint object
//!Introduced: chgloor Jan 07, 2012
// ----------------------------------------------------
class Waypoint : public Twaypoint{
 private:
  QGraphicsScene *scene;
  QGraphicsEllipseItem *ellipse;
  QGraphicsLineItem *norm;
  QGraphicsLineItem *path;

 public:
  Waypoint();
  Waypoint(double x, double y, double r, QGraphicsScene *scene);
  Tvector getForce(double myx, double myy, double fromx, double fromy, bool *reached); ///< returns the force into the direction of the waypoint
};

#endif
