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

/// Class that descripts an waypoint object
/// \author  chgloor
/// \date    2012-01-07
class Waypoint : public Ped::Twaypoint{
 private:
  QGraphicsScene *scene;
  QGraphicsEllipseItem *ellipse;
  QGraphicsLineItem *norm;
  QGraphicsLineItem *path;

 public:
  Waypoint();
  Waypoint(double x, double y, double r, QGraphicsScene *scene);
  Ped::Tvector getForce(double myx, double myy, double fromx, double fromy, bool *reached); ///< returns the force into the direction of the waypoint
};

#endif
