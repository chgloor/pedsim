//
// pedsim - A microscopic pedestrian simulation system.
// Copyright (c) by Christian Gloor
//

#ifndef WAYPOINT_H
#define WAYPOINT_H

#include "item.h"

#include <QGraphicsItem>

class Waypoint : public Item {

public:
    Waypoint();

    QRectF boundingRect() const;
    QPainterPath shape() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

protected:
    void advance(int step);

private:
    QColor color;
};

#endif
