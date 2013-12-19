//
// pedsim - A microscopic pedestrian simulation system.
// Copyright (c) 2003 - 2012 by Christian Gloor
//

#ifndef _agent_h_
#define _agent_h_ 1

#include <QGraphicsItem>

#include "ped_agent.h"
#include "ped_vector.h"

using namespace std;

/// Class that describes an agent object
/// \author  chgloor
/// \date    2003-12-26
class Agent : public Ped::Tagent {
private:
public:
    Agent(QGraphicsScene *scene);

    void move(double h);
    Ped::Tvector socialForce();
    Ped::Tvector obstacleForce();
    Ped::Tvector desiredForce();
    Ped::Tvector lookaheadForce(Ped::Tvector desired);
    Ped::Tvector myForce(Ped::Tvector desired);

    QGraphicsScene *graphicsscene;
    QGraphicsRectItem *rect;
    QGraphicsLineItem *linev;
    QGraphicsLineItem *lineea;
    QGraphicsLineItem *lineoa;
    QGraphicsLineItem *linesa;
    QGraphicsLineItem *linelfa;
};

#endif
