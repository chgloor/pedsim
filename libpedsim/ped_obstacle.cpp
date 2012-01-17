//
// pedsim - A microscopic pedestrian simulation system. 
// Copyright (c) 2003 - 2004 by Christian Gloor
//                              

#include "math.h"

#include "ped_obstacle.h"

#include <vector>

using namespace std;

/// Description: set intial values
/// \author  chgloor
/// \date    2012-01-07
Tobstacle::Tobstacle(double pax, double pay, double pbx, double pby) {
  static int staticid = 0;
  id = staticid++;
  ax = pax;
  ay = pay;
  bx = pbx;
  by = pby;
};


/// 
/// \author  chgloor
/// \date    2012-01-07
Tobstacle::Tobstacle() {
  static int staticid = 0;
  id = staticid++;
  ax = 0;
  ay = 0;
  bx = 1;
  by = 1;
};


/// Moves the obstacle to a new position.
/// \author  chgloor
/// \date    2012-01-07
void Tobstacle::setPosition(double pax, double pay, double pbx, double pby) {
	ax = pax, ay = pay;
	bx = pbx, by = pby;
};


/// Calculates and returns the forces of the obstacle to a given point x/y. 
/// x/y can be the location of an agent, but it can also be anything else, 
/// for example a grid coordinate of the user interface, if you want to display
/// the obstacle forces on the map.
/// \author  chgloor
/// \date    2012-01-17
/// \return  Tvector forces
/// \param   double x: The x coordinate of the point
/// \param   double y: The y coordinate of the point
Tvector Tobstacle::obstacleforce(double x, double y) {	
	double a1 = this->ax;
	double a2 = this->ay;
	double b1 = this->bx - this->ax;
	double b2 = this->by - this->ay;
	double lambda = (x*b1 + y*b2 - b1*a1 - b2*a2) / (b1*b1 + b2*b2);

	Tvector v; v.z = 0;
	if (lambda <= 0) { v.x = ax; v.y = ay; return v; };
	if (lambda >= 1) { v.x = bx; v.y = by; return v; };
	
	v.x = a1 + lambda*b1;
	v.y = a2 + lambda*b2;
	return v;
}
