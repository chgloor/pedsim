//
// pedsim - A microscopic pedestrian simulation system. 
// Copyright (c) 2003 - 2004 by Christian Gloor
//                              
// You can redistribute and/or modify this program under the terms of
// the GNU General Public License.  See copying.txt for details.
// 


#include "math.h"

#include "waypoint.h"
#include "vector.h"
#include "config.h"

#include <QPen>
#include <QGraphicsScene>

#include <vector>


using namespace std;

extern Config config;

/// Description: set intial values
/// \author  chgloor
/// \date    2012-01-07
Twaypoint::Twaypoint(double px, double py, double pr, QGraphicsScene *pscene) {
  static int staticid = 0;
  id = staticid++;
  x = px;
  y = py;
  r = pr;
  type = 0; // normal
  scene = pscene;
  ellipse = scene->addEllipse(x-r, y-r, r*2, r*2, QPen(QColor(44,0,0), 0.5, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin), QBrush(QColor(44, 0, 0)));
  norm = scene->addLine(x-r, y-r, x+r, y+r, QPen(Qt::darkRed, 0.5, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
  //  path = scene->addLine(x-r, y-r, x+r, y+r, QPen(Qt::darkBlue, 1, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));

	ellipse->setVisible(config.guiShowWaypoints);
	norm->setVisible(config.guiShowWaypoints);

};

/// 
/// \author  chgloor
/// \date    2012-01-07
Twaypoint::Twaypoint() {
  static int staticid = 0;
  id = staticid++;
  x = 0;
  y = 0;
  r = 1;
  ellipse = NULL;
};


/// 
/// \author  chgloor
/// \date    2012-01-10
/// \return  
/// \warning 
/// \param   
Tvector normalpoint(double p1, double p2, double oc11, double oc12, double oc21, double oc22) {
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
		
	ellipse->setVisible(config.guiShowWaypoints);
	norm->setVisible(config.guiShowWaypoints);

	if (type == 0) { // use normal to direction
		double distancex = x - fromx;
		double distancey = y - fromy;
		double dist2 = (distancex * distancex + distancey * distancey);  // dist2 = distanz im quadrat
		double dist = sqrt(dist2);

		// cout << "Dist " << distancex << "/" << distancey << " (" << dist << ")" << endl;
		
		double normalex = distancey / dist;
		double normaley = distancex / dist;
		
		// cout << "Norm " << normalex << "/" << normaley << " (" << dist << ")" << endl;
		// cout << "This " << this->getx() << "/" << this->gety() << " (" << this->getr() << ")" << endl;
		
		double oc11 = x + r * normalex;
		double oc12 = y - r * normaley;
		double oc21 = x - r * normalex;
		double oc22 = y + r * normaley;
		
		norm->setLine(oc11, oc12, oc21, oc22);
		
		// cout << "NDist " << oc11 << "/" << oc22 << endl;
		
		Tvector pnormal = normalpoint(myx, myy, oc11, oc12, oc21, oc22);
		
		//	path->setLine(fromx, fromy, pnormal.x, pnormal.y);
		
		double pndistancex = myx - pnormal.x;
		double pndistancey = myy - pnormal.y;
		double pndist2 = (pndistancex * pndistancex + pndistancey * pndistancey);  // dist2 = distanz im quadrat
		double pndist = sqrt(pndist2);
		
		if (pndist < 3) { *reached = true; } else { *reached = false; } 
		
		if (pndist == 0) { f.x = 0; f.y = 0; return f; }
		
		f.x = -pndistancex / pndist;
		f.y = -pndistancey / pndist;
		
		// cout << "PNDist " << f.x << "/" << f.y << " (" << pndist2 << ")" << endl;
		
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






/// 
/// \author  chgloor
/// \date    2012-01-10
/// \return  
/// \warning 
/// \param   
bool Twaypoint::hasReached(double myx, double myy) {
	 double distancex = myx - this->getx();
	 double distancey = myy - this->gety();
	 double dist2 = (distancex * distancex + distancey * distancey);  // dist2 = distanz im quadrat
	if (dist2 < (r*r)) { return true; } else { return false; }
}
