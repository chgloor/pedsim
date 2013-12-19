//
// pedsim - A microscopic pedestrian simulation system.
// Copyright (c) 2003 - 2012 by Christian Gloor
//


#include "agent.h"
#include "obstacle.h"
#include "config.h"
#include "scene.h"

#include <QPen>
#include <QGraphicsScene>
#include <QGraphicsView>

#include <iostream>

extern Config config;
extern Scene *gblscene;

using namespace std;

/// Agent Constructor
/// \date    2012-01-17
Agent::Agent(QGraphicsScene *pscene) : Tagent() {
    graphicsscene = pscene;
    rect = graphicsscene->addRect(QRectF(0,0,1,1), QPen(Qt::white, 0.1, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin), QBrush(QColor(Qt::white)));
    lineea = graphicsscene->addLine(QLineF(0, 0, 1, 1), QPen(Qt::red, 0.1, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
    lineoa = graphicsscene->addLine(QLineF(0, 0, 1, 1), QPen(Qt::blue, 0.1, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
    linesa = graphicsscene->addLine(QLineF(0, 0, 1, 1), QPen(Qt::green, 0.1, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
    linelfa = graphicsscene->addLine(QLineF(0, 0, 1, 1), QPen(Qt::magenta, 0.1, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
    linev  = graphicsscene->addLine(QLineF(0, 0, 1, 1), QPen(Qt::yellow, 0.1, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
};


/// Calculates the social force. Same as in lib, but adds graphical representation
/// \date    2012-01-17
Ped::Tvector Agent::socialForce() {
    Ped::Tvector t = Tagent::socialForce();
    if (config.showForces == true) {
        linesa->setLine(getx(), gety(), getx()+config.simPedForce*t.x, gety()+config.simPedForce*t.y);
        linesa->setVisible(true);
    } else {
        linesa->setVisible(false);
    }
    return t;
}


/// Calculates the obstacle force. Same as in lib, but adds graphical representation
/// \date    2012-01-17
Ped::Tvector Agent::obstacleForce() {
    Ped::Tvector t = Tagent::obstacleForce();
    if (config.showForces == true) {
        lineoa->setLine(getx(), gety(), getx()+config.simWallForce*t.x, gety()+config.simWallForce*t.y);
        lineoa->setVisible(true);
    } else {
        lineoa->setVisible(false);
    }
    return t;
}

/// Calculates the desired force. Same as in lib, but adds graphical representation
/// \author  chgloor
Ped::Tvector Agent::desiredForce() {
    Ped::Tvector t = Tagent::desiredForce();
    if (config.showForces == true) {
        lineea->setLine(getx(), gety(), getx()+1.0f*t.x, gety()+1.0*t.y);
        lineea->setVisible(true);
    } else {
        lineea->setVisible(false);
    }
    return t;
}

/// Calculates the look ahead force. Same as in lib, but adds graphical representation
/// \date    2012-01-17
Ped::Tvector Agent::lookaheadForce(Ped::Tvector desired) {
    Ped::Tvector t;
    if (config.mlLookAhead == true) {
        t = Tagent::lookaheadForce(desired);
    }
    if (config.showForces == true) {
        linelfa->setLine(getx(), gety(), getx()+1.0f*t.x, gety()+1.0*t.y);
        linelfa->setVisible(true);
    } else {
        linelfa->setVisible(false);
    }
    return t;
}

/// Calculates the custom force
/// \date    2012-02-12
Ped::Tvector Agent::myForce(Ped::Tvector desired) {
    Ped::Tvector t;
    if (config.mlTendency) {
        t.x = 0.5*desired.y;
        t.y = -0.5*desired.x;
    }
    return t;
}


/// move - calls the lib move and updates the graphics then
/// \date    2012-01-17
void Agent::move(double h) {
    setfactorsocialforce(config.simPedForce);
    setfactorobstacleforce(config.simWallForce);

    setVmax(gblscene->getGridValue(getx(), gety(), 0));

    Tagent::move(h);

    rect->setPos(getx()-0.5, gety()-0.5); // upper left edge
    if (config.showDirection == true) {
        linev->setLine(getx(), gety(), getx()+1.0*getvx(), gety()+1.0*getvy());
        linev->setVisible(true);
    } else {
        linev->setVisible(false);
    }

    if ((config.followAgent == true) && (id == 0)) {
        graphicsscene->views().first()->centerOn(getx(), gety());
    }
}
