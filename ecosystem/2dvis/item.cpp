//
// pedsim - A microscopic pedestrian simulation system.
// Copyright (c) by Christian Gloor
//

#include "item.h"

#include <QGraphicsScene>
#include <QPainter>
#include <QStyleOption>


Item::Item() : color(qrand() % 256, qrand() % 256, qrand() % 256) {
}


QRectF Item::boundingRect() const {
    qreal adjust = 0.5;
    return QRectF(-18 - adjust, -22 - adjust, 36 + adjust, 60 + adjust);
}


QPainterPath Item::shape() const {
    QPainterPath path;
    path.addRect(-10, -20, 20, 20);
    return path;
}


void Item::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *) {
    painter->setBrush(color);
    painter->setPen(QPen(QBrush(Qt::white), .1));
    painter->drawEllipse(-0.5, -0.5, 1.0, 1.0);
}


void Item::advance(int step) {
    if (!step) return;
    setPos(x, y);
}
