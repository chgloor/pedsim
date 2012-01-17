//
// pedsim - A microscopic pedestrian simulation system. 
// Copyright (c) 2003 - 2004 by Christian Gloor
//                              

#include "math.h"

#include "ped_waypoint.h"

#include <vector>

using namespace std;

/// Constructor: Sets some intial values
/// \author  chgloor
/// \date    2012-01-07
Twaypoint::Twaypoint(double px, double py, double pr) {
  static int staticid = 0;
  id = staticid++;
  x = px;
  y = py;
  r = pr;
  type = 0; // normal
};


/// Constructor
/// \author  chgloor
/// \date    2012-01-07
Twaypoint::Twaypoint() {
  static int staticid = 0;
  id = staticid++;
  x = 0;
  y = 0;
  r = 1;
};


/// Calculated the point that is on the given line and normal to the give position.
/// If it is not inside the line, the start or end point of the line is returned.
/// \author  chgloor
/// \date    2012-01-10
Tvector Twaypoint::normalpoint(double p1, double p2, double oc11, double oc12, double oc21, double oc22) {
	double a1 = oc11;
	double a2 = oc12;
	double b1 = oc21 - oc11;
	double b2 = oc22 - oc12;

	double lambda = (p1*b1 + p2*b2 - b1*a1 - b2*a2) / (b1*b1 + b2*b2);

	Tvector v; v.z = 0;
	if (lambda <= 0) { v.x = oc11; v.y = oc12; return v; };
	if (lambda >= 1) { v.x = oc21; v.y = oc22; return v; };
	
	v.x = a1 + lambda*b1;
	v.y = a2 + lambda*b2;
	return v;
} 


/// returns the force into the direction of the waypoint
/// \author  chgloor
/// \date    2012-01-10
Tvector Twaypoint::getForce(double myx, double myy, double fromx, double fromy, bool *reached) {
	Tvector f;
		
	if (type == 0) { // use normal to direction
		double distancex = x - fromx;
		double distancey = y - fromy;
		double dist2 = (distancex * distancex + distancey * distancey);  // dist2 = distanz im quadrat
		double dist = sqrt(dist2);

		double normalex = distancey / dist;
		double normaley = distancex / dist;
		
		double oc11 = x + r * normalex;
		double oc12 = y - r * normaley;
		double oc21 = x - r * normalex;
		double oc22 = y + r * normaley;
				
		Tvector pnormal = normalpoint(myx, myy, oc11, oc12, oc21, oc22);
		
		double pndistancex = myx - pnormal.x;
		double pndistancey = myy - pnormal.y;
		double pndist2 = (pndistancex * pndistancex + pndistancey * pndistancey);  // dist2 = distanz im quadrat
		double pndist = sqrt(pndist2);
		
		if (pndist < 3) { *reached = true; } else { *reached = false; } 		
		if (pndist == 0) { f.x = 0; f.y = 0; return f; }	  
		f.x = -pndistancex / pndist;
		f.y = -pndistancey / pndist;
	} else if (type == 1) { // point
		double distancex = x - myx;
		double distancey = y - myy;
		double dist2 = (distancex * distancex + distancey * distancey);  // dist2 = distanz im quadrat
		double dist = sqrt(dist2);
		f.x = distancex / dist;
		f.y = distancey / dist;
		if (dist < r) { *reached = true; } else { *reached = false; };
	}
	return f;
}
