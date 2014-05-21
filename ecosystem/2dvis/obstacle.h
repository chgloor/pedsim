//
// pedsim - A microscopic pedestrian simulation system.
// Copyright (c) by Christian Gloor
//

#ifndef OBSTACLE_H
#define OBSTACLE_H

#include "item.h"

#include <QGraphicsItem>

class Obstacle : public Item {

public:
    Obstacle();

    QRectF boundingRect() const;
    QPainterPath shape() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

protected:
    void advance(int step);

private:
    QColor color;
};

#endif
