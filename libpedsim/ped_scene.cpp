//
// pedsim - A microscopic pedestrian simulation system. 
// Copyright (c) 2003 - 2012 by Christian Gloor
//                              

#include "ped_scene.h"
#include "ped_agent.h"

using namespace std;


/// Default constructor.
/// \date    2012-01-17
Ped::Tscene::Tscene() {}

/// Used to add a Tagent to the Tscene. 
/// \date    2012-01-17
/// \warning addAgent() does call Tagent::assignScene() to assign itself to the agent.
/// \param   *a A pointer to the Tagent to add. 
void Ped::Tscene::addAgent(Ped::Tagent *a) {
	agent.push_back(a);
	a->assignScene(this);
}


/// Used to add a Tobstacle to the Tscene.
/// \date    2012-01-17
/// \param   *o A pointer to the Tobstacle to add.
void Ped::Tscene::addObstacle(Ped::Tobstacle *o) {
	obstacle.push_back(o);
}

