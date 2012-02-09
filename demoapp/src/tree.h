//
// pedsim - A microscopic pedestrian simulation system. 
// Copyright (c) 2003 - 2012 by Christian Gloor
//                              

#ifndef _tree_h_
#define _tree_h_ 1

#include <QGraphicsItem>
#include <QQueue>

#include <iostream>
#include <set>

#include "ped_tree.h"

class Scene;

using namespace std;


class Tree : public Ped::Ttree {
 private:
  QGraphicsScene *graphicsscene;
  QGraphicsRectItem *rect;
  Scene *scene;
  
 public:
  
  Tree(QGraphicsScene *graphicsscene, Scene *pedscene, int depth, double x, double y, double w, double h);  
  virtual ~Tree();

  virtual void addChildren();

  int cut();
};

#endif
