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

Agent::Agent() : color(255, 0, 0) {
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

  // body
  painter->setBrush(color);
  painter->setPen(QPen(QBrush(Qt::white), .1));
  painter->drawEllipse(SCALE * -0.2, SCALE * -0.5, SCALE * 0.4, SCALE * 1.0);

  // head
  painter->setBrush(QColor(255, 192, 0));
  painter->setPen(QPen(QBrush(Qt::white), .1));
  painter->drawEllipse(SCALE * -0.3, SCALE * -0.3, SCALE * 0.6, SCALE * 0.6);

  // eyes
  painter->setBrush(Qt::black);
  painter->setPen(QPen(QBrush(Qt::white), .05));
  painter->drawEllipse(SCALE * 0.15, SCALE * -0.175, SCALE * 0.1, SCALE * 0.1);
  painter->drawEllipse(SCALE * 0.15, SCALE *  0.075, SCALE * 0.1, SCALE * 0.1);

  // hair
  painter->setBrush(QColor(139,69,19)); // saddle brown
  painter->setPen(QPen(QBrush(Qt::white), .05));
  painter->drawChord(SCALE * -0.3, SCALE * -0.3, SCALE * 0.6, SCALE * 0.6, 90*16, 180*16);
}


void Agent::advance(int step) {
    if (!step) return;
    setPos(SCALE * x, SCALE * y);
}
