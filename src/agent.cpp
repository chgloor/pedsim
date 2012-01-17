//
// pedsim - A microscopic pedestrian simulation system. 
// Copyright (c) 2003 - 2004 by Christian Gloor
//                              


#include "math.h"

#include "ped_vector.h"

#include "agent.h"

#include "obstacle.h"
#include "config.h"

#include <iostream>

#include <QPen>
#include <QGraphicsScene>


using namespace std;

// ----------------------------------------------------
// Name: constructor
//!Description: set intial values
//!Introduced: chgloor Monday, December 29, 2003 11:10:37
// ----------------------------------------------------
Agent::Agent(QGraphicsScene *pscene) : Tagent() {
  scene = pscene;
  rect = scene->addRect(QRectF(0,0,1,1), QPen(Qt::darkGreen, 0.1, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin), QBrush(QColor(Qt::darkGreen)));	
  lineea = scene->addLine(QLineF(0, 0, 1, 1), QPen(Qt::red, 0.1, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));	
  lineoa = scene->addLine(QLineF(0, 0, 1, 1), QPen(Qt::blue, 0.1, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));	
  linesa = scene->addLine(QLineF(0, 0, 1, 1), QPen(Qt::green, 0.1, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));	
  linelfa = scene->addLine(QLineF(0, 0, 1, 1), QPen(Qt::magenta, 0.1, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));	
  linev  = scene->addLine(QLineF(0, 0, 1, 1), QPen(Qt::yellow, 0.1, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));	
};




// ----------------------------------------------------
// Name: move
//!Description: does the agent dynamics stuff 
//!Introduced: chgloor Monday, December 29, 2003 11:10:58
//!Return value: void
// ----------------------------------------------------
void Agent::move() {

	//
	//  G R A P H I C   S C E N E   U P D A T E
	//
	Tagent::move();

	rect->setPos(getx()-0.5, gety()-0.5); // upper left edge

	/*	if (config.showDirection == true) {
		linev->setLine(x, y, x+2*vx, y+2*vy);
		linev->setVisible(true);
	} else { linev->setVisible(false); }
	if (config.showForces == true) {
		lineea->setLine(x, y, x+2*eax, y+2*eay);
		lineea->setVisible(true);
		linesa->setLine(x, y, x+2*sax, y+2*say);
		linesa->setVisible(true);
		lineoa->setLine(x, y, x+2*oax, y+2*oay);
		lineoa->setVisible(true);
		linelfa->setLine(x, y, x+2*lfax, y+2*lfay);
		linelfa->setVisible(true);
	} else {
		lineea->setVisible(false);
		linesa->setVisible(false);
		lineoa->setVisible(false);
		linelfa->setVisible(false);
		}*/
}

