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


#include <QApplication>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QtOpenGL>
#include <QGLWidget>
#include <QGLFormat>
#include <QPen>

#include <iostream>                       // cout
#include <stdlib.h>                       // random

#include "mainwindow.h"
#include "agent.h"
#include "obstacle.h"
#include "style.h"
#include "vector.h"
#include "waypoint.h"
#include "config.h"

using namespace std;

/// this containers contain agents and obstacles
AgentContainer agent;                             
ObstacleContainer obstacle;
WaypointContainer waypoint;

Config config;

/// number of (time) steps simulated so far 
long systemtime = 0;

// start location center
#define XXX 0
#define YYY 0
#define ZZZ 0

// ----------------------------------------------------
// Name: main
// Description: - 
// Introduced: chgloor Monday, December 29, 2003 10:31:59
// Return value: 0
// ----------------------------------------------------
int main(int argc, char *argv[]) {
	cout << "simple pedestrian simulation" << endl;
	//	srandom(3);

	Q_INIT_RESOURCE(application);
	
	QApplication app(argc, argv);
	QApplication::setStyle(new Style());


	MainWindow mainwindow;
	mainwindow.show();

	QGraphicsScene *scene = new QGraphicsScene(0);

	scene->setBackgroundBrush(Qt::black);
	scene->setItemIndexMethod(QGraphicsScene::NoIndex);

	//	Twaypoint w0(0, 0, 15, scene);
	Twaypoint w1(-160, -51, 17, scene);   waypoint.push_back(w1);
	Twaypoint w11(-112, -2, 16, scene);    waypoint.push_back(w11);
	Twaypoint w2(163, -55, 16, scene);    waypoint.push_back(w2);
	Twaypoint w22(112, -2, 16, scene);     waypoint.push_back(w22);
	Twaypoint w23(165, -120, 15, scene);  waypoint.push_back(w23);
	Twaypoint w3(0, -120, 15, scene);     waypoint.push_back(w3);
	Twaypoint wstr( 12, -68, 8, scene);     waypoint.push_back(wstr);
	Twaypoint wstl(-12, -68, 8, scene);    waypoint.push_back(wstl);
	Twaypoint wsr( 17,  0, 8, scene);     waypoint.push_back(wsr);
	Twaypoint wsl(-17,  0, 8, scene);    waypoint.push_back(wsl);
	Twaypoint wst( 0, -17, 8, scene);     waypoint.push_back(wst);
	Twaypoint wsb( 0,  17, 8, scene);    waypoint.push_back(wsb);
	Twaypoint w4(0, 110, 15, scene);      waypoint.push_back(w4);
	Twaypoint wr1( 20, -142, 8, scene);      waypoint.push_back(wr1);
	Twaypoint wr2(150, -142, 8, scene);      waypoint.push_back(wr2);


	// saeulen
	obstacle.push_back(Tobstacle(-2, -50,  2, -50, scene->addLine(1,1,0,0,QPen(Qt::gray, 1, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin))));
	obstacle.push_back(Tobstacle(-2, -46,  2, -46, scene->addLine(1,1,0,0,QPen(Qt::gray, 1, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin))));
	obstacle.push_back(Tobstacle(-2, -46, -2, -50, scene->addLine(1,1,0,0,QPen(Qt::gray, 1, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin))));
	obstacle.push_back(Tobstacle( 2, -46,  2, -50, scene->addLine(1,1,0,0,QPen(Qt::gray, 1, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin))));

	obstacle.push_back(Tobstacle( 2, -70,  -2, -70, scene->addLine(1,1,0,0,QPen(Qt::gray, 1, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin))));
	obstacle.push_back(Tobstacle( 2, -66,  -2, -66, scene->addLine(1,1,0,0,QPen(Qt::gray, 1, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin))));
	obstacle.push_back(Tobstacle( 2, -66,  2, -70, scene->addLine(1,1,0,0,QPen(Qt::gray, 1, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin))));
	obstacle.push_back(Tobstacle( -2, -66,  -2, -70, scene->addLine(1,1,0,0,QPen(Qt::gray, 1, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin))));

	obstacle.push_back(Tobstacle( 2, -30, -2, -30, scene->addLine(1,1,0,0,QPen(Qt::gray, 1, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin))));
	obstacle.push_back(Tobstacle( 2, -26, -2, -26, scene->addLine(1,1,0,0,QPen(Qt::gray, 1, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin))));
	obstacle.push_back(Tobstacle( 2, -26,  2, -30, scene->addLine(1,1,0,0,QPen(Qt::gray, 1, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin))));
	obstacle.push_back(Tobstacle(-2, -26, -2, -30, scene->addLine(1,1,0,0,QPen(Qt::gray, 1, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin))));

	obstacle.push_back(Tobstacle(  0, -7, 7, 0, scene->addLine(1,1,0,0,QPen(Qt::gray, 1, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin))));
	obstacle.push_back(Tobstacle( 7,   0, 0, 7, scene->addLine(1,1,0,0,QPen(Qt::gray, 1, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin))));
	obstacle.push_back(Tobstacle(  0,  7,-7, 0, scene->addLine(1,1,0,0,QPen(Qt::gray, 1, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin))));
	obstacle.push_back(Tobstacle(-7,   0, 0,-7, scene->addLine(1,1,0,0,QPen(Qt::gray, 1, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin))));


	// walls

	// senkrecht unten
	obstacle.push_back(Tobstacle(-20, 120, -20,  25, scene->addLine(1,1,0,0,QPen(Qt::gray, 1, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin))));
	obstacle.push_back(Tobstacle( 20, 120,  20,  25, scene->addLine(1,1,0,0,QPen(Qt::gray, 1, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin))));
	obstacle.push_back(Tobstacle(-20, 120,  20, 120, scene->addLine(1,1,0,0,QPen(Qt::gray, 1, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin))));

	// senkrecht oben
	obstacle.push_back(Tobstacle(-20, -150, -20, -25, scene->addLine(1,1,0,0,QPen(Qt::gray, 1, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin))));
	obstacle.push_back(Tobstacle( 20, -135,  20, -25, scene->addLine(1,1,0,0,QPen(Qt::gray, 1, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin))));
	obstacle.push_back(Tobstacle(-20, -150, 180,-150, scene->addLine(1,1,0,0,QPen(Qt::gray, 1, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin))));

	// links 1
	obstacle.push_back(Tobstacle(-100, -15, -30, -15, scene->addLine(1,1,0,0,QPen(Qt::gray, 1, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin))));
	obstacle.push_back(Tobstacle(-120,  15, -30,  15, scene->addLine(1,1,0,0,QPen(Qt::gray, 1, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin))));
	obstacle.push_back(Tobstacle(-30, 15, -20,  25, scene->addLine(1,1,0,0,QPen(Qt::gray, 1, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin))));
	obstacle.push_back(Tobstacle(-30, -15, -20,  -25, scene->addLine(1,1,0,0,QPen(Qt::gray, 1, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin))));

	// links 2
	obstacle.push_back(Tobstacle(-150, -65, -100, -15, scene->addLine(1,1,0,0,QPen(Qt::gray, 1, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin))));
	obstacle.push_back(Tobstacle(-180, -45, -120,  15, scene->addLine(1,1,0,0,QPen(Qt::gray, 1, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin))));
	obstacle.push_back(Tobstacle(-180, -45, -150, -65, scene->addLine(1,1,0,0,QPen(Qt::gray, 1, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin))));

	// rechts 1
	obstacle.push_back(Tobstacle( 100, -15,  30, -15, scene->addLine(1,1,0,0,QPen(Qt::gray, 1, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin))));
	obstacle.push_back(Tobstacle( 120,  15,  30,  15, scene->addLine(1,1,0,0,QPen(Qt::gray, 1, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin))));
	obstacle.push_back(Tobstacle( 30, 15,  20,  25, scene->addLine(1,1,0,0,QPen(Qt::gray, 1, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin))));
	obstacle.push_back(Tobstacle( 30, -15,  20,  -25, scene->addLine(1,1,0,0,QPen(Qt::gray, 1, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin))));

	// rechts 2
	obstacle.push_back(Tobstacle( 150, -65,  100, -15, scene->addLine(1,1,0,0,QPen(Qt::gray, 1, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin))));
	obstacle.push_back(Tobstacle( 180, -45,  120,  15, scene->addLine(1,1,0,0,QPen(Qt::gray, 1, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin))));

	// bottleneck
	obstacle.push_back(Tobstacle( 180, -45,  180, -65, scene->addLine(1,1,0,0,QPen(Qt::gray, 1, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin))));
	obstacle.push_back(Tobstacle( 180, -65,  170, -85, scene->addLine(1,1,0,0,QPen(Qt::gray, 1, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin))));
	obstacle.push_back(Tobstacle( 150, -65,  160, -85, scene->addLine(1,1,0,0,QPen(Qt::gray, 1, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin))));
	obstacle.push_back(Tobstacle( 180,-100,  170, -85, scene->addLine(1,1,0,0,QPen(Qt::gray, 1, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin))));
	obstacle.push_back(Tobstacle( 150,-100,  160, -85, scene->addLine(1,1,0,0,QPen(Qt::gray, 1, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin))));

	obstacle.push_back(Tobstacle( 150,-100,  150,-135, scene->addLine(1,1,0,0,QPen(Qt::gray, 1, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin))));
	obstacle.push_back(Tobstacle( 180,-100,  180,-150, scene->addLine(1,1,0,0,QPen(Qt::gray, 1, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin))));
	//	obstacle.push_back(Tobstacle( 150,-150,  180,-150, scene->addLine(1,1,0,0,QPen(Qt::gray, 1, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin))));

	// ramp
	obstacle.push_back(Tobstacle( 150,-135,  20,-135, scene->addLine(1,1,0,0,QPen(Qt::gray, 1, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin))));
  
	for (int i = 0; i<100; i++) { 
		Tagent a(scene);

		if ((i > 0) && (i <= 4)) {
			a.setFollow(i-1);
			a.setVmax(2.2); 
		} else if (i == 0) {
			a.setVmax(2.2); 
		} else {
		}

		if (i%2 == 0) a.setPosition( XXX +  qrand()/(RAND_MAX/80) -100, YYY + qrand()/(RAND_MAX/20) -10, ZZZ);
		if (i%2 == 1) a.setPosition( XXX +  qrand()/(RAND_MAX/80) +20, YYY + qrand()/(RAND_MAX/20) -10, ZZZ);

		a.destinations.enqueue(w11);
		a.destinations.enqueue(w1);
		a.destinations.enqueue(w11);

		if (i%2 == 0) { a.destinations.enqueue(wsb); } else {a.destinations.enqueue(wst); }

		a.destinations.enqueue(w22);
		a.destinations.enqueue(w2);
		a.destinations.enqueue(w23);

		a.destinations.enqueue(wr2);
		a.destinations.enqueue(wr1);

		a.destinations.enqueue(w3);
		if (i%2 == 0) { a.destinations.enqueue(wstr); } else {a.destinations.enqueue(wstl); }
		if (i%2 == 0) { a.destinations.enqueue(wsr); } else {a.destinations.enqueue(wsl); }
		a.destinations.enqueue(w4);
		if (i%2 == 0) { a.destinations.enqueue(wsr); } else {a.destinations.enqueue(wsl); }
		if (i%2 == 0) { a.destinations.enqueue(wstr); } else {a.destinations.enqueue(wstl); }
		a.destinations.enqueue(w3);

		a.destinations.enqueue(wr1);
		a.destinations.enqueue(wr2);

		a.destinations.enqueue(w23);
		a.destinations.enqueue(w2);
		a.destinations.enqueue(w22);

		if (i%2 == 0) { a.destinations.enqueue(wsb); } else {a.destinations.enqueue(wst); }
		
		agent.push_back(a);
	}

	mainwindow.graphicsView->setScene(scene);
	mainwindow.graphicsView->setViewport(new QGLWidget(QGLFormat(QGL::SampleBuffers)));
	mainwindow.graphicsView->setViewportUpdateMode(QGraphicsView::MinimalViewportUpdate);
	mainwindow.graphicsView->setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);	
	mainwindow.graphicsView->show();

	return app.exec();
}




