//
// pedsim - A microscopic pedestrian simulation system. 
// Copyright (c) 2003 - 2004 by Christian Gloor
//                              

#include "ped_scene.h"
#include "ped_agent.h"

using namespace std;


/// 
/// \author  chgloor
/// \date    2012-01-17
/// \return  
/// \warning 
/// \param   
Tscene::Tscene() {

}

/// 
/// \author  chgloor
/// \date    2012-01-17
/// \return  
/// \warning 
/// \param   
void Tscene::addAgent(Tagent *a) {
	agent.push_back(a);
	a->assignScene(this);
}


/// 
/// \author  chgloor
/// \date    2012-01-17
/// \return  
/// \warning 
/// \param   
void Tscene::addObstacle(Tobstacle *o) {
	obstacle.push_back(o);
}

