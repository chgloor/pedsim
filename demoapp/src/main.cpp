///
/// pedsim - A microscopic pedestrian simulation system. 
/// Copyright (c) 2003 - 2012 by Christian Gloor
///                              
///
///       _
///   _  (__/   _ _ _   /    _ / _ ' __/'_    _ /    _ 
/// _) ()/ /((/(// (-  ()(/ ( /)/ /_) //(//) (/(()()/  
///                      /                  _/         
///

// ---> export LD_LIBRARY_PATH=libpedsim

#include <QApplication>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QtOpenGL>
#include <QGLWidget>
#include <QGLFormat>
#include <QPen>

#include <iostream>                       // cout
#include <stdlib.h>                       // random

#include "pedsim.h"

#include "mainwindow.h"
#include "agent.h"
#include "obstacle.h"
#include "style.h"
#include "waypoint.h"
#include "scene.h"
#include "config.h"

using namespace std;

vector<Agent*> myagents;
Scene *pedscene;

Config config;

/// number of (time) steps simulated so far 
long systemtime = 0;

// start location center
#define XXX 0
#define YYY 0
#define ZZZ 0

Obstacle *doorobstacle1;
Obstacle *doorobstacle2;

// ----------------------------------------------------
// Name: main
// Description: - 
// Introduced: chgloor Monday, December 29, 2003 10:31:59
// Return value: 0
// ----------------------------------------------------
int main(int argc, char *argv[]) {

	int nagents = 100;
	QString s = argv[1];
	if (s != "") {
		nagents  = s.toInt();
	}

	Q_INIT_RESOURCE(application);
	
	QApplication app(argc, argv);
	QApplication::setStyle(new Style());

	MainWindow mainwindow;
	mainwindow.show();

QGraphicsScene *graphicsscene = new QGraphicsScene(0);

	graphicsscene->setBackgroundBrush(Qt::black);
		graphicsscene->setItemIndexMethod(QGraphicsScene::NoIndex);

	pedscene = new Scene(graphicsscene);


	Waypoint w1(-160, -51, 17, graphicsscene);
	Waypoint w11(-112, -2, 16, graphicsscene);
	Waypoint w2(163, -55, 16, graphicsscene); 
	Waypoint w22(112, -2, 16, graphicsscene); 
	Waypoint w23(165, -120, 15, graphicsscene);
	Waypoint w3(0, -120, 15, graphicsscene);   
	Waypoint wstr( 12, -68, 8, graphicsscene); 
	Waypoint wstl(-12, -68, 8, graphicsscene); 
	Waypoint wsr( 17,  0, 8, graphicsscene);   
	Waypoint wsl(-17,  0, 8, graphicsscene);   
	Waypoint wst( 0, -17, 8, graphicsscene);   
	Waypoint wsb( 0,  17, 8, graphicsscene);   
	Waypoint w4(0, 110, 15, graphicsscene);    
	Waypoint wr1( 20, -142, 8, graphicsscene); 
	Waypoint wr2(150, -142, 8, graphicsscene); 


	// saeulen
	pedscene->addObstacle(new Obstacle(-2, -50,  2, -50, graphicsscene->addLine(1,1,0,0,QPen(Qt::gray, 1, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin))));
	pedscene->addObstacle(new Obstacle(-2, -46,  2, -46, graphicsscene->addLine(1,1,0,0,QPen(Qt::gray, 1, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin))));
	pedscene->addObstacle(new Obstacle(-2, -46, -2, -50, graphicsscene->addLine(1,1,0,0,QPen(Qt::gray, 1, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin))));
	pedscene->addObstacle(new Obstacle( 2, -46,  2, -50, graphicsscene->addLine(1,1,0,0,QPen(Qt::gray, 1, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin))));

	pedscene->addObstacle(new Obstacle( 2, -70,  -2, -70, graphicsscene->addLine(1,1,0,0,QPen(Qt::gray, 1, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin))));
	pedscene->addObstacle(new Obstacle( 2, -66,  -2, -66, graphicsscene->addLine(1,1,0,0,QPen(Qt::gray, 1, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin))));
	pedscene->addObstacle(new Obstacle( 2, -66,  2, -70, graphicsscene->addLine(1,1,0,0,QPen(Qt::gray, 1, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin))));
	pedscene->addObstacle(new Obstacle( -2, -66,  -2, -70, graphicsscene->addLine(1,1,0,0,QPen(Qt::gray, 1, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin))));

	pedscene->addObstacle(new Obstacle( 2, -30, -2, -30, graphicsscene->addLine(1,1,0,0,QPen(Qt::gray, 1, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin))));
	pedscene->addObstacle(new Obstacle( 2, -26, -2, -26, graphicsscene->addLine(1,1,0,0,QPen(Qt::gray, 1, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin))));
	pedscene->addObstacle(new Obstacle( 2, -26,  2, -30, graphicsscene->addLine(1,1,0,0,QPen(Qt::gray, 1, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin))));
	pedscene->addObstacle(new Obstacle(-2, -26, -2, -30, graphicsscene->addLine(1,1,0,0,QPen(Qt::gray, 1, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin))));

	pedscene->addObstacle(new Obstacle(  0, -7, 7, 0, graphicsscene->addLine(1,1,0,0,QPen(Qt::gray, 1, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin))));
	pedscene->addObstacle(new Obstacle( 7,   0, 0, 7, graphicsscene->addLine(1,1,0,0,QPen(Qt::gray, 1, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin))));
	pedscene->addObstacle(new Obstacle(  0,  7,-7, 0, graphicsscene->addLine(1,1,0,0,QPen(Qt::gray, 1, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin))));
	pedscene->addObstacle(new Obstacle(-7,   0, 0,-7, graphicsscene->addLine(1,1,0,0,QPen(Qt::gray, 1, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin))));


	// walls

	// senkrecht unten
	pedscene->addObstacle(new Obstacle(-20, 120, -20,  25, graphicsscene->addLine(1,1,0,0,QPen(Qt::gray, 1, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin))));
	pedscene->addObstacle(new Obstacle( 20, 120,  20,  25, graphicsscene->addLine(1,1,0,0,QPen(Qt::gray, 1, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin))));
	pedscene->addObstacle(new Obstacle(-20, 120,  20, 120, graphicsscene->addLine(1,1,0,0,QPen(Qt::gray, 1, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin))));

	// senkrecht oben
	pedscene->addObstacle(new Obstacle(-20, -150, -20, -25, graphicsscene->addLine(1,1,0,0,QPen(Qt::gray, 1, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin))));
	pedscene->addObstacle(new Obstacle( 20, -135,  20, -25, graphicsscene->addLine(1,1,0,0,QPen(Qt::gray, 1, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin))));
	pedscene->addObstacle(new Obstacle(-20, -150, 180,-150, graphicsscene->addLine(1,1,0,0,QPen(Qt::gray, 1, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin))));

	// links 1
	pedscene->addObstacle(new Obstacle(-100, -15, -30, -15, graphicsscene->addLine(1,1,0,0,QPen(Qt::gray, 1, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin))));
	pedscene->addObstacle(new Obstacle(-120,  15, -30,  15, graphicsscene->addLine(1,1,0,0,QPen(Qt::gray, 1, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin))));
	pedscene->addObstacle(new Obstacle(-30, 15, -20,  25, graphicsscene->addLine(1,1,0,0,QPen(Qt::gray, 1, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin))));
	pedscene->addObstacle(new Obstacle(-30, -15, -20,  -25, graphicsscene->addLine(1,1,0,0,QPen(Qt::gray, 1, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin))));

	// links 2
	pedscene->addObstacle(new Obstacle(-150, -65, -100, -15, graphicsscene->addLine(1,1,0,0,QPen(Qt::gray, 1, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin))));
	pedscene->addObstacle(new Obstacle(-180, -45, -120,  15, graphicsscene->addLine(1,1,0,0,QPen(Qt::gray, 1, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin))));
	pedscene->addObstacle(new Obstacle(-180, -45, -150, -65, graphicsscene->addLine(1,1,0,0,QPen(Qt::gray, 1, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin))));

	// rechts 1
	pedscene->addObstacle(new Obstacle( 100, -15,  30, -15, graphicsscene->addLine(1,1,0,0,QPen(Qt::gray, 1, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin))));
	pedscene->addObstacle(new Obstacle( 120,  15,  30,  15, graphicsscene->addLine(1,1,0,0,QPen(Qt::gray, 1, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin))));
	pedscene->addObstacle(new Obstacle( 30, 15,  20,  25, graphicsscene->addLine(1,1,0,0,QPen(Qt::gray, 1, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin))));
	pedscene->addObstacle(new Obstacle( 30, -15,  20,  -25, graphicsscene->addLine(1,1,0,0,QPen(Qt::gray, 1, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin))));

	// rechts 2
	pedscene->addObstacle(new Obstacle( 150, -65,  100, -15, graphicsscene->addLine(1,1,0,0,QPen(Qt::gray, 1, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin))));
	pedscene->addObstacle(new Obstacle( 180, -45,  120,  15, graphicsscene->addLine(1,1,0,0,QPen(Qt::gray, 1, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin))));

	// bottleneck
	pedscene->addObstacle(new Obstacle( 180, -45,  180, -65, graphicsscene->addLine(1,1,0,0,QPen(Qt::gray, 1, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin))));
	pedscene->addObstacle(new Obstacle( 180, -65,  170, -85, graphicsscene->addLine(1,1,0,0,QPen(Qt::gray, 1, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin))));
	pedscene->addObstacle(new Obstacle( 150, -65,  160, -85, graphicsscene->addLine(1,1,0,0,QPen(Qt::gray, 1, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin))));
	pedscene->addObstacle(new Obstacle( 180,-100,  170, -85, graphicsscene->addLine(1,1,0,0,QPen(Qt::gray, 1, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin))));
	pedscene->addObstacle(new Obstacle( 150,-100,  160, -85, graphicsscene->addLine(1,1,0,0,QPen(Qt::gray, 1, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin))));

	pedscene->addObstacle(new Obstacle( 150,-100,  150,-135, graphicsscene->addLine(1,1,0,0,QPen(Qt::gray, 1, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin))));
	pedscene->addObstacle(new Obstacle( 180,-100,  180,-150, graphicsscene->addLine(1,1,0,0,QPen(Qt::gray, 1, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin))));
	//	pedscene->addObstacle(new Obstacle( 150,-150,  180,-150, graphicsscene->addLine(1,1,0,0,QPen(Qt::gray, 1, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin))));

	// ramp
	pedscene->addObstacle(new Obstacle( 150,-135,  20,-135, graphicsscene->addLine(1,1,0,0,QPen(Qt::gray, 1, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin))));

	// gate
	doorobstacle1 = new Obstacle( 80, 10, 80, -10, graphicsscene->addLine(1,1,0,0,QPen(Qt::darkGray, 1, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin)));
	pedscene->addObstacle(doorobstacle1);
	doorobstacle2 = new Obstacle( 80-10, 0, 80+10, 00, graphicsscene->addLine(1,1,0,0,QPen(Qt::darkGray, 1, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin)));
	pedscene->addObstacle(doorobstacle2);
	pedscene->addObstacle(new Obstacle( 77, -15,  80, -10, graphicsscene->addLine(1,1,0,0,QPen(Qt::darkGray, 1, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin))));
	pedscene->addObstacle(new Obstacle( 83, -15,  80, -10, graphicsscene->addLine(1,1,0,0,QPen(Qt::darkGray, 1, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin))));
	pedscene->addObstacle(new Obstacle( 77,  15,  80, 10, graphicsscene->addLine(1,1,0,0,QPen(Qt::darkGray, 1, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin))));
	pedscene->addObstacle(new Obstacle( 83,  15,  80, 10, graphicsscene->addLine(1,1,0,0,QPen(Qt::darkGray, 1, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin))));


	for (int i = 0; i<nagents; i++) { 
		Agent *a = new Agent(graphicsscene);

		if ((i > 0) && (i <= 4)) {
			a->setFollow(i-1);
			a->setVmax(2.2); 
		} else if (i == 0) {
			a->setVmax(2.2); 
		}

		if (i%2 == 0) a->setPosition( XXX +  qrand()/(RAND_MAX/80) -100, YYY + qrand()/(RAND_MAX/20) -10, ZZZ);
		if (i%2 == 1) a->setPosition( XXX +  qrand()/(RAND_MAX/80) +20, YYY + qrand()/(RAND_MAX/20) -10, ZZZ);

		a->addWaypoint(&w11);
		a->addWaypoint(&w1);
		a->addWaypoint(&w11);
		if (i%2 == 0) { a->addWaypoint(&wsb); } else {a->addWaypoint(&wst); }
		a->addWaypoint(&w22);
		a->addWaypoint(&w2);
		a->addWaypoint(&w23);
		a->addWaypoint(&wr2);
		a->addWaypoint(&wr1);
		a->addWaypoint(&w3);
		if (i%2 == 0) { a->addWaypoint(&wstr); } else {a->addWaypoint(&wstl); }
		if (i%2 == 0) { a->addWaypoint(&wsr); } else {a->addWaypoint(&wsl); }
		a->addWaypoint(&w4);
		if (i%2 == 0) { a->addWaypoint(&wsr); } else {a->addWaypoint(&wsl); }
		if (i%2 == 0) { a->addWaypoint(&wstr); } else {a->addWaypoint(&wstl); }
		a->addWaypoint(&w3);
		a->addWaypoint(&wr1);
		a->addWaypoint(&wr2);
		a->addWaypoint(&w23);
		a->addWaypoint(&w2);
		a->addWaypoint(&w22);

		if (i%2 == 0) { a->addWaypoint(&wsb); } else {a->addWaypoint(&wst); }
		
		pedscene->addAgent(a);
		myagents.push_back(a);
	}

	mainwindow.graphicsView->setScene(graphicsscene);
	mainwindow.graphicsView->setViewport(new QGLWidget(QGLFormat(QGL::SampleBuffers)));
	mainwindow.graphicsView->setViewportUpdateMode(QGraphicsView::MinimalViewportUpdate);
	mainwindow.graphicsView->setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);	
	mainwindow.graphicsView->show();

	return app.exec();
}




