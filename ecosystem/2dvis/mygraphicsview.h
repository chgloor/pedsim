//
// pedsim - A microscopic pedestrian simulation system.
// Copyright (c) by Christian Gloor
//

// inherited from http://www.qtcentre.org/wiki/index.php?title=QGraphicsView:_Smooth_Panning_and_Zooming

#ifndef MYGRAPHICSVIEW_H
#define MYGRAPHICSVIEW_H

#include <QGraphicsView>
#include <QGraphicsRectItem>

class MyGraphicsView : public QGraphicsView {
public:
    MyGraphicsView(QGraphicsScene *scene, QWidget* parent = NULL);

protected:
   virtual void wheelEvent(QWheelEvent* event);

};

#endif
