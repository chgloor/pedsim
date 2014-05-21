//
// pedsim - A microscopic pedestrian simulation system.
// Copyright (c) by Christian Gloor
//

#ifndef ITEM_H
#define ITEM_H

#include <QGraphicsItem>

class Item : public QGraphicsItem {

public:
    Item();

    QRectF boundingRect() const;
    QPainterPath shape() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    double x;
    double y;
    double dx;
    double dy;

protected:
    void advance(int step);

private:
    QColor color;
};

#endif
