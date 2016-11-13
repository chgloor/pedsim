/// pedsim - A microscopic pedestrian simulation system.
/// Copyright (c) by Christian Gloor

#include "ped_includes.h"
#include <iostream>
#include <cstdlib>
#include <chrono>
#include <thread>
#include <cmath>
#include <algorithm>

using namespace std;


int main(int argc, char *argv[]) {
    cout << "PedSim Example using libpedsim version " << Ped::LIBPEDSIM_VERSION << endl;

    Ped::OutputWriter *ow = new Ped::UDPOutputWriter();
    ow->setScenarioName("Example 05");

    // setup
    Ped::Tscene *pedscene = new Ped::Tscene();
    pedscene->setOutputWriter(ow);

    Ped::Elevation *e = new Ped::Elevation("/home/chgloor/src/pedsim-3dvis/ecosystem/3dvis/ground2.asc");
    e->SetMeta(-125, -75, 1.0);
    pedscene->SetElevation(e);
    
    // outer boudaries
    pedscene->addObstacle(new Ped::Tobstacle(-125, 70,  125, 70));
    pedscene->addObstacle(new Ped::Tobstacle(-125, -70,  125, -70));
    pedscene->addObstacle(new Ped::Tobstacle(-125, 70,  -125, -70));
    pedscene->addObstacle(new Ped::Tobstacle( 125, 70,   125, -70));

    // bottleneck
    double w = 10;
    //    pedscene->addObstacle(new Ped::Tobstacle(  30,   -w,   30,  w));

    pedscene->addObstacle(new Ped::Tobstacle( -30,   w,   30,  w));
    pedscene->addObstacle(new Ped::Tobstacle( -30,  -w,   30, -w));

    pedscene->addObstacle(new Ped::Tobstacle( -30,  -w,   -100, -70));
    pedscene->addObstacle(new Ped::Tobstacle( -30,   w,   -100,  70));
    pedscene->addObstacle(new Ped::Tobstacle(  30,  -w,    100, -70));
    //    pedscene->addObstacle(new Ped::Tobstacle(  30,   w,    100,  70));

    pedscene->addObstacle(new Ped::Tobstacle(  60,  -70,    60, 70-w));
    pedscene->addObstacle(new Ped::Tobstacle( -60,  70-2*w,    60, 70-2*w));


    int nagents = 1;

    Ped::Twaypoint *w1 = new Ped::Twaypoint(-100, 60, 4);
    pedscene->addWaypoint(w1);
    Ped::Twaypoint *w2 = new Ped::Twaypoint(100, 0, 16);
    pedscene->addWaypoint(w2);

    for (int i = 0; i<nagents; i++) {
      Ped::Tagent *a = new Ped::Tagent();
      a->setPosition(0.0 + rand()/(RAND_MAX/40.0)-100.0, 0.0 + rand()/(RAND_MAX/30.0)-15.0, 0.0);
      a->addWaypoint(w1);
      a->addWaypoint(w2);
      a->setWaypointBehavior(Ped::Tagent::BEHAVIOR_ONCE);
      a->setfactorsocialforce(10.0);
      pedscene->addAgent(a);
    }
    
    // move all agents for a few steps
    long timestep = 0;

    for (int i=0; i<2000; ++i) {
        pedscene->moveAgents(0.4);

	std::this_thread::sleep_for(std::chrono::milliseconds(1000/25));
    }

    // cleanup
    for (auto a : pedscene->getAllAgents()) { delete a; };
    for (auto o : pedscene->getAllObstacles()) { delete o; };
    delete pedscene;

    return EXIT_SUCCESS;
}
