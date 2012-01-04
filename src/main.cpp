//
// spacesim - A microscopic space ship simulation system. 
// Copyright (c) 2010 by Christian Gloor
// based on pedsim - A microscopic pedestrian simulation system. 
// Copyright (c) 2003 - 2007 by Christian Gloor
//                              
// You can redistribute and/or modify this program under the terms of
// the GNU General Public License.  See copying.txt for details.
// 


#include <QApplication>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QtOpenGL>
#include <QGLWidget>
#include <QGLFormat>
#include <QPen>

using namespace std;

#include <iostream>                       // cout
#include <stdlib.h>                       // random

#include <vector>

#include "mainwindow.h"
#include "agent.h"

#include "main.h"

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
	cout << "simple space ship simulation" << endl;
	//	cout << "version " << VERSION_M << "." << GITCHANGENUMBER << "-" << VERSION_A << " (" << GITVERSION << ") committed by " << GITAUTHOR << endl;
  //  srandom(3);

	Q_INIT_RESOURCE(application);
	
	QApplication app(argc, argv);
	MainWindow mainWin;
	mainWin.show();

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

	for (int i = 0; i<300; i++) { 
		Tagent a;
		a.setType(i%2);
		//			a.setPosition( XXX +  qrand()/(RAND_MAX/40) -20, YYY + qrand()/(RAND_MAX/40) -20, ZZZ + qrand()/(RAND_MAX/40) -20);
		//a.setType(0);
		if (i%2 == 0) {
			a.setPosition( XXX +  qrand()/(RAND_MAX/1000) -500 -1000, YYY + qrand()/(RAND_MAX/400) -200, ZZZ + qrand()/(RAND_MAX/400) -200);
			a.rect = scene->addRect(QRectF(0, 0, 1, 1), QPen(Qt::red, 1, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));	
		} else {
			a.setPosition( XXX +  qrand()/(RAND_MAX/1000) -500 +1000, YYY + qrand()/(RAND_MAX/400) -200, ZZZ + qrand()/(RAND_MAX/400) -200);
			a.rect = scene->addRect(QRectF(0, 0, 1, 1), QPen(Qt::green, 1, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));	
		}
		agent.push_back(a);
	}

	
	mainWin.graphicsView->setScene(scene);
	mainWin.graphicsView->setViewport(new QGLWidget(QGLFormat(QGL::SampleBuffers)));

	return app.exec();
}




