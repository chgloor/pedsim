//
// pedsim - A microscopic pedestrian simulation system. 
// Copyright (c) 2003 - 2004 by Christian Gloor
//                              

#ifndef _agent_h_
#define _agent_h_ 1

#include <QGraphicsItem>
#include <QQueue>

#include <iostream>
#include <vector>

#include "waypoint.h"

#include "ped_agent.h"

using namespace std;

// ----------------------------------------------------
// Name: Tagent
//!Description: Class that descripts an agent object
//!Introduced: chgloor Dec 26, 2003
// ----------------------------------------------------
class Agent : public Tagent {
 private:
 public:
  Agent(QGraphicsScene *pscene);

  void move();

  QGraphicsScene *scene;
  QGraphicsRectItem *rect;  
  QGraphicsLineItem *linev;  
  QGraphicsLineItem *lineea;  
  QGraphicsLineItem *lineoa;  
  QGraphicsLineItem *linesa;  
  QGraphicsLineItem *linelfa;  

};



#endif
