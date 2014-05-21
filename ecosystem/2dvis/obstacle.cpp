//
// pedsim - A microscopic pedestrian simulation system.
// Copyright (c) by Christian Gloor
//

#include "obstacle.h"

#include <QGraphicsScene>
#include <QPainter>
#include <QStyleOption>

#include <iostream>

Obstacle::Obstacle() : color(qrand() % 256, qrand() % 256, qrand() % 256) {
}


QRectF Obstacle::boundingRect() const {
    qreal adjust = 0.5;
    return QRectF(-1800 - adjust, -2200 - adjust, 3006 + adjust, 6000 + adjust);
}


QPainterPath Obstacle::shape() const {
    QPainterPath path;
    path.addRect(-1000, -1000, 2000, 2000);
    return path;
}


void Obstacle::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *) {
    painter->setBrush(color);
    painter->setPen(QPen(QBrush(Qt::white), 1));
    painter->drawLine(0, 0, dx, dy);
}


void Obstacle::advance(int step) {
    if (!step) return;
    setPos(x, y);
    //    std::cout << x << "/" <<  y << " " << dx << "/" << dy << std::endl;
}
