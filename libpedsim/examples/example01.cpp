// pedsim - A microscopic pedestrian simulation system.
// Copyright (c) by Christian Gloor

#include <iostream>
#include <cstdlib>
#include <chrono>
#include <thread>

#include "ped_includes.h"

#include "ped_outputwriter.h"

using namespace std;

int main(int argc, char *argv[]) {

    // create an output writer which will send output to a file 
    Ped::OutputWriter *ow = new Ped::FileOutputWriter();
    ow->setScenarioName("Example 01");

    cout << "PedSim Example using libpedsim version " << Ped::LIBPEDSIM_VERSION << endl;

    // Setup
    Ped::Tscene *pedscene = new Ped::Tscene(-200, -200, 400, 400);

    pedscene->setOutputWriter(ow);

    Ped::Twaypoint *w1 = new Ped::Twaypoint(-100, 0, 24);
    Ped::Twaypoint *w2 = new Ped::Twaypoint(+100, 0, 12);

    Ped::Tobstacle *o = new Ped::Tobstacle(0, -50,  0, +50);
    pedscene->addObstacle(o);

    for (int i = 0; i<10; i++) {
        Ped::Tagent *a = new Ped::Tagent();

        a->addWaypoint(w1);
        a->addWaypoint(w2);

        a->setPosition(-50 + rand()/(RAND_MAX/80)-40, 0 + rand()/(RAND_MAX/20) -10, 0);

        pedscene->addAgent(a);
    }

    // Move all agents for 700 steps (and write their position through the outputwriter)
    for (int i=0; i<700; ++i) {
        pedscene->moveAgents(0.3);
	std::this_thread::sleep_for(std::chrono::milliseconds(3));
    }

    // Cleanup
    for (Ped::Tagent* agent : pedscene->getAllAgents()) delete agent;
    delete pedscene;
    delete w1;
    delete w2;
    delete o;
    delete ow;

    return EXIT_SUCCESS;
}
