// pedsim - A microscopic pedestrian simulation system.
// Copyright (c) by Christian Gloor

#include "ped_includes.h"
#include <iostream>
#include <cstdlib>
#include <chrono>
#include <thread>
#include <cmath>
#include <algorithm>

using namespace std;


class Tagent2: public Ped::Tagent {

public:
  Tagent2(Ped::OutputWriter *ow) : Ped::Tagent(), ow(ow), sensor_sensitivity(0.1) {
    factorobstacleforce = 10.0;
    factordesiredforce = 0.0;
    factorlookaheadforce = 0.0;
    v.x = 1; // needs some initial direction
  }

private:
  Ped::OutputWriter *ow;
  double sensor_sensitivity;

  double distance_sensor(Ped::Tvector direction) {
    double distance = std::numeric_limits<double>::infinity();
    Ped::Tvector intersection;
    bool has_intersection = false;
    for (auto obstacle : scene->getAllObstacles()) {
      Ped::Tvector ray = direction.normalized().scaled(1000.0); // max sensor view distance
      Ped::Tvector possibleintersection;
      if (Ped::Tvector::lineIntersection(p, p + ray, obstacle->getStartPoint(), obstacle->getEndPoint(), &possibleintersection) == 1) {
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
      ow->drawLine(p, intersection, 1, 0.5, 0.5, 0.5);
    }
    return distance;
  }

  Ped::Tvector myForce(Ped::Tvector e, const set<const Ped::Tagent*> &neighbors) {
    Ped::Tvector lf;
    obstacleforce = obstacleForce(neighbors);
    if (obstacleforce.length() > 0.001) {
      sensor_sensitivity += 0.01;
      auto p1 = p + obstacleforce.scaled(100.0);
      ow->drawLine(p, p1, 10, 1.0, 0.0, 0.0);
    }
    lf = v.normalized();

    Ped::Tvector r1 = lf.rotated(0.5);
    Ped::Tvector r2 = lf.rotated(-0.5);

    double distance1 = distance_sensor(r1);
    double distance2 = distance_sensor(r2);

    double x = sensor_sensitivity * (1.0 / min(distance1, distance2)) * ((distance1>distance2) ? 1.0 : -1.0);
    sensor_sensitivity -= 0.0001;
    return lf.rotated(x);
  }

};


int main(int argc, char *argv[]) {
    cout << "PedSim Example using libpedsim version " << Ped::LIBPEDSIM_VERSION << endl;

    Ped::OutputWriter *ow = new Ped::UDPOutputWriter();
    ow->setScenarioName("Example 03");

    // setup
    Ped::Tscene *pedscene = new Ped::Tscene(-200, -200, 400, 400);
    pedscene->setOutputWriter(ow);

    pedscene->addObstacle(new Ped::Tobstacle(0, -50,  0, +50));
    pedscene->addObstacle(new Ped::Tobstacle(-62,  -70,  -62, -10));
    pedscene->addObstacle(new Ped::Tobstacle(-62,   10,  -62,  70));
    pedscene->addObstacle(new Ped::Tobstacle( 62,  -70,   62, -10));
    pedscene->addObstacle(new Ped::Tobstacle( 62,   10,   62,  70));
    pedscene->addObstacle(new Ped::Tobstacle(-125, 70,  125, 70));
    pedscene->addObstacle(new Ped::Tobstacle(-125, -70,  125, -70));
    pedscene->addObstacle(new Ped::Tobstacle(-125, 70,  -125, -70));
    pedscene->addObstacle(new Ped::Tobstacle( 125, 70,   125, -70));

    int nagents = 10;

    for (int i = 0; i<nagents; i++) {
        Ped::Tagent *a = new Tagent2(ow);
        a->setPosition(0 + rand()/(RAND_MAX/100)-100, 0 + rand()/(RAND_MAX/30)-15, 0);
        pedscene->addAgent(a);
    }

    // move all agents for a few steps
    long timestep = 0;
    for (int i=0; i<10000; ++i) {
        pedscene->moveAgents(0.4);
	std::this_thread::sleep_for(std::chrono::milliseconds(1000/66));
    }

    // cleanup
    for (auto a : pedscene->getAllAgents()) { delete a; };
    for (auto o : pedscene->getAllObstacles()) { delete o; };
    delete pedscene;

    return EXIT_SUCCESS;
}
