//
// pedsim - A microscopic pedestrian simulation system.
// Copyright (c) by Christian Gloor
//

#include "agent.h"

#include <QGraphicsScene>
#include <QPainter>
#include <QStyleOption>


Agent::Agent() : color(qrand() % 256, qrand() % 256, qrand() % 256) {
}


QRectF Agent::boundingRect() const {
    qreal adjust = 0.5;
    return QRectF(-18 - adjust, -22 - adjust, 36 + adjust, 60 + adjust);
}


QPainterPath Agent::shape() const {
    QPainterPath path;
    path.addRect(-10, -20, 20, 20);
    return path;
}


void Agent::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *) {
    painter->setBrush(color);
    painter->setPen(QPen(QBrush(Qt::white), .1));
    painter->drawEllipse(-0.5, -0.5, 1.0, 1.0);
}


void Agent::advance(int step) {
    if (!step) return;
    setPos(x, y);
}
