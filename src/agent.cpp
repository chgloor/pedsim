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
  energy = 100;
  enemynearest = (AgentIterator)NULL;
  enemydist = 999999;
  deadsince = -1;
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
// Name: hit
//!Description: if an agent was hit by another agent 
//!Introduced: chgloor Monday, December 29, 2003 14:06:36
// ----------------------------------------------------
void Tagent::hit(long systemtime) {
	energy = energy - h*0.3 ;
	if ((energy < 0) && (deadsince <= 0)) {
		deadsince = systemtime;
		cerr << "agent " << id << " dies @ " << systemtime << endl;
	}
};


/// returns the agents nearest enemy position
/// \author  chgloor
/// \date    2010-02-11
double Tagent::getnex() {
	if (enemynearest != (AgentIterator)NULL) {
		return enemynearest->getx();
	}
	return 0;
}
double Tagent::getney() {
	if (enemynearest != (AgentIterator)NULL) {
		return enemynearest->gety();
	}
	return 0;
}
double Tagent::getnez() {
	if (enemynearest != (AgentIterator)NULL) {
		return enemynearest->getz();
	}
	return 0;
}


// ----------------------------------------------------
// Name: move
//!Description: does the agent dynamics stuff 
//!Introduced: chgloor Monday, December 29, 2003 11:10:58
//!Return value: void
// ----------------------------------------------------
void Tagent::move(long systemtime) {
	fire = false; // default, set later to true if fireing
	double vmax = 3; // in m/s
	
	// if nearest enemy is dead, unassign it and set distance to inf
	if ((enemynearest != (AgentIterator)NULL) && (enemynearest->isalive() == false)) {
// 		cerr << "agent " << id << " has killed its nearest enemy: agent " << enemynearest->getid() << endl;
		enemydist = 9999999;
		enemynearest = (AgentIterator)NULL;
	};
		
	  	
	double sax = 0; // 'social' acceleration in x direction
	double say = 0;
	double saz = 0;
	int tenemydist = 9999999;
	AgentIterator tenemynearest = (AgentIterator)NULL;
	for (AgentIterator iter = agent.begin(); iter!=agent.end(); iter++) {  // iterate over all agents == O(N^2) :(
		if ((iter->id != id)) {
			if (iter->isalive() == true) {
				double fx = 0;
				double fy = 0;
				double fz = 0;
				double distancex = x - iter->x;
				double distancey = y - iter->y;
				double distancez = z - iter->z;
				float dist2 = (distancex * distancex + distancey * distancey + distancez * distancez);  // dist2 = distanz im quadrat
				
				// search the nearest enemy, if none assigned
				if (enemynearest == (AgentIterator)NULL) {
					if (dist2 < tenemydist) {
						if (type != iter->gettype()) {
							tenemynearest = iter;
							tenemydist = dist2;
						}
					}
				}

				if ((dist2 > 0.000004) && (dist2 < 100)) { // 2cm- 10m distance
					fx = (distancex-0)/(exp(dist2-1));   // this was originally "exp(dist-1)"
					fy = (distancey-0)/(exp(dist2-1));
				} else {
					fx = 0; fy = 0; fz = 0;
				}
				
				sax += fx; // kummulieren ueber alle agenten
				say += fy;
				saz += fz;
			}
		}
	}

	// assign the nearest enemy, if none assigned yet
	if (enemynearest == (AgentIterator)NULL) {
		enemydist = tenemydist;
		enemynearest = tenemynearest;
// 		if (enemynearest != (AgentIterator)NULL) {
// 			cerr << "agent " << id << " has new nearest enemy: agent " << enemynearest->getid() << endl;
// 		} else {
// 			cerr << "agent " << id << " has no nearest enemy." << endl;
// 		}
	}

	// calculate desire to go to center of simulation 0/0/0
	double eax = 0;
	double eay = 0;
	double eaz = 0;
	
	if (true) { // heute: immer richtung 0/0/0
		double distancex = x - 0;
		double distancey = y - 0;
		double distancez = z - 0;
		float dist2 = (distancex * distancex + distancey * distancey + distancez * distancez);  // dist2 = distanz im quadrat
		
		//    if (dist2 > 0) {
		if (true) { // immer richtung 0/0/0
			eax = -0.03f * distancex / sqrt(dist2);
			eay = -0.03f * distancey / sqrt(dist2);
			eaz = -0.03f * distancez / sqrt(dist2);
		}
	}
	
	// calculate desire to follow nearest enemy
	double nax = 0;
	double nay = 0;
	double naz = 0;

	if (enemynearest != (AgentIterator)NULL) { 
		double distancex = x - enemynearest->getx();
		double distancey = y - enemynearest->gety();
		double distancez = z - enemynearest->getz();
		float dist2 = (distancex * distancex + distancey * distancey + distancez * distancez);  // dist2 = distanz im quadrat
	  
		if (true) { 
			nax = -0.2f * distancex / sqrt(dist2);
			nay = -0.2f * distancey / sqrt(dist2);
			naz = -0.2f * distancez / sqrt(dist2);
		}

		// fire at enemy
		if (dist2 < 350) {
			enemynearest->hit(systemtime);
			fire = true;
		}

		// too far away
		if (dist2 > 1000) {
// 		cerr << "agent " << id << " has lost its nearest enemy: agent " << enemynearest->getid() << endl;
			enemynearest = (AgentIterator)NULL;
		}
	}
	

	if (deadsince < 0) {

		// sum up all the acelerations of the agent
		ax = h*sax + h*eax + h*nax;
		ay = h*say + h*eay + h*nay;
		az = h*saz + h*eaz + h*naz;

		// calculate the new velocity based on v0 and the acceleration
		vx = vx + ax;
		vy = vy + ay;
		vz = vz + az;
	
		double speed = ( sqrt(vx*vx + vy*vy + vz*vz) / vmax );
		if (speed > 1) {
			vx = vx / speed;
			vy = vy / speed;
			vz = vz / speed;
		}
		
	} else {
		rect->setPen(QPen(Qt::gray, 1, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
	}

	// position update == actual move 
	x = x + h * vx; // x = x0 + v*t
	y = y + h * vy;
	z = z + h * vz;
	//		rect->setPos(rect->mapFromScene(x, y));
	rect->setPos(x, y);
	// 		cerr << "agent " << id << " eax " << eax << " x " << x << endl;
	// 		cerr << "agent " << id << " eay " << eay << " y " << y << endl;
	// 		cerr << "agent " << id << " eaz " << eaz << " z " << z << endl;

}
