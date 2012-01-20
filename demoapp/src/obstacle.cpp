//
// pedsim - A microscopic pedestrian simulation system. 
// Copyright (c) 2003 - 2012 by Christian Gloor
//                              

#include "obstacle.h"

#include "math.h"

#include <iostream>

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
	Tobstacle::setPosition(pax, pay, pbx, pby); // ??????????????  --chgloor 2012-01-17
};

/// rot phi around x/y
/// \author  chgloor
/// \date    2012-01-20
/// \return  
/// \warning due to rouning errors, this will fail after a while. use the original points (saved) and cache the total phi or something  --chgloor 2012-01-20
/// \param   
void Obstacle::rotate(double x, double y, double phi) {
	double anx = getax()*cos(phi) - x*cos(phi) - getay()*sin(phi) + y*sin(phi) + x;
	double any = getax()*sin(phi) - x*sin(phi) + getay()*cos(phi) - y*cos(phi) + y;

	double bnx = getbx()*cos(phi) - x*cos(phi) - getby()*sin(phi) + y*sin(phi) + x;
	double bny = getbx()*sin(phi) - x*sin(phi) + getby()*cos(phi) - y*cos(phi) + y;

	setPosition(anx, any, bnx, bny);
}
