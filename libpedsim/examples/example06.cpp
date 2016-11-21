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
    ow->setScenarioName("Example 06");

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

    // bottlenecks
    double w = 5;
    pedscene->addObstacle(new Ped::Tobstacle( -90, -70,  -90,  -30 - w)); // |
    pedscene->addObstacle(new Ped::Tobstacle( -60, -70,  -60,  -30 - w)); // |
    pedscene->addObstacle(new Ped::Tobstacle( -90, -30 - w,  -60, -30 - w)); // --
    pedscene->addObstacle(new Ped::Tobstacle( -90, -30 + w,  -30, -30 + w)); // --
    pedscene->addObstacle(new Ped::Tobstacle( -90, -30 + w,  -90, -w)); // |
    //    pedscene->addObstacle(new Ped::Tobstacle( -30, -30 + w,  -30, -w)); // |
    pedscene->addObstacle(new Ped::Tobstacle( -90,  -w,  -30, -w)); // --
    pedscene->addObstacle(new Ped::Tobstacle( -90,   w,  -60,  w)); // --
    pedscene->addObstacle(new Ped::Tobstacle( -90,  30 - w,  -90, +w)); // |
    pedscene->addObstacle(new Ped::Tobstacle( -60,  30 - w,  -60, +w)); // |
    pedscene->addObstacle(new Ped::Tobstacle( -90,  30 + w,  -60,  30 + w)); // --
    pedscene->addObstacle(new Ped::Tobstacle( -90,  30 - w,  -60,  30 - w)); // --
    pedscene->addObstacle(new Ped::Tobstacle( -90,  70,  -90,  30 + w)); // |
    pedscene->addObstacle(new Ped::Tobstacle( -60,  70,  -60,  30 + w)); // |

    // +
    pedscene->addObstacle(new Ped::Tobstacle( -30,  -70,  -30,  -30 + w)); // |
    pedscene->addObstacle(new Ped::Tobstacle( -30,  70 - 2*w,  -30,   -w)); // |
    pedscene->addObstacle(new Ped::Tobstacle( -30,  70 - 2*w,  0, 70-2*w)); // --
    pedscene->addObstacle(new Ped::Tobstacle( 0, -70,  0, 70-2*w)); // |

    // -| |---| |- (aka T)
    pedscene->addObstacle(new Ped::Tobstacle( 30,  70-2*w, 125-2*w, 70-2*w)); // --
    pedscene->addObstacle(new Ped::Tobstacle( 125-2*w,  30, 125-2*w, 70-2*w)); // |
    pedscene->addObstacle(new Ped::Tobstacle( 30,  30, 30, 70-2*w)); // |
    pedscene->addObstacle(new Ped::Tobstacle( 30,  30, 60, 30)); // --
    pedscene->addObstacle(new Ped::Tobstacle( 90,  30, 125-2*w, 30)); // --
    pedscene->addObstacle(new Ped::Tobstacle( 60,  30, 60, -70)); // |
    pedscene->addObstacle(new Ped::Tobstacle( 90,  30, 90, -70)); // |
    

    int nagents = 25;

    Ped::Twaypoint *w1 = new Ped::Twaypoint(100, -60, 4);
    pedscene->addWaypoint(w1);

    for (int i = 0; i<nagents; i++) {
      Ped::Tagent *a = new Ped::Tagent();
      a->setPosition(0.0 + rand()/(RAND_MAX/10.0)-110.0, 0.0 + rand()/(RAND_MAX/50.0)-25.0, 0.0);
      a->addWaypoint(w1);
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
