//
// pedsim - A microscopic pedestrian simulation system.
// Copyright (c) by Christian Gloor
//

#include "item.h"

#include <QGraphicsScene>
#include <QPainter>
#include <QStyleOption>

static const double SCALE = 10.0;


Item::Item() : color(qrand() % 256, qrand() % 256, qrand() % 256) {
}


QRectF Item::boundingRect() const {
    qreal adjust = 0.5;
    return QRectF(-18 - adjust, -22 - adjust, 36 + adjust, 60 + adjust);
    return QRectF(SCALE * (-18 - adjust), SCALE * (-22 - adjust), SCALE * (36 + adjust), SCALE * (60 + adjust));
}


QPainterPath Item::shape() const {
    QPainterPath path;
    path.addRect(SCALE * -10, SCALE * -20, SCALE * 20, SCALE * 20);
    return path;
}


void Item::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *) {
    painter->setBrush(color);
    painter->setPen(QPen(QBrush(Qt::white), .1));
    painter->drawEllipse(SCALE * -0.5, SCALE * -0.5, SCALE * 1.0, SCALE * 1.0);
}


void Item::advance(int step) {
    if (!step) return;    
    setPos(SCALE * x, SCALE * y);
}
