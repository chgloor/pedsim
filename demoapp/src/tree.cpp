//
// pedsim - A microscopic pedestrian simulation system. 
// Copyright (c) 2003 - 2004 by Christian Gloor
//     

#include "ped_agent.h"                         

#include "tree.h"
#include "config.h"
#include "scene.h"

#include <QPen>
#include <QGraphicsScene>

#include <iostream>
#include <algorithm>

using namespace std;

extern Config config;


/// Description: set intial values
/// \author  chgloor
/// \date    2012-01-28
Tree::Tree(QGraphicsScene *pscene, int pdepth, double px, double py, double pw, double ph){
	agentcount = 0;
	isleaf = true;
	scene = pscene;
	x = px; y = py; w = pw; h = ph;
	depth = pdepth;
	QPen p = QPen(QColor(88,0,0), 1, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);
	p.setCosmetic(true);
	rect = scene->addRect(x, y, w, h, p,  QBrush(QColor(depth*11, 0, 0)));
	rect->setZValue(-100+depth);
};

/// 
/// \author  chgloor
/// \date    2012-01-28
/// \return  
/// \warning 
/// \param   
Tree::~Tree() {
	if (!isleaf) {
		delete(tree1);
		delete(tree2);
		delete(tree3);
		delete(tree4);		
	}
	scene->removeItem(rect);	
	delete(rect);
}

/// 
/// \author  chgloor
/// \date    2012-01-28
/// \return  
/// \warning 
/// \param   
void Tree::addAgent(Ped::Tagent *a, Scene *pedscene) {
	if (isleaf) {
		agents.insert(a);
		pedscene->treehash[a] = this;
	} else {
		if ((a->getx() >= x+0.5f*w) && (a->gety() >= y+0.5f*h)) tree3->addAgent(a, pedscene); // 3
		if ((a->getx() <= x+0.5f*w) && (a->gety() <= y+0.5f*h)) tree1->addAgent(a, pedscene); // 1
		if ((a->getx() >= x+0.5f*w) && (a->gety() <= y+0.5f*h)) tree2->addAgent(a, pedscene); // 2
		if ((a->getx() <= x+0.5f*w) && (a->gety() >= y+0.5f*h)) tree4->addAgent(a, pedscene); // 4
	}
	if (agents.size() > 8) {
		isleaf = false;
		tree1 = new Tree(scene, depth+1, x, y, 0.5f*w, 0.5f*h);
		tree2 = new Tree(scene, depth+1, x+0.5f*w, y, 0.5f*w, 0.5f*h);
		tree3 = new Tree(scene, depth+1, x+0.5f*w, y+0.5f*h, 0.5f*w, 0.5f*h);
		tree4 = new Tree(scene, depth+1, x, y+0.5f*h, 0.5f*w, 0.5f*h);
		while (!agents.empty()) {
			Ped::Tagent *a = (*agents.begin());
			agents.erase(a);
			if ((a->getx() >= x+0.5f*w) && (a->gety() >= y+0.5f*h)) tree3->addAgent(a, pedscene); // 3
			if ((a->getx() <= x+0.5f*w) && (a->gety() <= y+0.5f*h)) tree1->addAgent(a, pedscene); // 1
			if ((a->getx() >= x+0.5f*w) && (a->gety() <= y+0.5f*h)) tree2->addAgent(a, pedscene); // 2
			if ((a->getx() <= x+0.5f*w) && (a->gety() >= y+0.5f*h)) tree4->addAgent(a, pedscene); // 4
		}
	}
}


/// 
/// \author  chgloor
/// \date    2012-01-28
/// \return  
/// \warning 
/// \param   
void Tree::moveAgent(Ped::Tagent *a, Scene *pedscene) {
	//	cout << "m";
	if ((a->getx() < x) || (a->getx() > (x+w)) || (a->gety() < y) || (a->gety() > (y+h))) {
		agents.erase(a);
		pedscene->placeAgent(a);		
	}	
}


/// 
/// \author  chgloor
/// \date    2012-01-28
/// \return  
/// \warning 
/// \param   
int Tree::cut(Scene *pedscene) {

	if (isleaf) {
		return agents.size();
	} else {
		int count = 0;
		count += tree1->cut(pedscene);
		count += tree2->cut(pedscene);
		count += tree3->cut(pedscene);
		count += tree4->cut(pedscene);
		if (count < 5) {
			agents = this->getAgents();
			// agentcount stays the same  --chgloor 2012-01-28
			isleaf = true;
			delete(tree1);
			delete(tree2);
			delete(tree3);
			delete(tree4);
			for (set<Ped::Tagent*>::iterator it = agents.begin(); it != agents.end(); ++it) {
				pedscene->treehash[(*it)] = this;
			}
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
set<Ped::Tagent*> Tree::getAgents() {
	if (isleaf) {
		return agents;
	} else {
		set<Ped::Tagent*> ta;
		set<Ped::Tagent*> t1 = tree1->getAgents();		
		set<Ped::Tagent*> t2 = tree2->getAgents();		
		set<Ped::Tagent*> t3 = tree3->getAgents();		
		set<Ped::Tagent*> t4 = tree4->getAgents();		
		ta.insert(t1.begin(), t1.end());
		ta.insert(t2.begin(), t2.end());
		ta.insert(t3.begin(), t3.end());
		ta.insert(t4.begin(), t4.end());
		return ta;
	}
}

/// 
/// \author  chgloor
/// \date    2012-01-29
/// \return  
/// \warning 
/// \param   
bool Tree::intersects(double px, double py, double pr) {
	if (((px+pr) > x) && ((px-pr) < (x+w)) && ((py+pr) > y) && ((py-pr) < (y+h))) return true; // x+-r/y+-r is inside
	return false;
}
