//
// pedsim - A microscopic pedestrian simulation system. 
// Copyright (c) 2003 - 2012 by Christian Gloor
//                              

#include "scene.h"
#include "config.h"
#include "tree.h"

#include <QTimer>

#include <iostream>

using namespace std;

extern Config config;


/// Description: set intial values
/// \date    2012-01-28
Scene::Scene(QGraphicsScene *pscene)  {
  scene = pscene;
  tree = new Tree(pscene, this, 0, -200, -160, 400, 320);

  movetimer = new QTimer();
  QObject::connect(movetimer, SIGNAL(timeout()), this, SLOT(moveAllAgents()));
  movetimer->start(1000/20);

  cleanuptimer = new QTimer();
  QObject::connect(cleanuptimer, SIGNAL(timeout()), this, SLOT(cleanupSlot()));
  cleanuptimer->start(1000);
  
};


/// \date    2012-01-28
Scene::Scene() : Tscene() {
};


/// \date    2012-02-04
void Scene::moveAllAgents() {
	moveAgents(config.simh);
	movetimer->setInterval(config.simSpeed);
}


/// \date    2012-02-04
void Scene::cleanupSlot() {
	cleanup();
}
