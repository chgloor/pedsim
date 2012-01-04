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
#include "style.h"
#include "vector.h"

#include "main.h"

using namespace std;


//#define VERSION_M "2"
//#define VERSION_A "pre"

/// this container contains agents
AgentContainer agent;                             

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

	scene->addRect(QRectF(0, 0, 1, 1), QPen(Qt::white, 1, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));	
	scene->addRect(QRectF(0, 100, 1, 1), QPen(Qt::gray, 1, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));	
	scene->addRect(QRectF(0, 110, 1, 1), QPen(Qt::gray, 1, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));	
	scene->addRect(QRectF(100, 0, 1, 1), QPen(Qt::gray, 1, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));	
	scene->addRect(QRectF(110, 0, 1, 1), QPen(Qt::gray, 1, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));	
	scene->addRect(QRectF(0, -100, 1, 1), QPen(Qt::gray, 1, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));	
	scene->addRect(QRectF(-100, 0, 1, 1), QPen(Qt::gray, 1, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));	

	for (int i = 0; i<100; i++) { 
		Tagent a;
		//		a.setPosition( XXX +  qrand()/(RAND_MAX/1000), YYY + qrand()/(RAND_MAX/400), ZZZ + qrand()/(RAND_MAX/400));
		a.setPosition( XXX +  qrand()/(RAND_MAX/400) -200, YYY + qrand()/(RAND_MAX/400) -200, ZZZ);
		a.rect = scene->addRect(QRectF(0, 0, 1, 1), QPen(Qt::green, 1, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));	

		Tvector v;
		v.x = -100;
		v.y = 0;
		v.z = 0;
		a.destinations.enqueue(v);
		v.x = 100;
		a.destinations.enqueue(v);

		agent.push_back(a);
	}
	
	mainwindow.graphicsView->setScene(scene);
	mainwindow.graphicsView->setViewport(new QGLWidget(QGLFormat(QGL::SampleBuffers)));

	return app.exec();
}




