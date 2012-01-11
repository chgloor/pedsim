// Copyright (C) by Christian Gloor. All rights reserved.
// See main.cpp for details.

#include <QtGui>

using namespace std;

#include <vector>

#include "agent.h"
#include "mainwindow.h"
#include "control.h"
#include "config.h"

#define ZOOMFACTOR 1.1


/// this container contains agents
extern AgentContainer agent;                             
/// number of (time) steps simulated so far 
extern long systemtime;

extern Config config;

MainWindow::MainWindow() {

	graphicsView = new QGraphicsView();
	setCentralWidget(graphicsView);
	graphicsView->scale(2, 2);
	

	uicontrol = new Control(this, false);
	addDockWidget(Qt::LeftDockWidgetArea, uicontrol);


	createActions();
	createMenus();
	//	createToolBars();
	createStatusBar();
	
	readSettings();
	
	timer = new QTimer(this);
	connect(timer, SIGNAL(timeout()), this, SLOT(timestep()));
	timer->setSingleShot(true);
	timer->start(1000/20);
	//timer->start(0);

}

void MainWindow::closeEvent(QCloseEvent *event) {
	event->accept();
}


void MainWindow::about() {
	QMessageBox::about(this, tr("About PedSim"),
							 tr("<b>PedSim</b> is a small pedestrian simulation system"
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

     // aboutQtAct = new QAction(tr("About &Qt"), this);
     // aboutQtAct->setStatusTip(tr("Show the Qt library's About box"));
     // connect(aboutQtAct, SIGNAL(triggered()), qApp, SLOT(aboutQt()));

     zoominAct = new QAction(QIcon(":/images/zoomin.png"), tr("Zoom In"), this);
     zoominAct->setStatusTip(tr("Zoom In"));
     connect(zoominAct, SIGNAL(triggered()), this, SLOT(zoomin()));

     zoomoutAct = new QAction(QIcon(":/images/zoomout.png"), tr("Zoom Out"), this);
     zoomoutAct->setStatusTip(tr("Zoom Out"));
     connect(zoomoutAct, SIGNAL(triggered()), this, SLOT(zoomout()));

//      resetTimeAct = new QAction(QIcon(":/images/backward.png"), tr("Reset"), this);
//      resetTimeAct->setStatusTip(tr("Reset Time"));
//      connect(resetTimeAct, SIGNAL(triggered()), this, SLOT(resetTime()));

//      startTimeAct = new QAction(QIcon(":/images/start.png"), tr("Start"), this);
//      startTimeAct->setStatusTip(tr("Start"));
//      connect(startTimeAct, SIGNAL(triggered()), this, SLOT(startTime()));
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
	//	helpMenu->addAction(aboutQtAct);
}

void MainWindow::createToolBars() {
	// fileToolBar = addToolBar(tr("File"));
	// editToolBar = addToolBar(tr("Edit"));
	editToolBar = addToolBar(tr("Zoom"));
	editToolBar->addAction(zoominAct);
	editToolBar->addAction(zoomoutAct);
	
// 	editToolBar = addToolBar(tr("Play"));
// 	editToolBar->addAction(resetTimeAct);
// 	editToolBar->addAction(startTimeAct);	
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

// void MainWindow::startTime() {
// 		graphicsView->scale(1/ZOOMFACTOR, 1/ZOOMFACTOR);
// }

// void MainWindow::resetTime() {
// 		graphicsView->scale(1/ZOOMFACTOR, 1/ZOOMFACTOR);
// }

void MainWindow::timestep() {	
	systemtime++;
	for (AgentIterator iter = agent.begin(); iter != agent.end(); ++iter) {
		iter->move(systemtime);
		Tagent a = *iter;
	}

	// char t[255];
	// sprintf(t, "Systemtime: %08ld", systemtime);
	statusBar()->showMessage(QString("Systemtime: %1").arg(systemtime));
	timer->start(config.simSpeed);
}
