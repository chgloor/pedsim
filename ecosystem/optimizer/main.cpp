//
// pedsim - A microscopic pedestrian simulation system.
// Copyright (c) by Christian Gloor
//
// Use something like this to compile:
// g++ main.cpp -o optimizer -I../../libpedsim -lpedsim -L../../libpedsim
//
// To collect the output in a file::
// ./main > out.dat
//
// Process output in gnuplot:
// gnuplot> plot "out.dat"
//
// Check for memory leaks:
// valgrind --leak-check=yes ./main

#include "ped_includes.h"

#include <iostream>
#include <sstream>

using namespace std;


#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string>
#include <memory>
#include <sys/types.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>

int opensocket() {
    int s = socket(AF_INET, SOCK_DGRAM, 0);
    int optval = 1;
    socklen_t optlen;
    getsockopt(s, SOL_SOCKET, SO_REUSEADDR, &optval, &optlen);
    return s;
}


void sender(int socket, string smsg) {
    struct sockaddr_in to;
    int bytes_sent;
    const char *msg;

    memset(&to, 0, sizeof(to));
    to.sin_family = AF_INET;
    to.sin_addr.s_addr   = inet_addr("127.0.0.1");
    to.sin_port   = htons(2222);

    msg = smsg.c_str();
    bytes_sent = sendto(socket, msg, strlen(msg), 0, (struct sockaddr*)&to, sizeof(to));
    //    cout << smsg << " " << bytes_sent << endl;
}


int main(int argc, char *argv[]) {

    cout << "# PedSim Example using libpedsim version " << Ped::LIBPEDSIM_VERSION << endl;

    // setup
    Ped::Tscene *pedscene = new Ped::Tscene(); // no quadtree

    // add one waypoint (=destination) with a small radius of 10 at the right end.
    Ped::Twaypoint *w1 = new Ped::Twaypoint( 100, 0, 10);
    Ped::Twaypoint *w2 = new Ped::Twaypoint(-100, 0, 10);

    // create and add obstacle
    Ped::Tobstacle *o1 = new Ped::Tobstacle(0, 0, 0, 0);  // set pos later
    Ped::Tobstacle *o2 = new Ped::Tobstacle(0, 0, 0, 0);  // set pos later

    pedscene->addObstacle(new Ped::Tobstacle(-100, -50,  100, -50));
    pedscene->addObstacle(new Ped::Tobstacle(-100,  50,  100,  50));
    pedscene->addObstacle(new Ped::Tobstacle(-100, -50, -100,  50));
    pedscene->addObstacle(new Ped::Tobstacle( 100, -50,  100,  50));

    pedscene->addObstacle(new Ped::Tobstacle(-40, -5,  40, -5));
    pedscene->addObstacle(new Ped::Tobstacle(-40, -5, -100, -50));
    pedscene->addObstacle(new Ped::Tobstacle( 40, -5,  100, -50));
    pedscene->addObstacle(new Ped::Tobstacle(-40,  5, 40,  5));
    pedscene->addObstacle(new Ped::Tobstacle(-40,  5, -100,  50));
    pedscene->addObstacle(new Ped::Tobstacle( 40,  5,  100,  50));


    pedscene->addObstacle(o1);
    pedscene->addObstacle(o2);

    // create agents
    for (int i = 0; i<50; i++) {
        Ped::Tagent *a = new Ped::Tagent();
        a->setWaypointBehavior(Ped::Tagent::BEHAVIOR_ONCE);  // only once
        pedscene->addAgent(a);
    }

    // convenience
    const vector<Ped::Tagent*>& myagents = pedscene->getAllAgents();
    const vector<Ped::Tobstacle*>& myobstacles = pedscene->getAllObstacles();

    int s = opensocket();

    for (int h=0; h<10; h=h+1) {

        // move obstacle
        o1->setPosition(0,  30, 0,  10-h);
        o2->setPosition(0, -30, 0, -10+h);
        cout << "# " << o1->getStartPoint().to_string() << " " << o1->getEndPoint().to_string() << endl;
        cout << "# " << o2->getStartPoint().to_string() << " " << o2->getEndPoint().to_string() << endl;

        sender(s, "<message><reset/></message>");

        for (vector<Ped::Tobstacle*>::const_iterator it = myobstacles.begin(); it != myobstacles.end(); ++it) {
            std::ostringstream msg;
            msg << "<message><position type=\"obstacle\" id=\"" << (*it)->getid()
                << "\" x=\"" << (*it)->getax() << "\" y=\"" << (*it)->getay()
                << "\" dx=\"" << (*it)->getbx()-(*it)->getax() << "\" dy=\"" << (*it)->getby()-(*it)->getay()
                << "\"/></message>";
            sender(s, msg.str());
        }

        long int average_timestep = 0;
        for (int smooth=0; smooth < 1; smooth++) {

            // reset agents
            for (vector<Ped::Tagent*>::const_iterator it = myagents.begin(); it != myagents.end(); ++it) {
                if ((*it)->getid() % 2 == 0) {
                    (*it)->setPosition(-100+smooth*3, -25 + (*it)->getid(), 0);
                    (*it)->addWaypoint(w1);
                } else {
                    (*it)->setPosition( 100+smooth*3, -25 + (*it)->getid(), 0);
                    (*it)->addWaypoint(w2);
                }
            }

            // move all agents for 10 steps (and print their position)
            int notreached = myagents.size();
            long int timestep = 0;
            while (notreached > 0) {
                timestep++;
                notreached = myagents.size();
                pedscene->moveAgents(0.1);

                if (timestep % 100 == 0) {
                    std::ostringstream msg;
                    msg << "<message><timestep value=\"" << timestep << "\"/></message>";
                    sender(s, msg.str());
                }

                for (vector<Ped::Tagent*>::const_iterator it = myagents.begin(); it != myagents.end(); ++it) {
                    // cout << timestep << " " << (*it)->getPosition().to_string() << " " << (*it)->reachedDestination() << endl;
                    std::ostringstream msg;
                    msg << "<message><position type=\"agent\" id=\"" << (*it)->getid() << "\" x=\"" << (*it)->getPosition().x << "\" y=\"" << (*it)->getPosition().y <<    "\"/></message>";
                    sender(s, msg.str());

                    if ((*it)->reachedDestination()) notreached--;

                    if ((*it)->reachedDestination()) {
                        cout << "" << h << " " << timestep << endl;
                    }

                }
                if (timestep >= 100000) notreached = 0; // seems to run forever.
            }
            //            cout << "" << h << " " << timestep << endl;
            average_timestep += timestep;
        }
        cout << "# " << h << " " << 1.0*average_timestep/10 << endl;
    }


    // cleanup
    for (vector<Ped::Tagent*>::const_iterator it = myagents.begin(); it != myagents.end(); ++it) {
        delete *it;
    }
    delete pedscene;
    delete w1;
    delete w2;
    delete o1;
    delete o2;

}
