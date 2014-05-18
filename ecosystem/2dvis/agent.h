//
// pedsim - A microscopic pedestrian simulation system.
// Copyright (c) by Christian Gloor
//

#ifndef AGENT_H
#define AGENT_H

#include <QGraphicsItem>

class Agent : public QGraphicsItem {

public:
    Agent();

    QRectF boundingRect() const;
    QPainterPath shape() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    double x;
    double y;

protected:
    void advance(int step);

private:
    qreal angle;
    qreal speed;
    qreal agentEyeDirection;
    QColor color;
};

#endif
