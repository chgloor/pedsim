//
// pedsim - A microscopic pedestrian simulation system. 
// Copyright (c) 2003 - 2012 by Christian Gloor
//                              

#ifndef _ped_tree_h_
#define _ped_tree_h_ 1

#ifdef WIN32
#define LIBEXPORT __declspec(dllexport)
#else
#define LIBEXPORT
#endif


#include <set>

using namespace std;

namespace Ped {
	
	class Tscene;
	class Tagent;
	
	class LIBEXPORT Ttree {
		friend class Tscene;
	private:
		int agentcount;
		set<Ped::Tagent*> agents;  // set and not vector, since we need to delete elements from the middle very often
		
		bool isleaf;		
		double x;
		double y;
		double w;
		double h;
		int depth;

		Ped::Tscene *scene;

	protected:
		Ttree *tree1;
		Ttree *tree2;
		Ttree *tree3;
		Ttree *tree4;

		virtual int cut();		
		virtual void addChildren();

	public:
		Ttree(Ped::Tscene *scene, int depth, double x, double y, double w, double h);
		virtual ~Ttree();

		virtual void addAgent(Ped::Tagent *a);
		virtual void moveAgent(Ped::Tagent *a);

		virtual set<Ped::Tagent*> getAgents() const; 
		
		virtual bool intersects(double px, double py, double pr) const;		

		double getx() const { return x; };                    
		double gety() const { return y; };                    
		double getw() const { return w; };                    
		double geth() const { return h; };                    

		double getdepth() const { return depth; };                    

	};
};

#endif
