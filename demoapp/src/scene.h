//
// pedsim - A microscopic pedestrian simulation system. 
// Copyright (c) 2003 - 2012 by Christian Gloor
//                              

#ifndef _scene_h_
#define _scene_h_ 1

#include <QGraphicsItem>
#include <QQueue>
#include <map>
#include <set>

#include <iostream>

#include "ped_scene.h"
#include "ped_agent.h"

#include "tree.h"

class Tagent;

using namespace std;

/// Class that descripts an scene object
/// \author  chgloor
/// \date    2012-01-28
class Scene : public Ped::Tscene {
 private:
  QGraphicsScene *scene;
    
 public:
  Scene();
  Scene(QGraphicsScene *scene);

  /* void virtual addAgent(Ped::Tagent *a); */
  /* void placeAgent(Ped::Tagent *a); */
  /* void moveAgent(Ped::Tagent *a); */
  
  /* set<Ped::Tagent*> getNeighbors(double x, double y, double dist); */
  /* map<Ped::Tagent*, Tree*> treehash; */

  /* void cleanup(); */

};

#endif
