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

//#include <vector>

#include "mainwindow.h"
#include "agent.h"
#include "obstacle.h"
#include "style.h"
#include "vector.h"
#include "waypoint.h"
#include "config.h"

#include "main.h"

using namespace std;


//#define VERSION_M "2"
//#define VERSION_A "pre"

/// this containers contain agents and obstacles
AgentContainer agent;                             
ObstacleContainer obstacle;
WaypointContainer waypoint;

Config config;

/// number of (time) steps simulated so far 
long systemtime = 0;
/// stream object used to send events over the network

//Tevent *event;

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
	Twaypoint w23(165, -140, 15, scene);  waypoint.push_back(w23);
	Twaypoint w3(0, -140, 15, scene);     waypoint.push_back(w3);
	Twaypoint wsr(10, -38, 8, scene);     waypoint.push_back(wsr);
	Twaypoint wsl(-10, -38, 8, scene);    waypoint.push_back(wsl);
	Twaypoint w4(0, 118, 15, scene);      waypoint.push_back(w4);


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
	obstacle.push_back(Tobstacle( 180, -65,  172, -85, scene->addLine(1,1,0,0,QPen(Qt::gray, 1, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin))));
	obstacle.push_back(Tobstacle( 150, -65,  158, -85, scene->addLine(1,1,0,0,QPen(Qt::gray, 1, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin))));
	obstacle.push_back(Tobstacle( 180,-100,  172, -85, scene->addLine(1,1,0,0,QPen(Qt::gray, 1, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin))));
	obstacle.push_back(Tobstacle( 150,-100,  158, -85, scene->addLine(1,1,0,0,QPen(Qt::gray, 1, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin))));

	obstacle.push_back(Tobstacle( 150,-100,  150,-135, scene->addLine(1,1,0,0,QPen(Qt::gray, 1, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin))));
	obstacle.push_back(Tobstacle( 180,-100,  180,-150, scene->addLine(1,1,0,0,QPen(Qt::gray, 1, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin))));
	//	obstacle.push_back(Tobstacle( 150,-150,  180,-150, scene->addLine(1,1,0,0,QPen(Qt::gray, 1, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin))));

	// ramp
	obstacle.push_back(Tobstacle( 150,-135,  20,-135, scene->addLine(1,1,0,0,QPen(Qt::gray, 1, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin))));
  

	// Tobstacle o2;
	// o2.line = scene->addLine(0,0,1,1, QPen(Qt::gray, 1, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
	// o2.setPosition(-50, 10, -5, 25);
	// obstacle.push_back(o2);

	for (int i = 0; i<100; i++) { 
		Tagent a;
		
		if (i < 4) {
			a.setFollow(10);
			a.setVmax(2); 
			a.rect = scene->addRect(QRectF(0, 0, 1, 1), QPen(Qt::red, 1, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));	
		} else if (i == 10) {
			a.setVmax(1.8); 
			a.rect = scene->addRect(QRectF(0, 0, 1, 1), QPen(Qt::yellow, 1, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));	
		} else {
			a.rect = scene->addRect(QRectF(0, 0, 1, 1), QPen(Qt::green, 1, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));	
		}
		a.setPosition( XXX +  qrand()/(RAND_MAX/50) -100, YYY + qrand()/(RAND_MAX/10) -5, ZZZ);
		
		a.destinations.enqueue(w11);
		a.destinations.enqueue(w1);
		a.destinations.enqueue(w11);
		a.destinations.enqueue(w22);
		a.destinations.enqueue(w2);
		a.destinations.enqueue(w23);

		a.destinations.enqueue(w3);
		a.destinations.enqueue(wsr);
		a.destinations.enqueue(w4);
		a.destinations.enqueue(wsl);
		a.destinations.enqueue(w3);

		a.destinations.enqueue(w23);
		a.destinations.enqueue(w2);
		a.destinations.enqueue(w22);
		

		agent.push_back(a);
	}
	
	mainwindow.graphicsView->setScene(scene);
	mainwindow.graphicsView->setViewport(new QGLWidget(QGLFormat(QGL::SampleBuffers)));

	return app.exec();
}




