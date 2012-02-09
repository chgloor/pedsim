//
// pedsim - A microscopic pedestrian simulation system. 
// Copyright (c) 2003 - 2004 by Christian Gloor
//     

#include "ped_agent.h"                         
#include "ped_scene.h"
#include "ped_tree.h"

#include <iostream>
//#include <algorithm>

#include "assert.h"

using namespace std;


/// Description: set intial values
/// \author  chgloor
/// \date    2012-01-28
// Ped::Ttree::Ttree(int pdepth, double px, double py, double pw, double ph){
Ped::Ttree::Ttree(Ped::Tscene *pscene, int pdepth, double px, double py, double pw, double ph){
	scene = pscene;
	agentcount = 0;
	isleaf = true;
	x = px; y = py; w = pw; h = ph;
	depth = pdepth;
};


/// 
/// \author  chgloor
/// \date    2012-01-28
/// \return  
/// \warning 
/// \param   
Ped::Ttree::~Ttree() {
	assert(isleaf == true); // newer delete a tree that is not a leaf, please
}

/// 
/// \author  chgloor
/// \date    2012-01-28
/// \return  
/// \warning 
/// \param   
//void Ped::Ttree::addAgent(Ped::Tagent *a, Ped::Tscene *pedscene) {
void Ped::Ttree::addAgent(const Ped::Tagent *a) {
	if (isleaf) {
		agents.insert(a);
		scene->treehash[a] = this;
	} else {
		if ((a->getx() >= x+0.5f*w) && (a->gety() >= y+0.5f*h)) tree3->addAgent(a); // 3
		if ((a->getx() <= x+0.5f*w) && (a->gety() <= y+0.5f*h)) tree1->addAgent(a); // 1
		if ((a->getx() >= x+0.5f*w) && (a->gety() <= y+0.5f*h)) tree2->addAgent(a); // 2
		if ((a->getx() <= x+0.5f*w) && (a->gety() >= y+0.5f*h)) tree4->addAgent(a); // 4
	}
	if (agents.size() > 8) {
		isleaf = false;
		addChildren();
		while (!agents.empty()) {
			const Ped::Tagent *a = (*agents.begin());
			if ((a->getx() >= x+0.5f*w) && (a->gety() >= y+0.5f*h)) tree3->addAgent(a); // 3
			if ((a->getx() <= x+0.5f*w) && (a->gety() <= y+0.5f*h)) tree1->addAgent(a); // 1
			if ((a->getx() >= x+0.5f*w) && (a->gety() <= y+0.5f*h)) tree2->addAgent(a); // 2
			if ((a->getx() <= x+0.5f*w) && (a->gety() >= y+0.5f*h)) tree4->addAgent(a); // 4
			agents.erase(a);
		}
	}
}

void Ped::Ttree::addChildren() {
	tree1 = new Ped::Ttree(scene, depth+1, x, y, 0.5f*w, 0.5f*h);
	tree2 = new Ped::Ttree(scene, depth+1, x+0.5f*w, y, 0.5f*w, 0.5f*h);
	tree3 = new Ped::Ttree(scene, depth+1, x+0.5f*w, y+0.5f*h, 0.5f*w, 0.5f*h);
	tree4 = new Ped::Ttree(scene, depth+1, x, y+0.5f*h, 0.5f*w, 0.5f*h);
}

/// 
/// \author  chgloor
/// \date    2012-01-28
/// \return  
/// \warning 
/// \param   
// void Ped::Ttree::moveAgent(Ped::Tagent *a, Ped::Tscene *pedscene) {
void Ped::Ttree::moveAgent(const Ped::Tagent *a) {
	if ((a->getx() < x) || (a->getx() > (x+w)) || (a->gety() < y) || (a->gety() > (y+h))) {
		scene->placeAgent(a);		
		agents.erase(a);
	}	
}


/// 
/// \author  chgloor
/// \date    2012-01-28
/// \return  
/// \warning 
/// \param   
//int Ped::Ttree::cut(Ped::Tscene *pedscene) {
int Ped::Ttree::cut() {
	if (isleaf) {
		// for (int i=0; i<depth; i++) cout << "- ";
		// cout << "L " << agents.size() << endl;
		return agents.size();		
	} else {
		// for (int i=0; i<depth; i++) cout << "- ";
		// cout << "N " << endl;
		int count = 0;
		count += tree1->cut();
		count += tree2->cut();
		count += tree3->cut();
		count += tree4->cut();
		if (count < 5) {
			// for (int i=0; i<depth; i++) cout << "- ";
			// cout << "C ";
			//			agents = this->getAgents();
			assert(tree1->isleaf == true);
			assert(tree2->isleaf == true);
			assert(tree3->isleaf == true);
			assert(tree4->isleaf == true);
			agents.insert(tree1->agents.begin(), tree1->agents.end());
			agents.insert(tree2->agents.begin(), tree2->agents.end());
			agents.insert(tree3->agents.begin(), tree3->agents.end());
			agents.insert(tree4->agents.begin(), tree4->agents.end());
			//			cout << agents.size() << endl;
			// agentcount stays the same  --chgloor 2012-01-28
			isleaf = true;
			for (set<const Ped::Tagent*>::iterator it = agents.begin(); it != agents.end(); ++it) {
				const Tagent *a = (*it);
				scene->treehash[a] = this;
			}
			delete(tree1);
			delete(tree2);
			delete(tree3);
			delete(tree4);
		}
		return count;
	}
}


/// 
/// \author  chgloor
/// \date    2012-01-28
/// \return  
/// \warning 
/// \param   
set<const Ped::Tagent*> Ped::Ttree::getAgents() const {
	set<const Ped::Tagent*> ta;
	if (isleaf) {
		return agents;
	} else {
		set<const Ped::Tagent*> t1 = tree1->getAgents();		
		set<const Ped::Tagent*> t2 = tree2->getAgents();		
		set<const Ped::Tagent*> t3 = tree3->getAgents();		
		set<const Ped::Tagent*> t4 = tree4->getAgents();		
		ta.insert(t1.begin(), t1.end());
		ta.insert(t2.begin(), t2.end());
		ta.insert(t3.begin(), t3.end());
		ta.insert(t4.begin(), t4.end());
	}
	return ta;
}


/// 
/// \author  chgloor
/// \date    2012-01-29
/// \return  
/// \warning 
/// \param   
bool Ped::Ttree::intersects(double px, double py, double pr) const {
	if (((px+pr) > x) && ((px-pr) < (x+w)) && ((py+pr) > y) && ((py-pr) < (y+h))) return true; // x+-r/y+-r is inside
	return false;
}
