//
// pedsim - A microscopic pedestrian simulation system.
// Copyright (c) by Christian Gloor
//

#include <QtWidgets>

#include <math.h>

#include "mygraphicsview.h"
#include "agent.h"
#include "obstacle.h"
#include "itemcontainer.h"
#include "receiver.h"

static const int AgentCount = 50;

static const double SCALE = 10.0;

QGraphicsScene *scene;

ItemContainer agentcontainer;
ItemContainer obstaclecontainer;


int main(int argc, char **argv) {
    QApplication app(argc, argv);
    qsrand(QTime(0, 0, 0).secsTo(QTime::currentTime()));

    scene = new QGraphicsScene();

    scene->setSceneRect(SCALE * -100, SCALE * -100, SCALE * 200, SCALE * 200);
    scene->setItemIndexMethod(QGraphicsScene::NoIndex);

    MyGraphicsView view(scene);
    view.setRenderHint(QPainter::Antialiasing);
    view.setBackgroundBrush(QPixmap(":/images/street.jpg"));
    view.setCacheMode(QGraphicsView::CacheBackground);
    view.setViewportUpdateMode(QGraphicsView::BoundingRectViewportUpdate);
    view.setDragMode(QGraphicsView::ScrollHandDrag);
    view.setWindowTitle(QT_TRANSLATE_NOOP(QGraphicsView, "PEDSIM's 2D Visualizer"));
    view.resize(900, 450);
    view.scale(5, 5);
    view.show();

    Receiver receiver;

    QTimer timer;
    QObject::connect(&timer, SIGNAL(timeout()), scene, SLOT(advance()));
    timer.start(1000 / 33);

    return app.exec();
}
