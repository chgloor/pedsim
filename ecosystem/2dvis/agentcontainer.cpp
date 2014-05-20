//
// pedsim - A microscopic pedestrian simulation system.
// Copyright (c) by Christian Gloor
//

#include "agentcontainer.h"
#include "agent.h"

#include <iostream>

AgentContainer::AgentContainer() {
}


void AgentContainer::updatePosition(int id, double x, double y) {
    container[id]->x = x;
    container[id]->y = y;
    //    std::cout << id << " pos " << x << "/" << y << std::endl;
}
