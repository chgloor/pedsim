// Copyright (C) by Christian Gloor. All rights reserved.
// See main.cpp for details.

#include <QtGui>

#include <vector>

#include "agent.h"
#include "mainwindow.h"
#include "control.h"
#include "config.h"

#define ZOOMFACTOR 1.2

using namespace std;

extern AgentContainer agent;                             
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
	createStatusBar();
	
	readSettings();

	connect(uicontrol, SIGNAL(zoomin()), this, SLOT(zoomin()));
	connect(uicontrol, SIGNAL(zoomout()), this, SLOT(zoomout()));
	
	timer = new QTimer(this);
	connect(timer, SIGNAL(timeout()), this, SLOT(timestep()));
	timer->setSingleShot(true);
	timer->start(1000/20);
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

	for (AgentIterator iter = agent.begin(); iter != agent.end(); ++iter) {
		iter->move();
	}

	statusBar()->showMessage(QString("Systemtime: %1").arg(systemtime));
	timer->start(config.simSpeed);
}
