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

#include <QPen>


#include <vector>

extern AgentContainer agent;

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


// ----------------------------------------------------
// Name: move
//!Description: does the agent dynamics stuff 
//!Introduced: chgloor Monday, December 29, 2003 11:10:58
//!Return value: void
// ----------------------------------------------------
void Tagent::move(long systemtime) {
	double vmax = 3; // in m/s
		  	
	double sax = 0; // 'social' acceleration in x direction
	double say = 0;
	double saz = 0;

	for (AgentIterator iter = agent.begin(); iter!=agent.end(); iter++) {  // iterate over all agents == O(N^2) :(
		if ((iter->id != id)) {
			double fx = 0;
			double fy = 0;
			double fz = 0;
			double distancex = x - iter->x;
			double distancey = y - iter->y;
			double distancez = z - iter->z;
			float dist2 = (distancex * distancex + distancey * distancey + distancez * distancez);  // dist2 = distanz im quadrat
			
			if ((dist2 > 0.000004) && (dist2 < 100)) { // 2cm- 10m distance
				fx = (distancex-0)/(exp(dist2-1));   // this was originally "exp(dist-1)"
				fy = (distancey-0)/(exp(dist2-1));
			} else {
				fx = 0; fy = 0; fz = 0;
			}
			
			sax += 50.0f*fx; // kummulieren ueber alle agenten
			say += 50.0f*fy;
			saz += 50.0f*fz;
		}
	}

	// calculate desire to go to center of simulation 0/0/0
	double eax = 0;
	double eay = 0;
	double eaz = 0;
	
	if ((hasreacheddestination == true) && (destinations.size() > 0)) {
		destination = destinations.dequeue();
		hasreacheddestination = false;
	}
	if (true) { // heute: immer richtung 0/0/0
		double distancex = x - destination.x;
		double distancey = y - destination.y;
		double distancez = z - destination.z;
		float dist2 = (distancex * distancex + distancey * distancey + distancez * distancez);  // dist2 = distanz im quadrat
	
		if (hasreacheddestination == false) {
			if (dist2 < 2) {
				hasreacheddestination = true;
				destinations.enqueue(destination); // round queue
			}
		} // next: one step in dir of dest ... 

		//    if (dist2 > 0) {
		if (true) { // immer richtung 0/0/0
			eax = -0.5f * distancex / sqrt(dist2);
			eay = -0.5f * distancey / sqrt(dist2);
			eaz = -0.5f * distancez / sqrt(dist2);
		}
	}
	
	// sum up all the acelerations of the agent
	ax = h*sax + h*eax;
	ay = h*say + h*eay;
	az = h*saz + h*eaz;
	
	// calculate the new velocity based on v0 and the acceleration
	vx = 0.5*vx + ax;
	vy = 0.5*vy + ay;
	vz = 0.5*vz + az;
	
	//	double speed = ( sqrt(vx*vx + vy*vy + vz*vz) / vmax );
	double speed = (sqrt(vx*vx + vy*vy + vz*vz));
	if (speed > vmax) {
		vx = vx / speed;
		vy = vy / speed;
		vz = vz / speed;
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
