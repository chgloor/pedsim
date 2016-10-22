//
// pedsim - A microscopic pedestrian simulation system.
// Copyright (c) by Christian Gloor
//

#include "itemcontainer.h"
#include "item.h"

#include <cmath>

#include <QtWidgets>

#include <iostream>

extern QGraphicsScene *scene;


ItemContainer::ItemContainer() {
}


// Removes all items from the container
void ItemContainer::clear() {
    container.clear();
}


void ItemContainer::for_each(void (*fn)(Item*)) {
    QHash<QString, Item*>::iterator it;
    for (it = container.begin(); it != container.end(); ++it) {
        fn(*it);
    }
}

void ItemContainer::removeItem(QString id) {
  scene->removeItem(container[id]);
  container.remove(id);
};


void ItemContainer::updatePosition(QString id, double x, double y) {
  double oldx = container[id]->x;
  double oldy = container[id]->y;

  container[id]->x = x;
  container[id]->y = y;
    
  double newr = atan2(y-oldy, x-oldx) * 180 / 3.1415;
  double oldr = container[id]->rotation();
  double r = oldr * 0.96 + newr * 0.04;
  container[id]->setRotation(r);
}

void ItemContainer::updatePosition(QString id, double x, double y, double radius) {
  updatePosition(id, x, y);
  container[id]->radius = radius;
}


void ItemContainer::updatePosition(QString id, double x, double y, double dx, double dy) {
    updatePosition(id, x, y);
    container[id]->dx = dx;
    container[id]->dy = dy;
}
