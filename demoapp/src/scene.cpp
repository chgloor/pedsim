//
// pedsim - A microscopic pedestrian simulation system. 
// Copyright (c) 2003 - 2004 by Christian Gloor
//                              

#include "scene.h"
#include "config.h"
#include "tree.h"

#include "ped_agent.h"

#include <QPen>
#include <QGraphicsScene>

#include <iostream>
#include <stack>

using namespace std;

extern Config config;


/// Description: set intial values
/// \author  chgloor
/// \date    2012-01-28
Scene::Scene(QGraphicsScene *pscene) : Tscene() {
  scene = pscene;
  //  ellipse = scene->addEllipse(getx()-getr(), gety()-getr(), getr()*2, getr()*2, QPen(QColor(44,0,0), 0.5, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin), QBrush(QColor(44, 0, 0)));
  tree = new Tree(scene, 0, -200, -160, 400, 320);
};


/// 
/// \author  chgloor
/// \date    2012-01-28
Scene::Scene() : Tscene() {
};


/// 
/// \author  chgloor
/// \date    2012-01-28
/// \return  
/// \warning 
/// \param   
void Scene::addAgent(Ped::Tagent *a) {
	tree->addAgent(a, this);
	Ped::Tscene::addAgent(a);
}

/// 
/// \author  chgloor
/// \date    2012-01-28
/// \return  
/// \warning 
/// \param   
void Scene::placeAgent(Ped::Tagent *a) {
	tree->addAgent(a, this);
}

/// 
/// \author  chgloor
/// \date    2012-01-28
/// \return  
/// \warning 
/// \param   
void Scene::moveAgent(Ped::Tagent *a) {
	treehash[a]->moveAgent(a, this);
}

/// 
/// \author  chgloor
/// \date    2012-01-28
/// \return  
/// \warning 
/// \param   
void Scene::cleanup() {
	tree->cut(this);
	//	cout << treehash.size();
}

/// 
/// \author  chgloor
/// \date    2012-01-29
/// \return  
/// \warning 
/// \param   
set<Ped::Tagent*> Scene::getNeighbors(double x, double y, double dist) {
	stack<Tree*> treestack;
	set<Ped::Tagent*> neighbors;
	treestack.push(tree);
	
	while(!treestack.empty()) {
		Tree *t = treestack.top();
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
