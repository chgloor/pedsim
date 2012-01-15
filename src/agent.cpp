//
// pedsim - A microscopic pedestrian simulation system. 
// Copyright (c) 2003 - 2004 by Christian Gloor
//                              


#include "math.h"

#include "agent.h"
#include "obstacle.h"
#include "vector.h"
#include "config.h"

#include <QPen>
#include <QGraphicsScene>

#include <vector>

using namespace std;

extern AgentContainer agent;
extern ObstacleContainer obstacle;
extern Config config;


// ----------------------------------------------------
// Name: constructor
//!Description: set intial values
//!Introduced: chgloor Monday, December 29, 2003 11:10:37
// ----------------------------------------------------
Tagent::Tagent(QGraphicsScene *pscene) {
  static int staticid = 0;
  id = staticid++;
  scene = pscene;
  x = 0;
  y = 0;
  z = 0;
  vx = 0;
  vy = 0;
  vz = 0;
  hasreacheddestination = true;
  destination.settype(1); // point
  destination.setr(1);
  follow = -1;
  rect = scene->addRect(QRectF(0,0,1,1), QPen(Qt::darkGreen, 0.1, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin), QBrush(QColor(Qt::darkGreen)));	
  lineea = scene->addLine(QLineF(0, 0, 1, 1), QPen(Qt::red, 0.1, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));	
  lineoa = scene->addLine(QLineF(0, 0, 1, 1), QPen(Qt::blue, 0.1, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));	
  linesa = scene->addLine(QLineF(0, 0, 1, 1), QPen(Qt::green, 0.1, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));	
  linelfa = scene->addLine(QLineF(0, 0, 1, 1), QPen(Qt::magenta, 0.1, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));	
  linev  = scene->addLine(QLineF(0, 0, 1, 1), QPen(Qt::yellow, 0.1, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));	
  vmax = 2.0 + 1.0*(double)rand()/(double)RAND_MAX; // in m/s between 2.0 and 4.0
};


/// 
/// \author  chgloor
/// \date    2012-01-08
void Tagent::setFollow(int id) {
	follow = id;
}
int Tagent::getFollow() {
	return follow;
}


/// 
/// \author  chgloor
/// \date    2012-01-08
void Tagent::setVmax(double pvmax) {
	vmax = pvmax;
}


// ----------------------------------------------------
// Name: setPosition
//!Description: sets the position
//!Introduced: chgloor Tuesday, February 10, 2004 10:48:39
//!Return value: void
// ----------------------------------------------------
void Tagent::setPosition(double px, double py, double pz) {
	x = px, y = py; z = pz; 
};


