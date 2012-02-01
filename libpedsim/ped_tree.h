//
// pedsim - A microscopic pedestrian simulation system. 
// Copyright (c) 2003 - 2012 by Christian Gloor
//                              

#ifndef _ped_tree_h_
#define _ped_tree_h_ 1

#include <iostream>
#include <set>

using namespace std;

namespace Ped {
	
	class Tscene;
	class Tagent;
	
	class Ttree {
	private:
		int agentcount;
		set<Ped::Tagent*> agents; // set and not vector, since we need to delete elements from the middle very often
		

	protected:
		Ped::Tscene *scene;
		double x;
		double y;
		double w;
		double h;
		int depth;
		

	public:
		//		Ttree(int depth, double x, double y, double w, double h);
		Ttree(Ped::Tscene *scene, int depth, double x, double y, double w, double h);
		virtual ~Ttree();
		
		/* virtual void addAgent(Ped::Tagent *a, Ped::Tscene *pedscene); */
		/* virtual void moveAgent(Ped::Tagent *a, Ped::Tscene *pedscene); */
		virtual void addAgent(Ped::Tagent *a);
		virtual void moveAgent(Ped::Tagent *a);
		virtual set<Ped::Tagent*> getAgents(); // vector, b/c it is used only for transfer
		
		virtual bool intersects(double px, double py, double pr);
		
		/* virtual int cut(Ped::Tscene *pedscene); */
		virtual int cut();
		virtual void addChildren();

		Ttree *tree1;
		Ttree *tree2;
		Ttree *tree3;
		Ttree *tree4;
		
		bool isleaf;		
	};
};

#endif
