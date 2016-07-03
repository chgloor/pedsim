//
// pedsim - A microscopic pedestrian simulation system.
// Copyright (c) by Christian Gloor
//

#include "agent.h"

#include <QGraphicsScene>
#include <QPainter>
#include <QStyleOption>

static const double SCALE = 10.0;


//Agent::Agent() : color(qrand() % 256, qrand() % 256, qrand() % 256) {}

Agent::Agent() : color(255, 255, 255) {
}


QRectF Agent::boundingRect() const {
    qreal adjust = 0.5;
    return QRectF(SCALE * (-18 - adjust), SCALE * (-22 - adjust), SCALE * (36 + adjust), SCALE * (60 + adjust));
}


QPainterPath Agent::shape() const {
    QPainterPath path;
    path.addRect(SCALE * -10, SCALE * -20, SCALE * 20, SCALE * 20);
    return path;
}


void Agent::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *) {
    painter->setBrush(color);
    painter->setPen(QPen(QBrush(Qt::white), .1));
    painter->drawEllipse(SCALE * -0.5, SCALE * -0.5, SCALE * 1.0, SCALE * 1.0);
}


void Agent::advance(int step) {
    if (!step) return;
    setPos(SCALE * x, SCALE * y);
}
