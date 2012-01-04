//
// pedsim - A microscopic pedestrian simulation system. 
// Copyright (c) 2003 - 2004 by Christian Gloor
//                              
// You can redistribute and/or modify this program under the terms of
// the GNU General Public License.  See copying.txt for details.
// 

#include <stdio.h>
#include <iostream> // cout ...
#include <fstream> // files
#include <string>   // strncpy

#include "pov.h"
#include "agent.h"
#include "functions.h"
#include "vector.h"

using namespace std;

extern AgentContainer a;


// --------------------------------------------------
// Name: Tpov
// Purpose: Constructor. Initializes open files etc
// Introduced: chgloor Monday, December 29, 2003 12:26:47
// --------------------------------------------------
Tpov::Tpov(char *pfilename, long systemtime) {
  strncpy(filename, pfilename, sizeof(filename));
  this->systemtime = systemtime;
  newfile();
}


// ----------------------------------------------------
// Name: newfile
// Description: opens a new file and adds pov intro
// Introduced: chgloor Monday, January  5, 2004  1:43:21
// ----------------------------------------------------
void Tpov::newfile() {
	file.open (filename, ios::out);
	
	file << "// Frame " << systemtime << endl << endl;
	file << "#include \"colors.inc\"" << endl;
	file << "#include \"scene.inc\"" << endl;
	file << "#include \"camera.inc\"" << endl;
	file << "#include \"objects.inc\"" << endl;
	file << "#include \"ship.inc\"" << endl;
	file << endl;
}


/// drawAgent draws an agent
/// \author  chgloor
/// \date    2010-02-11
//void Tpov::drawAgent(int id, int type, double x, double y, double z, double vx, double vy, double vz, bool isfireing, double nex, double ney, double nez) {
void Tpov::drawAgent(AgentIterator a) {
	//	http://forums.xna.com/forums/t/10203.aspx

	// O is your object's position
	Tvector *o = new Tvector();
	o->x = a->getx();
	o->y = a->gety();
	o->z = a->getz();

	// U is the nominal "up" vector
	Tvector *u = new Tvector();
	Tvector *aa = new Tvector();
	Tvector *av = new Tvector();
// 	u->x = 0;
// 	u->y = 0;
// 	u->z = 1;
	aa->x = a->getax();
	aa->y = a->getay();
	aa->z = a->getaz();
	aa->normalize();

	av->x = a->getvx();
	av->y = a->getvy();
	av->z = a->getvz();
	av->normalize();

	u->x = aa->x - av->x;
	u->y = aa->y - av->y;
	u->z = aa->z - av->z;
	u->normalize();

	delete aa;
	delete av;

	// D is the direction
	Tvector *d = new Tvector();
	d->x = a->getvx();
	d->y = a->getvy();
	d->z = a->getvz();

	//   Vector3 Right = Vector3.Cross(U, D);
	Tvector *right = new Tvector();
	right->cross(u, d);

	//   Vector3.Normalize(ref Right, out Right);
	right->normalize();

	//   Vector3 Backwards = Vector3.Cross(Right, U);
	Tvector *backwards = new Tvector();
	backwards->cross(right, u);

	//   Vector3.Normalize(ref Backwards, out Backwards);
	backwards->normalize();

	//   Vector3 Up = Vector3.Cross(Backwards, Right);
	Tvector *up = new Tvector();
	up->cross(backwards, right);

	//   Matrix rot = new Matrix(Right.X, Right.Y, Right.Z, 0, Up.X, Up.Y, Up.Z, 0, Backwards.X, Backwards.Y, Backwards.Z, 0, 0, 0, 0, 1);


	// 1st p cam

	// camera {
	//	  location <0, -200, 0>
	//   look_at <0, 0, 0>
	//	  right RATIO*x
	// }

	if (a->getid() == 298) { // cam-ship
		file << "#if (CAM = 1)" << endl;
		file << "  camera { " << endl;
		file << "    location <" << a->getx()+2*av->x << ", " << a->gety()+2*av->y << ", " << a->getz()+2*av->z << "> " << endl;
		file << "    look_at <" << a->getx()+10*av->x << ", " << a->gety()+10*av->y << ", " << a->getz()+10*av->z << "> " << endl;
		file << "    sky <" << up->x << ", " << up->y << ", " << up->z << "> " << endl;
		//		file << "  right RATIO* <" << up->x << ", " << up->y << ", " << up->z << "> " << endl;
		//		file << "  up <" << right->x << ", " << right->y << ", " << right->z << "> " << endl;
		file << "    right RATIO*x " << endl;
		file << "    up y " << endl;
		file << "  }" << endl;
		file << "#end" << endl;
	} 
	
	// ships
	
	if ((a->isalive() == true) || ((systemtime - a->getdeadsince()) < 10)) {
		if (a->isalive() == false) {
			file << "object { explosion" << (systemtime - a->getdeadsince()) << endl;
			//		cerr << "explosion " << a->getid() << " " << systemtime << " " << a->getdeadsince() << endl;
		} 
		if ((a->isalive() == true)) {
			if (a->gettype() == 0) {
				file << "object { ship1  " << endl;
			} else {
				file << "object { ship2  " << endl;
			}
		}
		
		file << "  matrix < " << right->x << ", " << right->y << ", " << right->z << ", " << up->x << ", " << up->y << ", " << up->z << ", " << backwards->x << ", " << backwards->y << ", " << backwards->z << ", " << a->getx() << ", " << a->gety() << ", " << a->getz() << " >" << endl;
		
		file << " }" << endl;
	}
	
	// lasers  

	if (a->isalive() == true) {
		if ((rand()/(RAND_MAX + 1.0)) < 0.25) { 
			double rx = (rand()/(RAND_MAX + 2.0))-1.0;
			double ry = (rand()/(RAND_MAX + 2.0))-1.0;
			double rz = (rand()/(RAND_MAX + 2.0))-1.0;
			if (a->gettype() == 0) {
				if (a->isfireing() == true) {
					file << "cylinder { <" << a->getx() << ", " << a->gety() << ", " << a->getz() << ">, <" << a->getnex()+rx << ", " << a->getney()+ry << ", " << a->getnez()+rz << ">, 0.1 hollow material {laser_red}}" << endl;
					file << "object { explosionL  translate <" << a->getnex()+rx << ", " << a->getney()+ry << ", " << a->getnez()+rz << ">}" << endl;
				}
			} else {
				if (a->isfireing() == true) {
					file << "cylinder { <" << a->getx() << ", " << a->gety() << ", " << a->getz() << ">, <" << a->getnex()+rx << ", " << a->getney()+ry << ", " << a->getnez()+rz << ">, 0.1 hollow material {laser_green}}" << endl;
					file << "object { explosionL  translate <" << a->getnex()+rx << ", " << a->getney()+ry << ", " << a->getnez()+rz << ">}" << endl;
				}
			}
		}
	}

	delete o;
	delete u;
	delete d;
	delete right;
	delete backwards;
	delete up;

}
