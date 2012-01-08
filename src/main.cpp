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

#include "main.h"

using namespace std;


//#define VERSION_M "2"
//#define VERSION_A "pre"

/// this containers contain agents and obstacles
AgentContainer agent;                             
ObstacleContainer obstacle;

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
	//  srandom(3);

	Q_INIT_RESOURCE(application);
	
	QApplication app(argc, argv);
	QApplication::setStyle(new Style());


	MainWindow mainwindow;
	mainwindow.show();

	QGraphicsScene *scene = new QGraphicsScene(0);

	scene->setBackgroundBrush(Qt::black);
	scene->setItemIndexMethod(QGraphicsScene::NoIndex);

	scene->addRect(QRectF(0, 100, 1, 1), QPen(Qt::red, 1, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));	
	scene->addRect(QRectF(100, 0, 1, 1), QPen(Qt::red, 1, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));	
	scene->addRect(QRectF(200, 0, 1, 1), QPen(Qt::red, 1, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));	
	//	scene->addRect(QRectF(300, 0, 1, 1), QPen(Qt::red, 1, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));	
	scene->addRect(QRectF(0, -100, 1, 1), QPen(Qt::red, 1, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));	
	scene->addRect(QRectF(-100, 0, 1, 1), QPen(Qt::red, 1, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));	
	scene->addRect(QRectF(-200, 0, 1, 1), QPen(Qt::red, 1, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));	
	//	scene->addRect(QRectF(-300, 0, 1, 1), QPen(Qt::red, 1, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));	

	Tvector v0; v0.x =  0; v0.y = 0; v0.z = 0;

	Tvector v1; v1.x = -165; v1.y = -55; v1.z = 0;
	Tvector v11; v11.x = -110; v11.y = -0; v11.z = 0;
	Tvector v2; v2.x = +165; v2.y = -55; v2.z = 0;
	Tvector v22; v22.x = 110; v22.y = -0; v22.z = 0;
	Tvector v23; v23.x = 165; v23.y = -150; v23.z = 0;

	Tvector v3; v3.x = 0; v3.y = -150; v3.z = 0;
	Tvector v4; v4.x = 0; v4.y = +120; v4.z = 0;

	// saeulen
	obstacle.push_back(Tobstacle(-4, -50,  0, -50, scene->addLine(1,1,0,0,QPen(Qt::gray, 1, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin))));
	obstacle.push_back(Tobstacle(-4, -46,  0, -46, scene->addLine(1,1,0,0,QPen(Qt::gray, 1, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin))));
	obstacle.push_back(Tobstacle(-4, -46, -4, -50, scene->addLine(1,1,0,0,QPen(Qt::gray, 1, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin))));
	obstacle.push_back(Tobstacle( 0, -46,  0, -50, scene->addLine(1,1,0,0,QPen(Qt::gray, 1, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin))));

	obstacle.push_back(Tobstacle( 4, -40,  0, -40, scene->addLine(1,1,0,0,QPen(Qt::gray, 1, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin))));
	obstacle.push_back(Tobstacle( 4, -36,  0, -36, scene->addLine(1,1,0,0,QPen(Qt::gray, 1, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin))));
	obstacle.push_back(Tobstacle( 4, -36,  4, -40, scene->addLine(1,1,0,0,QPen(Qt::gray, 1, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin))));
	obstacle.push_back(Tobstacle( 0, -36,  0, -40, scene->addLine(1,1,0,0,QPen(Qt::gray, 1, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin))));

	obstacle.push_back(Tobstacle( 2, -30, -2, -30, scene->addLine(1,1,0,0,QPen(Qt::gray, 1, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin))));
	obstacle.push_back(Tobstacle( 2, -26, -2, -26, scene->addLine(1,1,0,0,QPen(Qt::gray, 1, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin))));
	obstacle.push_back(Tobstacle( 2, -26,  2, -30, scene->addLine(1,1,0,0,QPen(Qt::gray, 1, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin))));
	obstacle.push_back(Tobstacle(-2, -26, -2, -30, scene->addLine(1,1,0,0,QPen(Qt::gray, 1, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin))));


	// walls

	// senkrecht unten
	obstacle.push_back(Tobstacle(-15, 120, -15,  15, scene->addLine(1,1,0,0,QPen(Qt::gray, 1, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin))));
	obstacle.push_back(Tobstacle( 15, 120,  15,  15, scene->addLine(1,1,0,0,QPen(Qt::gray, 1, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin))));
	obstacle.push_back(Tobstacle(-15, 120,  15, 120, scene->addLine(1,1,0,0,QPen(Qt::gray, 1, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin))));

	// senkrecht oben
	obstacle.push_back(Tobstacle(-15, -150, -15, -15, scene->addLine(1,1,0,0,QPen(Qt::gray, 1, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin))));
	obstacle.push_back(Tobstacle( 15, -150,  15, -15, scene->addLine(1,1,0,0,QPen(Qt::gray, 1, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin))));
	obstacle.push_back(Tobstacle(-15, -150,  15,-150, scene->addLine(1,1,0,0,QPen(Qt::gray, 1, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin))));

	// links 1
	obstacle.push_back(Tobstacle(-100, -15, -15, -15, scene->addLine(1,1,0,0,QPen(Qt::gray, 1, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin))));
	obstacle.push_back(Tobstacle(-120,  15, -15,  15, scene->addLine(1,1,0,0,QPen(Qt::gray, 1, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin))));

	// links 2
	obstacle.push_back(Tobstacle(-150, -65, -100, -15, scene->addLine(1,1,0,0,QPen(Qt::gray, 1, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin))));
	obstacle.push_back(Tobstacle(-180, -45, -120,  15, scene->addLine(1,1,0,0,QPen(Qt::gray, 1, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin))));
	obstacle.push_back(Tobstacle(-180, -45, -150, -65, scene->addLine(1,1,0,0,QPen(Qt::gray, 1, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin))));

	// rechts 1
	obstacle.push_back(Tobstacle( 100, -15,  15, -15, scene->addLine(1,1,0,0,QPen(Qt::gray, 1, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin))));
	obstacle.push_back(Tobstacle( 120,  15,  15,  15, scene->addLine(1,1,0,0,QPen(Qt::gray, 1, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin))));

	// rechts 2
	obstacle.push_back(Tobstacle( 150, -65,  100, -15, scene->addLine(1,1,0,0,QPen(Qt::gray, 1, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin))));
	obstacle.push_back(Tobstacle( 180, -45,  120,  15, scene->addLine(1,1,0,0,QPen(Qt::gray, 1, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin))));

	// bottleneck
	obstacle.push_back(Tobstacle( 180, -45,  180, -65, scene->addLine(1,1,0,0,QPen(Qt::gray, 1, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin))));
	obstacle.push_back(Tobstacle( 180, -65,  170, -85, scene->addLine(1,1,0,0,QPen(Qt::gray, 1, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin))));
	obstacle.push_back(Tobstacle( 150, -65,  160, -85, scene->addLine(1,1,0,0,QPen(Qt::gray, 1, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin))));
	obstacle.push_back(Tobstacle( 180,-100,  170, -85, scene->addLine(1,1,0,0,QPen(Qt::gray, 1, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin))));
	obstacle.push_back(Tobstacle( 150,-100,  160, -85, scene->addLine(1,1,0,0,QPen(Qt::gray, 1, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin))));

	obstacle.push_back(Tobstacle( 150,-100,  150,-150, scene->addLine(1,1,0,0,QPen(Qt::gray, 1, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin))));
	obstacle.push_back(Tobstacle( 180,-100,  180,-150, scene->addLine(1,1,0,0,QPen(Qt::gray, 1, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin))));
	obstacle.push_back(Tobstacle( 150,-150,  180,-150, scene->addLine(1,1,0,0,QPen(Qt::gray, 1, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin))));

  
	// Tobstacle o2;
	// o2.line = scene->addLine(0,0,1,1, QPen(Qt::gray, 1, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
	// o2.setPosition(-50, 10, -5, 25);
	// obstacle.push_back(o2);

	for (int i = 0; i<100; i++) { 
		Tagent a;
		//		a.setPosition( XXX +  qrand()/(RAND_MAX/1000), YYY + qrand()/(RAND_MAX/400), ZZZ + qrand()/(RAND_MAX/400));
		if (i == 1) {
			a.rect = scene->addRect(QRectF(0, 0, 1, 1), QPen(Qt::red, 1, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));	
		} else {
			a.rect = scene->addRect(QRectF(0, 0, 1, 1), QPen(Qt::green, 1, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));	
		}

		if (i%2 == 0) {
			a.setPosition( XXX +  qrand()/(RAND_MAX/200) -100, YYY + qrand()/(RAND_MAX/10) -5, ZZZ);
			//			a.destinations.enqueue(v0);
			a.destinations.enqueue(v11);
			a.destinations.enqueue(v1);
			a.destinations.enqueue(v11);
			//			a.destinations.enqueue(v0);
			a.destinations.enqueue(v22);
			a.destinations.enqueue(v2);
			a.destinations.enqueue(v23);
			a.destinations.enqueue(v2);
			a.destinations.enqueue(v22);
		} else {
			a.setPosition( XXX +  qrand()/(RAND_MAX/10) -5, YYY + qrand()/(RAND_MAX/200) -100, ZZZ);
			//			a.destinations.enqueue(v0);
			a.destinations.enqueue(v4);
			//			a.destinations.enqueue(v0);
			a.destinations.enqueue(v3);
		}

		agent.push_back(a);
	}
	
	mainwindow.graphicsView->setScene(scene);
	mainwindow.graphicsView->setViewport(new QGLWidget(QGLFormat(QGL::SampleBuffers)));

	return app.exec();
}




