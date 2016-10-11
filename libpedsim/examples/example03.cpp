// pedsim - A microscopic pedestrian simulation system.
// Copyright (c) by Christian Gloor
//
// Use somethin like this to compile:
// g++ examples/example03.cpp -o example03 -lpedsim -L. -I. -std=c++11
//   export LD_LIBRARY_PATH=.
//   ./example03

#include "ped_includes.h"
#include <iostream>
#include <cstdlib>
#include <chrono>
#include <thread>
#include <cmath>

using namespace std;

// Returns 1 if the lines intersect, otherwise 0. In addition, if the lines 
// intersect the intersection point may be stored in the floats i_x and i_y.
// Based on an algorithm in Andre LeMothe's "Tricks of the Windows Game Programming Gurus"
int Intersection(Ped::Tvector p0, Ped::Tvector p1, Ped::Tvector p2, Ped::Tvector p3, Ped::Tvector *intersection) {
  Ped::Tvector s1(p1.x - p0.x, p1.y - p0.y);
  Ped::Tvector s2(p3.x - p2.x, p3.y - p2.y);

  float s = (-s1.y * (p0.x - p2.x) + s1.x * (p0.y - p2.y)) / (-s2.x * s1.y + s1.x * s2.y);
  float t = ( s2.x * (p0.y - p2.y) - s2.y * (p0.x - p2.x)) / (-s2.x * s1.y + s1.x * s2.y);

  if (s >= 0 && s <= 1 && t >= 0 && t <= 1) { // intersection
    if (intersection != NULL) {
      intersection->x = p0.x + (t * s1.x);
      intersection->y = p0.y + (t * s1.y);
    }
    return 1;
  }

  return 0; // No intersection
}

Ped::Tvector rotate(Ped::Tvector lf, double theta) { // theta in rad
    return Ped::Tvector(lf.x * cos(theta) - lf.y * sin(theta), lf.x * sin(theta) + lf.y * cos(theta));
}


/// New class that inherits from the library agent class.  It shows how the
/// myForce() method can be used to add an additional force component to an
/// agent to change its behaviour.
class Tagent2: public Ped::Tagent {

public:
  Tagent2(Ped::OutputWriter *ow) : Ped::Tagent(), ow(ow) {
    factorobstacleforce = 10.0;
    factordesiredforce = 0.0;
    factorlookaheadforce = 0.0;

    v.x = 1; // need some initial direction
  }

private:
  Ped::OutputWriter *ow;

  double distance_sensor(Ped::Tvector direction) {
    double distance = std::numeric_limits<double>::infinity();
    Ped::Tvector intersection;
    bool has_intersection = false;
    for (auto obstacle : scene->getAllObstacles()) {
      Ped::Tvector ray = 1000.0 * direction.normalized(); // max sensor view distance
      Ped::Tvector possibleintersection;
      if (Intersection(p, p + ray, obstacle->getStartPoint(), obstacle->getEndPoint(), &possibleintersection) == 1) {
	Ped::Tvector distvector = possibleintersection - p;
	double d = distvector.length();
	if (d < distance) { 
	  distance = d;
	  intersection = possibleintersection;
	}
	has_intersection = true;
      }
      
    }

    if (has_intersection) {
      ow->drawLine(p, intersection);
    }
    return distance;
  }

  Ped::Tvector myForce(Ped::Tvector e, const set<const Ped::Tagent*> &neighbors) {
    Ped::Tvector lf;
    obstacleforce = obstacleForce(neighbors);
    lf = v.normalized();

    Ped::Tvector r1 = rotate(lf, 0.2);
    Ped::Tvector r2 = rotate(lf, -0.2);

    double distance1 = distance_sensor(r1);
    double distance2 = distance_sensor(r2);

    if ((distance1 < 50) || (distance2 < 50)){
      if (distance1 < distance2) {
	return rotate(lf, -0.01);      
      } else {
	return rotate(lf, 0.01);      
      }
    } else {
      return lf;
    }
  }

};


int main(int argc, char *argv[]) {
    cout << "PedSim Example using libpedsim version " << Ped::LIBPEDSIM_VERSION << endl;

    Ped::OutputWriter *ow = new Ped::FileOutputWriter();
    ow->setScenarioName("Example 03");

    // setup
    Ped::Tscene *pedscene = new Ped::Tscene(-200, -200, 400, 400);
    pedscene->setOutputWriter(ow);

    // Ped::Twaypoint *w1 = new Ped::Twaypoint(-100, 0, 24);
    // Ped::Twaypoint *w2 = new Ped::Twaypoint(+100, 0, 120);

    pedscene->addObstacle(new Ped::Tobstacle(0, -50,  0, +50));
    pedscene->addObstacle(new Ped::Tobstacle(-62,  -70,  -62, -10));
    pedscene->addObstacle(new Ped::Tobstacle(-62,   10,  -62,  70));
    pedscene->addObstacle(new Ped::Tobstacle( 62,  -70,   62, -10));
    pedscene->addObstacle(new Ped::Tobstacle( 62,   10,   62,  70));
    pedscene->addObstacle(new Ped::Tobstacle(-125, 70,  125, 70));
    pedscene->addObstacle(new Ped::Tobstacle(-125, -70,  125, -70));
    pedscene->addObstacle(new Ped::Tobstacle(-125, 70,  -125, -70));
    pedscene->addObstacle(new Ped::Tobstacle( 125, 70,   125, -70));

    int nagents = 50;

    for (int i = 0; i<nagents; i++) {
        Ped::Tagent *a = new Tagent2(ow);
	//        a->addWaypoint(w1);
	//  a->addWaypoint(w2);
        a->setPosition(0 + rand()/(RAND_MAX/100)-100, 0 + rand()/(RAND_MAX/30)-15, 0);
        pedscene->addAgent(a);
    }

    // move all agents for a few steps
    long timestep = 0;
    //    while (true) {
    for (int i=0; i<10000; ++i) {
        pedscene->moveAgents(0.4);
	//	std::this_thread::sleep_for(std::chrono::milliseconds(1000/25));
	cout << timestep++ << endl;
    }

    // cleanup
    for (auto a : pedscene->getAllAgents()) { delete a; };
    for (auto o : pedscene->getAllObstacles()) { delete o; };
    //    for (auto w : pedscene->getAllWaypoints()) { delete w; };
    delete pedscene;

    return EXIT_SUCCESS;
}
