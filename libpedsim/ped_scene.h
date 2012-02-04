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

#include <set>
#include <vector>
#include <map>

namespace Ped {

	class Tagent;
	class Tobstacle;
	class Ttree;
	
	using namespace std;	
	
	/// Class that defines a Tscene object
	/// \author  chgloor
	/// \date    2010-02-12
	class LIBEXPORT Tscene {
		friend class Ped::Tagent;
		friend class Ped::Ttree;

	private:
		vector<Tagent*> agent;                            
		vector<Tobstacle*> obstacle;

	protected:
		Ttree *tree;
		void placeAgent(Ped::Tagent *a);

	public:
		Tscene();
		virtual ~Tscene();

		virtual void addObstacle(Tobstacle *o);
		
		virtual void addAgent(Tagent *a);
		virtual void moveAgent(Ped::Tagent *a);

		virtual void cleanup();
		virtual void moveAgents(double h);
		
		set<Ped::Tagent*> getNeighbors(double x, double y, double dist);
		map<Ped::Tagent*, Ttree*> treehash;		
	};
};
#endif
