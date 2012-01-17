//
// pedsim - A microscopic pedestrian simulation system. 
// Copyright (c) 2003 - 2012 by Christian Gloor
//                              

#include "obstacle.h"

using namespace std;


/// Description: set intial values
/// \author  chgloor
/// \date    2012-01-07
Obstacle::Obstacle(double pax, double pay, double pbx, double pby, QGraphicsLineItem *pl) : Tobstacle(pax, pay, pbx, pby) {
  line = pl;
  line->setLine(pax, pay, pbx, pby);
};


/// moves the obstacle ot a new position
/// \author  chgloor
/// \date    2012-01-07
void Obstacle::setPosition(double pax, double pay, double pbx, double pby) {
	line->setLine(pax, pay, pbx, pby);
	Tobstacle(pax, pay, pbx, pby); // ??????????????  --chgloor 2012-01-17
};
