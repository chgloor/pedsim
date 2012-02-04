//
// pedsim - A microscopic pedestrian simulation system. 
// Copyright (c) 2003 - 2004 by Christian Gloor
//                              

#include "scene.h"
#include "config.h"
#include "tree.h"

#include "ped_agent.h"

#include <QTimer>

#include <iostream>
#include <stack>

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


/// 
/// \date    2012-01-28
Scene::Scene() : Tscene() {
};


/// 
/// \date    2012-02-04
/// \return  
/// \warning 
/// \param   
void Scene::moveAllAgents() {
	moveAgents(config.simh);
	movetimer->setInterval(config.simSpeed);
}

/// 
/// \author  chgloor
/// \date    2012-02-04
/// \return  
/// \warning 
/// \param   
void Scene::cleanupSlot() {
	cleanup();
}
