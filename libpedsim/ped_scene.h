//
// pedsim - A microscopic pedestrian simulation system. 
// Copyright (c) 2003 - 2012 by Christian Gloor
//                              

#ifndef _ped_scene_h_
#define _ped_scene_h_ 1

//#include "ped_agent.h"
//#include "ped_obstacle.h"
#include "ped_vector.h"
#include "ped_waypoint.h"

#include <vector>

class Tagent;
class Tobstacle;

/// A container for the agents. Defined here because some methods inside the Tagent class iterate over this container
#define AgentContainer vector<Tagent*>
/// A container iterator for the agents. Defined here because some methods inside the Tagent class iterate over this container
#define AgentIterator vector<Tagent*>::iterator

/// A container for the obstacles. Defined here because some methods inside the Tobstacle class iterate over this container
#define ObstacleContainer vector<Tobstacle*>

/// A container iterator for the obstacles. Defined here because some methods inside the Tobstacle class iterate over this container
#define ObstacleIterator vector<Tobstacle*>::iterator


using namespace std;


/// Class that defines a Tscene object
/// \author  chgloor
/// \date    2012-01-17
class Tscene {
 private:

  
 public:
  Tscene();

  AgentContainer agent;                             
  ObstacleContainer obstacle;
  //  WaypointContainer waypoint;
  
  void addAgent(Tagent *a);
  void addObstacle(Tobstacle *o);
};

#endif
