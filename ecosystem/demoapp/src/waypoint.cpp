//
// pedsim - A microscopic pedestrian simulation system. 
// Copyright (c) 2003 - 2012 by Christian Gloor
//                              

#include "waypoint.h"
#include "config.h"

#include <QPen>
#include <QGraphicsScene>

#include <iostream>

using namespace std;

extern Config config;


/// Description: set intial values
/// \date    2012-01-07
Waypoint::Waypoint(double px, double py, double pr, QGraphicsScene *pscene) : Twaypoint(px, py, pr) {
  scene = pscene;
  ellipse = scene->addEllipse(getx()-getr(), gety()-getr(), getr()*2, getr()*2, QPen(QColor(44,0,0), 0.5, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin), QBrush(QColor(44, 0, 0)));
  norm = NULL;
  ellipse->setVisible(config.guiShowWaypoints);
};


/// \date    2012-01-07
Waypoint::Waypoint() : Twaypoint() {
};


/// returns the force into the direction of the waypoint
/// \date    2012-01-10
Ped::Tvector Waypoint::getForce(double myx, double myy, double fromx, double fromy, bool *reached) {
	ellipse->setVisible(config.guiShowWaypoints);
	return Twaypoint::getForce(myx, myy, fromx, fromy, reached);
}
