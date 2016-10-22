//
// pedsim - A microscopic pedestrian simulation system.
// Copyright (c) by Christian Gloor
//

#include "obstacle.h"

#include <QGraphicsScene>
#include <QPainter>
#include <QStyleOption>

#include <iostream>

static const double SCALE = 10.0;


Obstacle::Obstacle() : color(qrand() % 256, qrand() % 256, qrand() % 256) {
}


QRectF Obstacle::boundingRect() const {
    qreal adjust = 0.5;
    return QRectF(SCALE * (-1800 - adjust), SCALE * (-2200 - adjust), SCALE * (3600 + adjust), SCALE * (6000 + adjust));
}


QPainterPath Obstacle::shape() const {
    QPainterPath path;
    path.addRect(SCALE * -1000, SCALE * -1000, SCALE * 2000, SCALE * 2000);
    return path;
}


void Obstacle::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *) {
    painter->setBrush(color);

    painter->setPen(QPen(QBrush(QColor(255, 255, 255, 255)), SCALE * 0.1));
    painter->drawLine(0, 0, SCALE * dx, SCALE * dy);
    painter->setPen(QPen(QBrush(QColor(0, 200, 255, 50)), SCALE * 1));
    painter->drawLine(0, 0, SCALE * dx, SCALE * dy);
}


void Obstacle::advance(int step) {
    if (!step) return;
    setPos(SCALE * x, SCALE * y);
    //    std::cout << x << "/" <<  y << " " << dx << "/" << dy << std::endl;
}
