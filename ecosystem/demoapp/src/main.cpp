///
/// pedsim - A microscopic pedestrian simulation system.
/// Copyright (c) 2003 - 2013 by Christian Gloor
///
/// http://pedsim.silmaril.org/
///       _
///   _  (__/   _ _ _   /    _ / _ ' __/'_    _ /    _
/// _) ()/ /((/(// (-  ()(/ ( /)/ /_) //(//) (/(()()/
///                      /                  _/
///

// Linux:
// ---> export LD_LIBRARY_PATH=libpedsim

#include <QtWidgets>

// #include <QGraphicsView>
// #include <QGraphicsScene>
//#include <QtOpenGL>

#include <iostream>

#include "mainwindow.h"
//#include "style.h"
#include "scene.h"
#include "config.h"
#include "loadscene.h"

#include "ped_outputwriter.h"

using namespace std;

Config config;

Scene *gblscene;

/// The programm entry point. Sets up everything, and calls QT exec to start the event loop.
/// \date    2003-12-29
/// \return  whatever app.exec() returns.
int main(int argc, char **argv) {

    QString scenefile = argv[1];
    if (scenefile == "") {
        scenefile = "scene.xml";
    }

    Q_INIT_RESOURCE(application);

    QApplication app(argc, argv);
    //	QApplication::setStyle(new Style());

    MainWindow mainwindow;
    mainwindow.show();

    QGraphicsScene *graphicsscene = new QGraphicsScene();

    graphicsscene->setBackgroundBrush(Qt::black);
    graphicsscene->setItemIndexMethod(QGraphicsScene::NoIndex);

    Scene *pedscene = new Scene(graphicsscene);
    pedscene->setOutputWriter(new Ped::UDPOutputWriter());
    gblscene = pedscene;

    Loadscene l(scenefile, pedscene, graphicsscene);

    mainwindow.graphicsView->setScene(graphicsscene);
    // mainwindow.graphicsView->setViewport(new QGLWidget(QGLFormat(QGL::SampleBuffers)));
    mainwindow.graphicsView->setViewportUpdateMode(QGraphicsView::MinimalViewportUpdate);
    mainwindow.graphicsView->setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);
    mainwindow.graphicsView->show();

    return app.exec();
}