/// 
/// \author  chgloor
/// \date    2012-01-10
Tvector obstacleforce(double p1, double p2, double oc11, double oc12, double oc21, double oc22) {	
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


// ----------------------------------------------------
// Name: move
//!Description: does the agent dynamics stuff 
//!Introduced: chgloor Monday, December 29, 2003 11:10:58
//!Return value: void
// ----------------------------------------------------
void Tagent::move() {
		  	
	//
	//  ' S O C I A L '   A C C E L E R A T I O N 
	//
	double sax = 0; 
	double say = 0;
	double saz = 0;

	for (AgentIterator iter = agent.begin(); iter!=agent.end(); iter++) {  // iterate over all agents == O(N^2) :(
		double fx = 0;
		double fy = 0;
		double fz = 0;
		if ((iter->id != id)) {
			if ((abs(x-iter->x) < 10) && (abs(y-iter->y) < 10)) { // quick dist check
				double distancex = iter->x - x;
				double distancey = iter->y - y;
				double distancez = iter->z - z;
				double dist2 = (distancex * distancex + distancey * distancey + distancez * distancez);  
				double expdist = exp(sqrt(dist2)-1);
				if ((dist2 > 0.000004) && (dist2 < 400)) { // 2cm- 20m distance
					fx = -distancex/expdist;
					fy = -distancey/expdist;
				}						
				sax += config.simPedForce*fx; 
				say += config.simPedForce*fy;
				saz += config.simPedForce*fz;
			}
		}
	}


	//
	//  D E S I R E   A C C E L E R A T I O N
	//
	double eax = 0;
	double eay = 0;
	double eaz = 0;
		
	if ((hasreacheddestination == true) && (destinations.size() > 0)) {
		lastdestination.setx(destination.getx());
		lastdestination.sety(destination.gety());
		destination = destinations.dequeue();
		hasreacheddestination = false;
	}

	if (follow > 0) {
		destination.setx(agent.at(follow).getx());
		destination.sety(agent.at(follow).gety());
		destination.settype(1); // point
		destination.setr(0); // point
	}
	
	bool reached;
	Tvector ef = destination.getForce(x, y, lastdestination.getx(), lastdestination.gety(), &reached);
	eax = ef.x * vmax; // walk with full speed if nothing else affects me
	eay = ef.y * vmax;

	if (hasreacheddestination == false) {
		if (reached == true) {
			hasreacheddestination = true;
			destinations.enqueue(destination); // round queue
		}
	} 
	
	if (config.mlTendency == true) {
		eax = eax + 0.1*eay;
		eay = eay + -0.1*eax;
	}


	//
	//  L O O K I N G   F O R W A R D
	//
	double lfax = 0;
	double lfay = 0;
	double lfaz = 0;

	int lookforwardcount = 0;
		
	for (AgentIterator iter = agent.begin(); iter!=agent.end(); iter++) {  // iterate over all agents == O(N^2) :(
		if ((iter->id != id)) {
			double distancex = iter->x - x;
			double distancey = iter->y - y;
			double dist2 = (distancex * distancex + distancey * distancey); // 2D  
			if ((config.mlLookAhead) && (dist2 < 400)) { // look ahead feature
				double at2v  = atan2(-eax, -eay); // was vx, vy  --chgloor 2012-01-15 
				double at2d  = atan2(-distancex, -distancey);
				double at2v2 = atan2(-iter->vx, -iter->vy);
				double pi = 3.14159265;
				double s = at2d - at2v;   if (s > pi) s -= 2*pi;   if (s < -pi) s += 2*pi; 
				double vv = at2v - at2v2; if (vv > pi) vv -= 2*pi; if (vv < -pi) vv += 2*pi;
				if ((vv < -2.5) || (vv > 2.5)) { // entgegengesetzte richtung
					if ((s < 0) && (s > -0.3)) { // position vor mir, in meine richtung
						lookforwardcount--;
					} 
					if ((s > 0) && (s < 0.3)) {
						lookforwardcount++;
					}
				}
			}
		}
	}
	lfaz = 0; // 2d  --chgloor 2012-01-15
	if (lookforwardcount < 0) {
		lfax = 0.5f *  eay; // was vx, vy  --chgloor 2012-01-15  
		lfay = 0.5f * -eax;
	}
	if (lookforwardcount >  0) {
		lfax = 0.5f * -eay;
		lfay = 0.5f *  eax;
	}




	// 
	//  O B S T A C L E   A C C E L E R A T I O N
	//
	double oax = 0;
	double oay = 0;
	double oaz = 0;

	Tobstacle o;
	double mindisto2 = 99999; // obstacle with is closest only  --chgloor 2012-01-12
	double mindox = 0;
	double mindoy = 0;
	foreach (o, obstacle) {
		Tvector ov = obstacleforce(x, y, o.getax(), o.getay(), o.getbx(), o.getby());
		double dox = x - ov.x;
		double doy = y - ov.y;
		double disto2 = (dox * dox + doy * doy);  // dist2 = distanz im quadrat
		if ((disto2 < mindisto2) && (disto2 > 0.000004)) { // 2cm - inf distance
			mindisto2 = disto2;
			mindox = dox;
			mindoy = doy;
		}	
	}
	double oaxyf = exp(sqrt(mindisto2)-1);
	oax = config.simWallForce*mindox/oaxyf;
	oay = config.simWallForce*mindoy/oaxyf;


	//
	//  T O T A L   A C C E L E R A T I O N
	//

	// ax = config.simh*sax + config.simh*eax + config.simh*oax;
	// ay = config.simh*say + config.simh*eay + config.simh*oay;
	// az = config.simh*saz + config.simh*eaz + config.simh*oaz;
	ax = sax + eax + oax + lfax; // h also in calculation of the forces? arent they indep of the constant h?  --chgloor 2012-01-14
	ay = say + eay + oay + lfay;
	az = saz + eaz + oaz +    0;
	
	// calculate the new velocity based on v0 and the acceleration
	vx = 0.75*vx + ax; 
	vy = 0.75*vy + ay; // <<<<<<<<<<<-----------  is this 0.85 dependent of h?? think so   --chgloor 2012-01-15
	vz = 0; //0.75*vz + az;
	
	//	double speed = ( sqrt(vx*vx + vy*vy + vz*vz) / vmax );
	double speed = (sqrt(vx*vx + vy*vy + vz*vz));
	if (speed > vmax) {
		vx = (vx / speed) * vmax;
		vy = (vy / speed) * vmax;
		//vz = (vz / speed) * vmax;
	}

	// position update == actual move 
	x = x + config.simh * vx; // x = x0 + v*t
	y = y + config.simh * vy;
	z = 0; // z + h * vz; // 2D  --chgloor 2012-01-04


	//
	//  G R A P H I C   S C E N E   U P D A T E
	//

	//		rect->setPos(rect->mapFromScene(x, y));
	rect->setPos(x-0.5, y-0.5); // upper left edge
	if (config.showDirection == true) {
		linev->setLine(x, y, x+2*vx, y+2*vy);
		linev->setVisible(true);
	} else { linev->setVisible(false); }
	if (config.showForces == true) {
		lineea->setLine(x, y, x+2*eax, y+2*eay);
		lineea->setVisible(true);
		linesa->setLine(x, y, x+2*sax, y+2*say);
		linesa->setVisible(true);
		lineoa->setLine(x, y, x+2*oax, y+2*oay);
		lineoa->setVisible(true);
		linelfa->setLine(x, y, x+2*lfax, y+2*lfay);
		linelfa->setVisible(true);
	} else {
		lineea->setVisible(false);
		linesa->setVisible(false);
		lineoa->setVisible(false);
		linelfa->setVisible(false);
	}
}

