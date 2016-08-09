//
// pedsim - A microscopic pedestrian simulation system. 
// Copyright (c) 2003 - 2012 by Christian Gloor
//                              

#ifndef _obstacle_h_
#define _obstacle_h_ 1

#include <QGraphicsItem>

#include "ped_obstacle.h"

using namespace std;

/// \author  chgloor
/// \date    2012-01-17
class Obstacle: public Ped::Tobstacle {
 private:

 public:
  Obstacle(double ax, double ay, double bx, double by, QGraphicsLineItem *l);
  QGraphicsLineItem *line;

  void setPosition(double ax, double ay, double bx, double by);
};

#endif
