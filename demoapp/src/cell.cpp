//
// pedsim - A microscopic pedestrian simulation system.
// Copyright (c) 2003 - 2012 by Christian Gloor
//

#include "cell.h"

#include <QPen>
#include <QGraphicsScene>
#include <QGraphicsItem>

Cell::Cell(double x, double y, double w, double h, QGraphicsScene *gs) {
    graphicsscene = gs;


    QPen p = QPen(QColor(55,55,55), 1, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);
    p.setCosmetic(true);
    QGraphicsRectItem *rect = graphicsscene->addRect(x, y, w, h, p);
    rect->setVisible(true);
    rect->setZValue(-200);
    double v = 1;
    // if ((int)(x/10) % 2 == 0) v = 3;
    values.push_back(v);
}
