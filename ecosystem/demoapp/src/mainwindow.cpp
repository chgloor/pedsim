///
/// pedsim - A microscopic pedestrian simulation system.
/// Copyright (c) 2003 - 2013 by Christian Gloor
///

#include "mainwindow.h"
#include "control.h"
#include "config.h"

#include <QtWidgets>

#define ZOOMFACTOR 1.2

using namespace std;

extern Config config;

MainWindow::MainWindow() {
    graphicsView = new QGraphicsView();
    setCentralWidget(graphicsView);
    graphicsView->scale(4, 4);

    uicontrol = new Control(this, false);
    addDockWidget(Qt::LeftDockWidgetArea, uicontrol);

    createActions();
    createMenus();
    createStatusBar();

    readSettings();

    connect(uicontrol, SIGNAL(zoomin()), this, SLOT(zoomin()));
    connect(uicontrol, SIGNAL(zoomout()), this, SLOT(zoomout()));
}


void MainWindow::closeEvent(QCloseEvent *event) {
    event->accept();
}


void MainWindow::about() {
    QMessageBox::about(this, tr("About PedSim Demo"),
                             tr("<b>PedSim Demo</b> is a small pedestrian simulation system"
                                 "with an interactive GUI, "
                                 "suitable for small experiments. <br>"
                                 "It is based on <b>libpedsim</b>, http://pedsim.silmaril.org/<br>"
                                 " (c) by Christian Gloor"));
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
    QSettings settings("Christian Gloor", "PedSim");
    QPoint pos = settings.value("pos", QPoint(200, 200)).toPoint();
    QSize size = settings.value("size", QSize(1280, 800)).toSize();
    resize(size);
    move(pos);
}


void MainWindow::writeSettings() {
    QSettings settings("Christian Gloor", "PedSim");
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
