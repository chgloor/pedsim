//
// pedsim - A microscopic pedestrian simulation system.
// Copyright (c) by Christian Gloor
//
// Use something like this to compile:
// g++ examples/example01.cpp -o example01 -I. -lpedsim -L. -g -std=c++0x
//
// Check for memory leaks e.g. like this:
// valgrind --leak-check=yes ./example

#include <iostream>
#include <cstdlib> // rand

#include "ped_includes.h"

#include "ped_outputwriter.h"

using namespace std;

int main(int argc, char *argv[]) {

    Ped::OutputWriter *ow = new Ped::CSV_OutputWriter();

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

    // Move all agents for 10 steps (and print their position through the outputwriter)
    for (int i=0; i<10; ++i) {
        pedscene->moveAgents(0.2);
    }

    // Cleanup
    for (Ped::Tagent* agent : pedscene->getAllAgents()) delete agent;
    delete pedscene;
    delete w1;
    delete w2;
    delete o;
}
