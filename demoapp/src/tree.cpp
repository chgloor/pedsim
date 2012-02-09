//
// pedsim - A microscopic pedestrian simulation system. 
// Copyright (c) 2003 - 2012 by Christian Gloor
//     

#include "ped_agent.h"                         

#include "tree.h"
#include "config.h"
#include "scene.h"

#include <QPen>
#include <QGraphicsScene>

#include <iostream>

using namespace std;

extern Config config;
extern QGraphicsScene *graphicsscene;


/// Description: set intial values
/// \date    2012-01-28
Tree::Tree(QGraphicsScene *pgraphicsscene, Scene *pedscene, int pdepth, double px, double py, double pw, double ph) : Ped::Ttree(pedscene, pdepth, px, py, pw, ph) {
	graphicsscene = pgraphicsscene;
	scene = pedscene;
	QPen p = QPen(QColor(88,0,0), 1, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);
	p.setCosmetic(true);
	rect = graphicsscene->addRect(getx(), gety(), getw(), geth(), p);
	rect->setVisible(config.showTree);
	rect->setZValue(-100+getdepth());
};


/// Destructor: removes the graphics from the screen, too.
/// \date    2012-01-28
Tree::~Tree() {
	graphicsscene->removeItem(rect);	
	delete(rect);
}

/// \date    2012-02-05
int Tree::cut() {
	rect->setVisible(config.showTree);
	return Ttree::cut();	
}

/// New addChildren method. Does basically the same as the base method, but passes the graphicsscene to the children.
/// \date    2012-02-04
void Tree::addChildren() {
	tree1 = new Tree(graphicsscene, scene, getdepth()+1, getx(), gety(), 0.5f*getw(), 0.5f*geth());
	tree2 = new Tree(graphicsscene, scene, getdepth()+1, getx()+0.5f*getw(), gety(), 0.5f*getw(), 0.5f*geth());
	tree3 = new Tree(graphicsscene, scene, getdepth()+1, getx()+0.5f*getw(), gety()+0.5f*geth(), 0.5f*getw(), 0.5f*geth());
	tree4 = new Tree(graphicsscene, scene, getdepth()+1, getx(), gety()+0.5f*geth(), 0.5f*getw(), 0.5f*geth());
}

