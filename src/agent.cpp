//
// pedsim - A microscopic pedestrian simulation system. 
// Copyright (c) 2003 - 2004 by Christian Gloor
//                              
// You can redistribute and/or modify this program under the terms of
// the GNU General Public License.  See copying.txt for details.
// 


#include "math.h"

#include "main.h"
#include "agent.h"
#include "obstacle.h"
#include "vector.h"
#include "config.h"

#include <QPen>


#include <vector>

using namespace std;

extern AgentContainer agent;
extern ObstacleContainer obstacle;
extern Config config;

const double h = 0.4;


// ----------------------------------------------------
// Name: constructor
//!Description: set intial values
//!Introduced: chgloor Monday, December 29, 2003 11:10:37
// ----------------------------------------------------
Tagent::Tagent() {
  static int staticid = 0;
  id = staticid++;
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
  
  vmax = 2.0 + 2.0*(double)rand()/(double)RAND_MAX; // in m/s between 2.0 and 4.0
};

/// 
/// \author  chgloor
/// \date    2012-01-08
/// \return  
/// \warning 
/// \param   
void Tagent::setFollow(int id) {
	follow = id;
}
int Tagent::getFollow() {
	return follow;
}

/// 
/// \author  chgloor
/// \date    2012-01-08
/// \return  
/// \warning 
/// \param   
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
/// \return  
/// \warning 
/// \param   
Tvector obstacleforce(double p1, double p2, double oc11, double oc12, double oc21, double oc22) {
	
	double a1 = oc11;
	double a2 = oc12;
	double b1 = oc21 - oc11;
	double b2 = oc22 - oc12;
	
	//	cout << a1 << "/" << a2 << " " << b1 << "/" << b2 << ", " << p1 << "/" << p2 << endl;

	double lambda = (p1*b1 + p2*b2 - b1*a1 - b2*a2) / (b1*b1 + b2*b2);

	//	cout << lambda << endl;

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
void Tagent::move(long systemtime) {
	//	double vmax = 3; // in m/s
		  	
	double sax = 0; // 'social' acceleration in x direction
	double say = 0;
	double saz = 0;

	for (AgentIterator iter = agent.begin(); iter!=agent.end(); iter++) {  // iterate over all agents == O(N^2) :(
		double fx = 0;
		double fy = 0;
		double fz = 0;
		if ((iter->id != id)) {
			if ((abs(x-iter->x) < 10) && (abs(y-iter->y) < 10)) { // quick dist check
				double distancex = x+h*vx - iter->x;
				double distancey = y+h*vy - iter->y;
				double distancez = z+h*vz - iter->z;
				double dist2 = (distancex * distancex + distancey * distancey + distancez * distancez);  // dist2 = distanz im quadrat
				double dist = sqrt(dist2);
				
				if ((dist2 > 0.000004) && (dist2 < 400)) { // 2cm- 20m distance
					fx = (distancex-0)/(exp(dist-1));   // this was originally "exp(dist-1)"
					fy = (distancey-0)/(exp(dist-1));
				}		
			}
			
			sax += config.simPedForce*fx; // kummulieren ueber alle agenten
			say += config.simPedForce*fy;
			saz += config.simPedForce*fz;
		}
	}

	// calculate desire to go to destination
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
		//		if (destination.hasReached(x, y) == true) {
		if (reached == true) {
			hasreacheddestination = true;
			destinations.enqueue(destination); // round queue
		}
	} // next: one step in dir of dest ... 

	eax = eax + 0.1*eay;
	eay = eay + 0.1*eax;

	
	// obstacles
	double oax = 0;
	double oay = 0;
	double oaz = 0;

	Tobstacle o;
	double mindisto = 99999; // obstacle with is closest only  --chgloor 2012-01-12
	double minoax = 0;
	double minoay = 0;

	foreach (o, obstacle) {
		Tvector ov = obstacleforce(x, y, o.getax(), o.getay(), o.getbx(), o.getby());

		double dox = x - ov.x;
		double doy = y - ov.y;

		double disto2 = (dox * dox + doy * doy);  // dist2 = distanz im quadrat
		double disto = sqrt(disto2);
		if ((disto < mindisto) && (disto2 > 0.000004) && (disto2 < 1600)) { // 2cm- 40m distance
			minoax += config.simWallForce*(dox-0)/(exp(disto-1)); 
			minoay += config.simWallForce*(doy-0)/(exp(disto-1));
			mindisto = disto;
		} else {
			oax += 0; oay += 0; 
		}		
	}
	oax = minoax;
	oay = minoay;


	// sum up all the acelerations of the agent
	ax = h*sax + h*eax + h*oax;
	ay = h*say + h*eay + h*oay;
	az = h*saz + h*eaz + h*oaz;
	
	// calculate the new velocity based on v0 and the acceleration
	vx = 0.75*vx + ax;
	vy = 0.75*vy + ay;
	vz = 0; //0.5*vz + az;
	
	//	double speed = ( sqrt(vx*vx + vy*vy + vz*vz) / vmax );
	double speed = (sqrt(vx*vx + vy*vy + vz*vz));
	if (speed > vmax) {
		vx = (vx / speed) * vmax;
		vy = (vy / speed) * vmax;
		vz = (vz / speed) * vmax;
	}
	

	// position update == actual move 
	x = x + h * vx; // x = x0 + v*t
	y = y + h * vy;
	z = 0; // z + h * vz; // 2D  --chgloor 2012-01-04

	//		rect->setPos(rect->mapFromScene(x, y));
	rect->setPos(x, y);
	// 		cerr << "agent " << id << " eax " << eax << " x " << x << endl;
	// 		cerr << "agent " << id << " eay " << eay << " y " << y << endl;
	// 		cerr << "agent " << id << " eaz " << eaz << " z " << z << endl;

}

