// Copyright (C) by Christian Gloor. All rights reserved.
// See main.cpp for details.

#include <QtGui>

#include <vector>

#include "agent.h"
#include "scene.h"

#include "mainwindow.h"
#include "control.h"
#include "config.h"
#include "obstacle.h"

#define ZOOMFACTOR 1.2

using namespace std;

extern vector<Agent*> myagents;                             
extern Scene *pedscene;

extern long systemtime;
extern Config config;

extern Obstacle *doorobstacle1;
extern Obstacle *doorobstacle2;


MainWindow::MainWindow() {
	graphicsView = new QGraphicsView();
	setCentralWidget(graphicsView);
	graphicsView->scale(2, 2);
	
	uicontrol = new Control(this, false);
	addDockWidget(Qt::LeftDockWidgetArea, uicontrol);

	createActions();
	createMenus();
	createStatusBar();
	
	readSettings();

	connect(uicontrol, SIGNAL(zoomin()), this, SLOT(zoomin()));
	connect(uicontrol, SIGNAL(zoomout()), this, SLOT(zoomout()));
	
	timer = new QTimer(this);
	connect(timer, SIGNAL(timeout()), this, SLOT(timestep()));
	timer->setSingleShot(true);
	timer->start(1000/20);

	QTimer *fpstimer = new QTimer(this);
	connect(fpstimer, SIGNAL(timeout()), this, SLOT(fps()));
	fpstimer->start(3000);
	fpscount = 0;
}

void MainWindow::closeEvent(QCloseEvent *event) {
	event->accept();
}

void MainWindow::about() {
	QMessageBox::about(this, tr("About PedSim Demo"),
							 tr("<b>PedSim Demo</b> is a small pedestrian simulation system"
								 "with an interactive GUI, "
								 "suitable for small experiments. <br>(c) 2012 by Christian Gloor"));
}

void MainWindow::createActions() {
     exitAct = new QAction(tr("E&xit"), this);
     exitAct->setShortcut(tr("Ctrl+Q"));
     exitAct->setStatusTip(tr("Exit the application"));
     connect(exitAct, SIGNAL(triggered()), this, SLOT(close()));

     aboutAct = new QAction(tr("&About"), this);
     aboutAct->setStatusTip(tr("Show the application's About box"));
     connect(aboutAct, SIGNAL(triggered()), this, SLOT(about()));

     zoominAct = new QAction(QIcon(":/images/zoomin.png"), tr("Zoom In"), this);
     zoominAct->setStatusTip(tr("Zoom In"));
     connect(zoominAct, SIGNAL(triggered()), this, SLOT(zoomin()));

     zoomoutAct = new QAction(QIcon(":/images/zoomout.png"), tr("Zoom Out"), this);
     zoomoutAct->setStatusTip(tr("Zoom Out"));
     connect(zoomoutAct, SIGNAL(triggered()), this, SLOT(zoomout()));
 }

void MainWindow::createMenus() {
	fileMenu = menuBar()->addMenu(tr("&File"));
	fileMenu->addSeparator();
	fileMenu->addAction(exitAct);
	
	viewMenu = menuBar()->addMenu(tr("&View"));
	viewMenu->addAction(uicontrol->toggleViewAction());

	menuBar()->addSeparator();

	helpMenu = menuBar()->addMenu(tr("&Help"));
	helpMenu->addAction(aboutAct);
}

void MainWindow::createToolBars() {
	editToolBar = addToolBar(tr("Zoom"));
	editToolBar->addAction(zoominAct);
	editToolBar->addAction(zoomoutAct);
}

void MainWindow::createStatusBar() {
	statusBar()->showMessage(tr("Ready"));
}

void MainWindow::readSettings() {
	QSettings settings("Christian Gloor", "SpaceSim");
	QPoint pos = settings.value("pos", QPoint(200, 200)).toPoint();
	QSize size = settings.value("size", QSize(1280, 800)).toSize();
	resize(size);
	move(pos);
}

void MainWindow::writeSettings() {
	QSettings settings("Christian Gloor", "SpaceSim");
	settings.setValue("pos", pos());
	settings.setValue("size", size());
}

QString MainWindow::strippedName(const QString &fullFileName) {
	return QFileInfo(fullFileName).fileName();
}

void MainWindow::zoomin() {
	graphicsView->scale(ZOOMFACTOR, ZOOMFACTOR);
}

void MainWindow::zoomout() {
		graphicsView->scale(1/ZOOMFACTOR, 1/ZOOMFACTOR);
}

void MainWindow::timestep() {	
	systemtime++;
	fpscount++;
	for (vector<Agent*>::iterator iter = myagents.begin(); iter != myagents.end(); ++iter) {
		Agent *a = (*iter);
		a->move(config.simh);
		pedscene->moveAgent(a);
		//		a->print();
	}
	
	if (systemtime %100 == 0) pedscene->cleanup();
	
	set<Ped::Tagent*> a = pedscene->getNeighbors(0, 0, 15);
	// for (set<Ped::Tagent*>::iterator it = a.begin(); it != a.end(); ++it) {
	// 	cout << "n " << (*it)->getx() << "/" << (*it)->gety() << endl;
	// }
	//	cout << a.size() << endl;


	doorobstacle1->rotate(80, 0, config.simh * 0.1);
	doorobstacle2->rotate(80, 0, config.simh * 0.1);

	statusBar()->showMessage(QString("Systemtime: %1").arg(systemtime));
	timer->start(config.simSpeed);
}

/// 
/// \author  chgloor
/// \date    2012-01-30
/// \return  
/// \warning 
/// \param   
void MainWindow::fps() {	 
	uicontrol->setfps(1.0f*fpscount/3);
	fpscount = 0;
}
