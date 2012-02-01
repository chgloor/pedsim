//
// pedsim - A microscopic pedestrian simulation system. 
// Copyright (c) 2003 - 2012 by Christian Gloor
//                              

#include "ped_scene.h"
#include "ped_agent.h"
#include "ped_tree.h"

#include <stack>

using namespace std;


/// Default constructor.
/// \date    2012-01-17
Ped::Tscene::Tscene() {
	tree = new Ped::Ttree(this, 0, -200, -160, 400, 320);
}

/// Used to add a Tagent to the Tscene. 
/// \date    2012-01-17
/// \warning addAgent() does call Tagent::assignScene() to assign itself to the agent.
/// \param   *a A pointer to the Tagent to add. 
void Ped::Tscene::addAgent(Ped::Tagent *a) {
	agent.push_back(a);
	a->assignScene(this);
	tree->addAgent(a);
}


/// Used to add a Tobstacle to the Tscene.
/// \date    2012-01-17
/// \param   *o A pointer to the Tobstacle to add.
void Ped::Tscene::addObstacle(Ped::Tobstacle *o) {
	obstacle.push_back(o);
}


/// 
/// \date    2012-01-28
/// \param   
void Ped::Tscene::placeAgent(Ped::Tagent *a) {
	tree->addAgent(a);
}


/// 
/// \date    2012-01-28
/// \param   
void Ped::Tscene::moveAgent(Ped::Tagent *a) {
	treehash[a]->moveAgent(a);
}


/// 
/// \date    2012-01-28
/// \param   
void Ped::Tscene::cleanup() {
	tree->cut();
}


/// 
/// \date    2012-01-29
/// \return  
/// \param   
set<Ped::Tagent*> Ped::Tscene::getNeighbors(double x, double y, double dist) {
	stack<Ped::Ttree*> treestack;
	set<Ped::Tagent*> neighbors;
	treestack.push(tree);
	
	while(!treestack.empty()) {
		Ped::Ttree *t = treestack.top();
		treestack.pop();
		if (t->isleaf) {
			set<Ped::Tagent*> a = t->getAgents();
			neighbors.insert(a.begin(), a.end());
		} else {
			if (t->tree1->intersects(x, y, dist)) treestack.push(t->tree1); 
			if (t->tree2->intersects(x, y, dist)) treestack.push(t->tree2); 
			if (t->tree3->intersects(x, y, dist)) treestack.push(t->tree3); 
			if (t->tree4->intersects(x, y, dist)) treestack.push(t->tree4); 
		}
	}
	return neighbors;
}
