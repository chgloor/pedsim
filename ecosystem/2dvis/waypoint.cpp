//
// pedsim - A microscopic pedestrian simulation system.
// Copyright (c) by Christian Gloor
//

#include "waypoint.h"

#include <QGraphicsScene>
#include <QPainter>
#include <QStyleOption>

static const double SCALE = 10.0;


//Waypoint::Waypoint() : color(qrand() % 256, qrand() % 256, qrand() % 256) {}

Waypoint::Waypoint() : color(127, 0, 0, 20) {}


QRectF Waypoint::boundingRect() const {
    qreal adjust = 0.5;
    return QRectF(SCALE * (-18 - adjust), SCALE * (-22 - adjust), SCALE * (36 + adjust), SCALE * (60 + adjust));
}


QPainterPath Waypoint::shape() const {
    QPainterPath path;
    path.addRect(SCALE * -10, SCALE * -20, SCALE * 20, SCALE * 20);
    return path;
}


void Waypoint::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *) {
    painter->setBrush(color);
    painter->setPen(QPen(QBrush(Qt::red), 1));
    painter->drawEllipse(SCALE * (-radius), SCALE * (-radius), SCALE * radius * 2, SCALE * radius *2);
}


void Waypoint::advance(int step) {
    if (!step) return;
    setPos(SCALE * x, SCALE * y);
}
