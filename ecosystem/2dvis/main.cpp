//
// pedsim - A microscopic pedestrian simulation system.
// Copyright (c) by Christian Gloor
//

#include <QtWidgets>

#include <math.h>

#include "agent.h"
#include "receiver.h"

static const int AgentCount = 50;

int main(int argc, char **argv) {
    QApplication app(argc, argv);
    qsrand(QTime(0, 0, 0).secsTo(QTime::currentTime()));

    QGraphicsScene scene;
    scene.setSceneRect(-300, -300, 600, 600);
    scene.setItemIndexMethod(QGraphicsScene::NoIndex);

    for (int i = 0; i < AgentCount; ++i) {
        Agent *agent = new Agent;
        agent->setPos(::sin((i * 6.28) / AgentCount) * 200,
                      ::cos((i * 6.28) / AgentCount) * 200);
        scene.addItem(agent);
    }

    QGraphicsView view(&scene);
    view.setRenderHint(QPainter::Antialiasing);
    view.setBackgroundBrush(QPixmap(":/images/street.jpg"));
    view.setCacheMode(QGraphicsView::CacheBackground);
    view.setViewportUpdateMode(QGraphicsView::BoundingRectViewportUpdate);
    view.setDragMode(QGraphicsView::ScrollHandDrag);
    view.setWindowTitle(QT_TRANSLATE_NOOP(QGraphicsView, "PEDSIM's 2D Visualizer"));
    view.resize(900, 450);
    view.show();

    Receiver receiver();

    QTimer timer;
    QObject::connect(&timer, SIGNAL(timeout()), &scene, SLOT(advance()));
    timer.start(1000 / 33);

    //    updateAgentPosition();
    //    QObject::connect(&receiver, updateAgentPosition(int, double, double);

    return app.exec();
}
