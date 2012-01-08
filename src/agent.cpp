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

#include <QPen>


#include <vector>

extern AgentContainer agent;
extern ObstacleContainer obstacle;

const double h = 0.4;

using namespace std;


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
  
  vmax = 1.5 + 2.0*(double)rand()/(double)RAND_MAX; // in m/s between 1.5 and 3.5
};


// ----------------------------------------------------
// Name: setPosition
//!Description: sets the position
//!Introduced: chgloor Tuesday, February 10, 2004 10:48:39
//!Return value: void
// ----------------------------------------------------
void Tagent::setPosition(double px, double py, double pz) {
	x = px, y = py; z = pz; 
};

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
				double distancex = x - iter->x;
				double distancey = y - iter->y;
				double distancez = z - iter->z;
				double dist2 = (distancex * distancex + distancey * distancey + distancez * distancez);  // dist2 = distanz im quadrat
				double dist = sqrt(dist2);
				
				if ((dist2 > 0.000004) && (dist2 < 100)) { // 2cm- 10m distance
					fx = (distancex-0)/(exp(dist-1));   // this was originally "exp(dist-1)"
					fy = (distancey-0)/(exp(dist-1));
				}		
			}
			
			sax += 5.0f*fx; // kummulieren ueber alle agenten
			say += 5.0f*fy;
			saz += 5.0f*fz;
		}
	}

	// calculate desire to go to destination
	double eax = 0;
	double eay = 0;
	double eaz = 0;
	
	if ((hasreacheddestination == true) && (destinations.size() > 0)) {
		destination = destinations.dequeue();
		hasreacheddestination = false;
	}
	if (true) { 
		double distancex = x - destination.x;
		double distancey = y - destination.y;
		double distancez = z - destination.z;
		float dist2 = (distancex * distancex + distancey * distancey + distancez * distancez);  // dist2 = distanz im quadrat
	
		if (hasreacheddestination == false) {
			if (dist2 < 8*8) { // 8^2 m
				hasreacheddestination = true;
				destinations.enqueue(destination); // round queue
			}
		} // next: one step in dir of dest ... 

		//    if (dist2 > 0) {
		if (true) { // immer richtung 0/0/0
			eax = -vmax * distancex / sqrt(dist2);
			eay = -vmax * distancey / sqrt(dist2);
			eaz = -vmax * distancez / sqrt(dist2);
		}
	}

	// obstacles
	double oax = 0;
	double oay = 0;
	double oaz = 0;

	Tobstacle o;
	foreach (o, obstacle) {
		Tvector ov = obstacleforce(x, y, o.getax(), o.getay(), o.getbx(), o.getby());
		//		cout << "fp " << ov.x << "/" << ov.y << endl;

		double dox = x - ov.x;
		double doy = y - ov.y;

		float disto2 = (dox * dox + doy * doy);  // dist2 = distanz im quadrat
		
		if ((disto2 > 0.000004) && (disto2 < 400)) { // 2cm- 20m distance
			oax += 50.0f*(dox-0)/(exp(disto2-1));   // this was originally "exp(dist-1)"
			oay += 50.0f*(doy-0)/(exp(disto2-1));
		} else {
			oax += 0; oay += 0; 
		}

		
	}

	// sum up all the acelerations of the agent
	ax = h*sax + h*eax + h*oax;
	ay = h*say + h*eay + h*oay;
	az = h*saz + h*eaz + h*oaz;
	
	// calculate the new velocity based on v0 and the acceleration
	vx = 0.5*vx + ax;
	vy = 0.5*vy + ay;
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

