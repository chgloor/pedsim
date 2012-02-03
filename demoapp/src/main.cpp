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
#include "loadscene.h"

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

// Obstacle *doorobstacle1;
// Obstacle *doorobstacle2;

// ----------------------------------------------------
// Name: main
// Description: - 
// Introduced: chgloor Monday, December 29, 2003 10:31:59
// Return value: 0
// ----------------------------------------------------
int main(int argc, char *argv[]) {
	
	QString scenefile = argv[1];
	if (scenefile == "") {
		scenefile = "scene.xml";
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

	Loadscene l(scenefile, pedscene, graphicsscene);

	// gate
	/*
	  doorobstacle1 = new Obstacle( 80, 10, 80, -10, graphicsscene->addLine(1,1,0,0,QPen(Qt::darkGray, 1, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin)));
	  pedscene->addObstacle(doorobstacle1);
	  doorobstacle2 = new Obstacle( 80-10, 0, 80+10, 00, graphicsscene->addLine(1,1,0,0,QPen(Qt::darkGray, 1, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin)));
	  pedscene->addObstacle(doorobstacle2);
	  pedscene->addObstacle(new Obstacle( 77, -15,  80, -10, graphicsscene->addLine(1,1,0,0,QPen(Qt::darkGray, 1, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin))));
	  pedscene->addObstacle(new Obstacle( 83, -15,  80, -10, graphicsscene->addLine(1,1,0,0,QPen(Qt::darkGray, 1, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin))));
	  pedscene->addObstacle(new Obstacle( 77,  15,  80, 10, graphicsscene->addLine(1,1,0,0,QPen(Qt::darkGray, 1, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin))));
	  pedscene->addObstacle(new Obstacle( 83,  15,  80, 10, graphicsscene->addLine(1,1,0,0,QPen(Qt::darkGray, 1, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin))));
	*/

	mainwindow.graphicsView->setScene(graphicsscene);
	mainwindow.graphicsView->setViewport(new QGLWidget(QGLFormat(QGL::SampleBuffers)));
	mainwindow.graphicsView->setViewportUpdateMode(QGraphicsView::MinimalViewportUpdate);
	mainwindow.graphicsView->setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);	
	mainwindow.graphicsView->show();

	return app.exec();
}




