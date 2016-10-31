//
// pedsim - A microscopic pedestrian simulation system.
// Copyright (c) by Christian Gloor
//

#include "itemcontainer.h"
#include "item.h"

#include <cmath>

extern Qt3DCore::QEntity *scene;


ItemContainer::ItemContainer() {}

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
//  scene->removeItem(container[id]);
  container[id]->z = -100; // don't know how to remove from scene. Send to agent heaven (which is below 0)
  container[id]->updateComponents();
  container.remove(id);
  //container[id]->deleteLater();
  //  scene->removeComponent(dynamic_cast<Qt3DCore::QComponent*>(container[id]));
};

void ItemContainer::updatePosition(QString id, double x, double y) {
  double oldx = container[id]->x;
  double oldy = container[id]->y;

  container[id]->x = x;
  container[id]->y = y;
    
  container[id]->updateComponents();
//  double newr = atan2(y-oldy, x-oldx) * 180 / 3.1415;
//  double oldr = container[id]->rotation();
//  double r = oldr * 0.96 + newr * 0.04;
//  container[id]->setRotation(r);
}

void ItemContainer::setRotation(QString id, double r) {
	container[id]->r = r;
	container[id]->updateComponents();
};

Item* ItemContainer::at(QString id) {
  return container[id];
}
