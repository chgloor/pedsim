//
// pedsim - A microscopic pedestrian simulation system. 
// Copyright (c) 2003 - 2012 by Christian Gloor
//                              

#ifndef _ped_scene_h_
#define _ped_scene_h_ 1

#ifdef WIN32
#define LIBEXPORT __declspec(dllexport)
#else
#define LIBEXPORT
#endif

#include "ped_vector.h"
#include "ped_waypoint.h"

#include <vector>

namespace Ped {

	class Tagent;
	class Tobstacle;
	
	/// A container for the agents. Defined here because some methods inside the Ped::Tagent class iterate over this container
#define AgentContainer vector<Tagent*>
	/// A container iterator for the agents. Defined here because some methods inside the Ped::Tagent class iterate over this container
#define AgentIterator vector<Tagent*>::iterator
	
	/// A container for the obstacles. Defined here because some methods inside the Tobstacle class iterate over this container
#define ObstacleContainer vector<Tobstacle*>
	/// A container iterator for the obstacles. Defined here because some methods inside the Tobstacle class iterate over this container
#define ObstacleIterator vector<Tobstacle*>::iterator
	
	using namespace std;
	
	
	/// Class that defines a Tscene object
	/// \author  chgloor
	/// \date    2010-02-12
	class LIBEXPORT Tscene {
	private:

		friend class Ped::Tagent;
		AgentContainer agent;                             
		ObstacleContainer obstacle;

	public:
		Tscene();
		
		void virtual addAgent(Tagent *a);
		void addObstacle(Tobstacle *o);

		
	};

}
#endif
