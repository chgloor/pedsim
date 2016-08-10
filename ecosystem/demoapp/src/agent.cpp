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

extern Config config;
extern Scene *gblscene;

using namespace std;

/// Agent Constructor
/// \date    2012-01-17
Agent::Agent(QGraphicsScene *pscene) : Tagent() {
    graphicsscene = pscene;
    rect = graphicsscene->addRect(QRectF(0,0,1,1), QPen(Qt::white, 0.1, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin), QBrush(QColor(Qt::white)));
    lineea = graphicsscene->addLine(QLineF(0, 0, 1, 1), QPen(Qt::gray, 0.1, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
    lineoa = graphicsscene->addLine(QLineF(0, 0, -1, 1), QPen(Qt::blue, 0.1, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
    linesa = graphicsscene->addLine(QLineF(0, 0, 1, 1), QPen(Qt::red, 0.1, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
    linelfa = graphicsscene->addLine(QLineF(0, 0, 1, 1), QPen(Qt::green, 0.1, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
    linev  = graphicsscene->addLine(QLineF(0, 0, 1, 1), QPen(Qt::yellow, 0.1, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
};


/// Calculates the social force. Same as in lib, but adds graphical representation
/// \date    2012-01-17
Ped::Tvector Agent::socialForce(const set<const Ped::Tagent*> &neighbors) {
    Ped::Tvector t = Tagent::socialForce(neighbors);
    if (config.showForces == true) {
        linesa->setLine(p.x, p.y, p.x + 3.0 * t.x, p.y + 3.0 * t.y);
        linesa->setVisible(true);
    } else {
        linesa->setVisible(false);
    }
    return t;
}


/// Calculates the obstacle force. Same as in lib, but adds graphical representation
/// \date    2012-01-17
Ped::Tvector Agent::obstacleForce(const set<const Ped::Tagent*> &neighbors) {
    Ped::Tvector t = Tagent::obstacleForce(neighbors);
    if (config.showForces == true) {
        lineoa->setLine(p.x, p.y, p.x + 10.0 * t.x, p.y + 10.0 * t.y);
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
        lineea->setLine(p.x, p.y, p.x + 1.0 * t.x, p.y + 1.0 * t.y);
        lineea->setVisible(true);
    } else {
        lineea->setVisible(false);
    }
    return t;
}


/// Calculates the look ahead force. Same as in lib, but adds graphical representation
/// \date    2012-01-17
Ped::Tvector Agent::lookaheadForce(Ped::Tvector desired, const set<const Ped::Tagent*> &neighbors) {
    Ped::Tvector t;
    if (config.mlLookAhead == true) {
      t = Tagent::lookaheadForce(desired, neighbors);
    }
    if (config.showForces == true) {
        linelfa->setLine(p.x, p.y, p.x + 1.0 * t.x, p.y + 1.0 * t.y);
        linelfa->setVisible(true);
    } else {
        linelfa->setVisible(false);
    }
    return t;
}


/// Calculates the custom force
/// \date    2012-02-12
Ped::Tvector Agent::myForce(Ped::Tvector desired, const set<const Ped::Tagent*> &neighbors) {
    Ped::Tvector t;
    if (config.mlTendency) {
        t.x = 0.5 * desired.y;
        t.y = -0.5 * desired.x;
    }
    return t;
}


/// move - calls the lib move and updates the graphics then
/// \date    2012-01-17
void Agent::move(double h) {
    setfactorsocialforce(config.simPedForce);
    setfactorobstacleforce(config.simWallForce);

    //    setVmax(gblscene->getGridValue(getx(), gety(), 0));

    Tagent::move(h);

    rect->setPos(p.x - 0.5, p.y - 0.5); // upper left edge
    if (config.showDirection == true) {
        linev->setLine(p.x, p.y, p.x + 1.0 * v.x, p.y + 1.0 * v.y);
        linev->setVisible(true);
    } else {
        linev->setVisible(false);
    }

    // update graphic center if option selected
    if ((config.followAgent == true) && (id == 0)) {
        graphicsscene->views().first()->centerOn(p.x, p.y);
    }
}
